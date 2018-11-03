#include "Cube.hpp"
#include "Display.hpp"

Cube cube;

char		*filetostr(char *filename)
{
	char	buf[1000];
	char	*ret;
	FILE	*ptr;
	int		i;

	ret = (char*)calloc(1000, 1);
	ptr = fopen(filename, "r");
	i = 0;
	while (fgets(buf, 999, ptr))
	{
		ret = (char*)realloc(ret, strlen(ret) + strlen(buf) + 1);
		strcpy(ret + i, buf);
		i += strlen(buf);
	}
	fclose(ptr);
	return (ret);
}

void	mult(float *a, float *b, float *p)
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			p[i * 4 + j] = 0;
			k = -1;
			while (++k < 4)
				p[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
		}
	}
}

struct disp {
	char key;
	void	(Cube::*func)(int);
};

disp	rotMethods[] = {
	{'F', &Cube::rotFront},
	{'R', &Cube::rotRight},
	{'U', &Cube::rotUp},
	{'B', &Cube::rotBack},
	{'L', &Cube::rotLeft},
	{'D', &Cube::rotDown},
};

int main(int ac, char **av){
	Display display;
	if (ac < 2){
		cout << RED << "Cube not shuffled.\n";
	}
	// if (ac == 2)
	// 	for (int i = 0; av[1][i]; i++)
	// 		if (av[1][i] == 'F' || av[1][i] == 'R' || av[1][i] == 'U' ||
	// 			av[1][i] == 'B' || av[1][i] == 'L' || av[1][i] == 'D')
	// 		{
	// 			int num = 1;
	// 			if (av[1][i + 1] == '\'')
	// 				num = 3;
	// 			else if (av[1][i + 1] == '2')
	// 				num = 2;
	// 			cube.rotCube(av[1][i], num);
	// 		}
	// cout << GREEN << "Cube shuffle complete!\n";

	display.waitlist.append(av[1]);
	while (!glfwWindowShouldClose(display.window))
		display.loop();
}
