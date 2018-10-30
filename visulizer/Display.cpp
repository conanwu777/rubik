# include "Display.hpp"

bool Display::spin = 1;
bool Display::rot = 0;
float Display::angle;
char Display::face;
int Display::num;

string names[26] = {
	"DBL", "DCL", "DFL", "CBL", "CCL", "CFL", "UBL", "UCL", "UFL",
	"DBC", "DCC", "DFC", "CBC", "CFC", "UBC", "UCC", "UFC",
	"DBR", "DCR", "DFR", "CBR", "CCR", "CFR", "UBR", "UCR", "UFR"
};

Display::Display()
{
	buildCube();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(1200, 1200, "Rubik", NULL, NULL);
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	initbufmatrix();
	buffervertexsetup();
	glfwSetKeyCallback(window, processinput);
}

Display::~Display()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaders);
	glfwDestroyWindow(window);
	glfwTerminate();
}

void	Display::getshader()
{
	unsigned int	vertexshader;
	unsigned int	fragmentshader;
	const GLchar *const	vsrc = filetostr("shader.vs");
	const GLchar *const	fsrc = filetostr("shader.fs");

	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vsrc, NULL);
	glCompileShader(vertexshader);
	int success;
    char infoLog[512];
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
   
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fsrc, NULL);
	glCompileShader(fragmentshader);
    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
    
	shaders = glCreateProgram();
	glAttachShader(shaders, vertexshader);
	glAttachShader(shaders, fragmentshader);
	glLinkProgram(shaders);
	
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	free((void*)vsrc);
	free((void*)fsrc);
}

void	Display::buffervertexsetup()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * nv * sizeof(float),
		out, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void	Display::initbufmatrix()
{
	static float tm[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	static float tp[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		-FAR / (FAR - NEAR), -1, 0, 0, -FAR * NEAR / (FAR - NEAR), 0};

	tp[0] = 1.0 / tan(90 / 2 * PI / 180);
	tp[5] = tp[0];
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	getshader();
	proj = glGetUniformLocation(shaders, "p");

	m = (float*)calloc(16, sizeof(float));
	m = (float*)memcpy(m, &tm[0], 16 * sizeof(float));
	p = (float*)calloc(16, sizeof(float));
	p = (float*)memcpy(p, &tp[0], 16 * sizeof(float));
	v = (float*)calloc(16, sizeof(float));
	v = (float*)memcpy(v, &g_v[0], 16 * sizeof(float));
	camx = (float*)calloc(16, sizeof(float));
	camx = (float*)memcpy(camx, &tm[0], 16 * sizeof(float));
	camz = (float*)calloc(16, sizeof(float));
	camz = (float*)memcpy(camz, &tm[0], 16 * sizeof(float));
	prod = (float*)calloc(16, sizeof(float));
}

void Display::buildCube(){
	int count = 0;
	int cubie = 0;
	for (int x = -1; x < 2; x++)
		for (int y = -1; y < 2; y++)
			for (int z = -1; z < 2; z++)
				if (x != 0 || y != 0 || z != 0){
					for (int i = 0; i < 36; i++){

						memcpy(&pos[i], &base[i * 6], 6 * sizeof(float));
						pos[i].x += x;
						pos[i].y += y;
						pos[i].z += z;
					}
					cubie++;
				}
	memcpy(out, pos, sizeof(float) * 5616);
}

void	Display::getmatrix()
{
	float t[16];
	float t2[16];
	float t3[16];

	m[0] = cos(theta);
	m[2] = sin(theta);
	m[8] = -sin(theta);
	m[10] = cos(theta);
	camx[5] = cos(rotx);
	camx[6] = sin(rotx);
	camx[9] = -sin(rotx);
	camx[10] = cos(rotx);
	camz[0] = cos(rotz);
	camz[2] = sin(rotz);
	camz[8] = -sin(rotz);
	camz[10] = cos(rotz);
	mult(camz, camx, &t3[0]);
	mult(g_v, &t3[0], &t2[0]);
	mult(&t2[0], p, &t[0]);
	mult(m, &t[0], prod);
}

void	Display::loop()
{
	keyholds(window);
	getmatrix();
	glUniformMatrix4fv(proj, 1, GL_FALSE, prod);
	glClearColor(0.06f, 0.09f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaders);
	glBindVertexArray(vao);
	if (rot)
		rotate();
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * nv * sizeof(float),
		out, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, nv * 3);
	glfwSwapBuffers(window);
	glfwPollEvents();
	if (spin)
		theta += PI / 100;
	if (theta > 2 * PI)
		theta -= 2 * PI;
}

void	Display::rotate(){
	if (angle == 0)
		memcpy(out, base, sizeof(float) * 5616);
	for (int i = 0; i < 26; i++)
		if (names[i].find(face) != string::npos)
			for (int j = 0; j < 36; j++)
			{
				float t1 = ((float*)(&pos[i][j]))[(num + 2) % 3] * cos(angle)
				- ((float*)(&pos[i][j]))[(num + 1) % 3] * sin(angle);
				float t2 = ((float*)(&pos[i][j]))[(num + 1) % 3] * cos(angle)
				+ ((float*)(&pos[i][j]))[(num + 2) % 3] * sin(angle);
				out[i * 216 + j * 6 + (num + 2) % 3] = t1;
				out[i * 216 + j * 6 + (num + 1) % 3] = t2;
			}
	angle += 0.01;
	if (angle >= PI / 2)
	{
		cube.rotCube(face, 1);
		for (int i = 0; i < 26; i++)
		{
			size_t n = count(names[i].begin(), names[i].end(), 'C');
			if (n == 2){
				continue;
			}
			if (n == 1){
				for (int j = 0; j < 3; j++){
					;
				}
			}
		}
		rot = 0;
	}
}

void	Display::processinput(GLFWwindow *window, int k, int s, int a, int m)
{
	(void)k;
	(void)s;
	(void)a;
	(void)m;
	if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		spin = !spin;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (!rot && (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS
		|| glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS))
	{
		rot = 1;
		angle = 0;
		num = 0;
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			face = 'F';
		else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
			face = 'B';
		else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
			face = 'L';
		else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			face = 'R';
		else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
			face = 'U';
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			face = 'D';
		if (face == 'U' || face == 'D')
			num = 1;
		else if (face == 'F' || face == 'B')
			num = 2;
	}
}

void	Display::keyholds(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		g_v[12] -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		g_v[12] += 0.1;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		g_v[13] -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		g_v[13] += 0.1;
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		g_v[14] += 0.1;
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		g_v[14] -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		rotx -= 0.02;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		rotx += 0.02;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		rotz -= 0.02;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		rotz += 0.02;
}
