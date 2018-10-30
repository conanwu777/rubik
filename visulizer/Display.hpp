#ifndef DISPLAY_HPP
# define DISPLAY_HPP

# include <math.h>
# include <OpenGL/gl3.h>
# include <GLFW/glfw3.h>
# include "rubik.hpp"


# define ORANGE "\e[1;38;2;255;120;10m"
# define RED "\e[1;38;2;225;20;20m"
# define WHITESPACE " \t\n\r"
# define PI 3.1415926
# define FAR 50
# define NEAR 0.1


struct Vertex {
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
};

class Display {
	public:
		GLFWwindow *window;

		float	*m;
		float	*p;
		float	*v;
		float	*camx;
		float	*camz;
		float	*prod;

		Vertex	pos[936];
		Vertex	out[936];
		Vertex	base[36] = {
			//front
			{ 0.45f,  0.45f,  0.45f, 0.757, 0.090, 0.090},
			{ 0.45f,  0.45f, -0.45f, 0.757, 0.090, 0.090},
			{ 0.45f, -0.45f, -0.45f, 0.757, 0.090, 0.090},
			{ 0.45f, -0.45f, -0.45f, 0.757, 0.090, 0.090},
			{ 0.45f, -0.45f,  0.45f, 0.757, 0.090, 0.090},
			{ 0.45f,  0.45f,  0.45f, 0.757, 0.090, 0.090},
			//back
			{-0.45f, -0.45f, -0.45f, 1.000, 0.698, 0.000},
			{ 0.45f, -0.45f, -0.45f, 1.000, 0.698, 0.000},
			{ 0.45f,  0.45f, -0.45f, 1.000, 0.698, 0.000},
			{ 0.45f,  0.45f, -0.45f, 1.000, 0.698, 0.000},
			{-0.45f,  0.45f, -0.45f, 1.000, 0.698, 0.000},
			{-0.45f, -0.45f, -0.45f, 1.000, 0.698, 0.000},
			//front
			{-0.45f, -0.45f,  0.45f, 0.655, 0.819, 0.000},
			{ 0.45f, -0.45f,  0.45f, 0.655, 0.819, 0.000},
			{ 0.45f,  0.45f,  0.45f, 0.655, 0.819, 0.000},
			{ 0.45f,  0.45f,  0.45f, 0.655, 0.819, 0.000},
			{-0.45f,  0.45f,  0.45f, 0.655, 0.819, 0.000},
			{-0.45f, -0.45f,  0.45f, 0.655, 0.819, 0.000},
			//left
			{-0.45f,  0.45f,  0.45f, 0.000, 0.717, 0.612},
			{-0.45f,  0.45f, -0.45f, 0.000, 0.717, 0.612},
			{-0.45f, -0.45f, -0.45f, 0.000, 0.717, 0.612},
			{-0.45f, -0.45f, -0.45f, 0.000, 0.717, 0.612},
			{-0.45f, -0.45f,  0.45f, 0.000, 0.717, 0.612},
			{-0.45f,  0.45f,  0.45f, 0.000, 0.717, 0.612},
			//down
			{-0.45f, -0.45f, -0.45f, 0.152, 0.376, 0.710},
			{ 0.45f, -0.45f, -0.45f, 0.152, 0.376, 0.710},
			{ 0.45f, -0.45f,  0.45f, 0.152, 0.376, 0.710},
			{ 0.45f, -0.45f,  0.45f, 0.152, 0.376, 0.710},
			{-0.45f, -0.45f,  0.45f, 0.152, 0.376, 0.710},
			{-0.45f, -0.45f, -0.45f, 0.152, 0.376, 0.710},
			//up
			{-0.45f,  0.45f, -0.45f, 1.000, 0.968, 0.078},
			{ 0.45f,  0.45f, -0.45f, 1.000, 0.968, 0.078},
			{ 0.45f,  0.45f,  0.45f, 1.000, 0.968, 0.078},
			{ 0.45f,  0.45f,  0.45f, 1.000, 0.968, 0.078},
			{-0.45f,  0.45f,  0.45f, 1.000, 0.968, 0.078},
			{-0.45f,  0.45f, -0.45f, 1.000, 0.968, 0.078}
		};

		float	*color;
		int		nv = 936;
		float	max;

		unsigned int	vao;
		unsigned int	vbo;
		unsigned int	proj;
		unsigned int	shaders;

		float	g_v[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -8, 1};
		static bool	spin;
		float	theta = 0;
		float	rotx = 0;
		float	rotz = 0;

		static bool rot;
		static float angle;
		static char face;
		static int num;

		Display();
		~Display();
		void	getshader();
		void	buffervertexsetup();
		void	initbufmatrix();
		void	getmatrix();
		void	loop();
		void	buildCube();
		void	keyholds(GLFWwindow *window);
		void	rotate();
		static void	processinput(GLFWwindow *window, int k, int s, int a, int m);


};

char		*filetostr(char *filename);
void	mult(float *a, float *b, float *p);

#endif
