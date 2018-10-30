#include "Cube.hpp"
#include "Display.hpp"

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

// int main()
// {
// 	Cube cube;

// 	cube.print();
// 	cube.rotDown(1);
// 	cube.print();

// 	cube.rotUp(1);
// 	cube.print();

// 	cube.rotLeft(1);
// 	cube.print();

// 	cube.rotRight(1);
// 	cube.print();

// 	cube.rotFront(1);
// 	cube.print();

// 	cube.rotBack(1);
// 	cube.print();

// 	cube.rotBack(3);
// 	cube.print();

// 	cube.rotFront(3);
// 	cube.print();

// 	cube.rotRight(3);
// 	cube.print();

// 	cube.rotLeft(3);
// 	cube.print();

// 	cube.rotUp(3);
// 	cube.print();

// 	cube.rotDown(3);
// 	cube.print();
// }

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

	Cube cube;

	if (ac < 2){
		printf("Cube not shuffled.");
		return 0;
	}

	for (int i = 0; i < av[1][i]; i++)
		for (int j = 0; j < 6; j++)
			if (av[1][i] == 'F' || av[1][i] == 'R' || av[1][i] == 'U' ||
				av[1][i] == 'B' || av[1][i] == 'L' || av[1][i] == 'D')
			{
				int num = 1;
				if (av[1][i + 1] == '\'')
					num = 3;
				else if (av[1][i + 1] == '2')
					num = 2;
				cube.rotCube(j, num);
			}
	cube.print();
}
