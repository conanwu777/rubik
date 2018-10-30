#include "Cube.hpp"
#include "Solver.hpp"

int64_t getCornerHash(Cube c)
{
	int64_t hash = 0;
	for (int i = 0; i < 8; i++){
		hash <<= 3;
		hash += c.cPos[i];
	}
	for (int i = 0; i < 8; i++){
		hash <<= 2;
		hash += c.cOri[i];
	}
	return hash;
}

int64_t	getTopHash(Cube c)
{
	int64_t hash = 0;
	for (int i = 0; i < 6; i++){
		hash <<= 3;
		hash += c.ePos[i];
	}
	for (int i = 0; i < 6; i++){
		hash <<= 2;
		hash += c.eOri[i];
	}
	return hash;
}

int64_t	getBotHash(Cube c)
{
	int64_t hash = 0;
	for (int i = 6; i < 12; i++){
		hash <<= 3;
		hash += c.ePos[i];
	}
	for (int i = 6; i < 12; i++){
		hash <<= 2;
		hash += c.eOri[i];
	}
	return hash;
}

int main(int ac, char **av){

	Cube cube;

	if (ac < 2){
		cout << RED << "Cube not shuffled.\n";
	}
	if (ac == 2)
		for (int i = 0; av[1][i]; i++)
			if (av[1][i] == 'F' || av[1][i] == 'R' || av[1][i] == 'U' ||
				av[1][i] == 'B' || av[1][i] == 'L' || av[1][i] == 'D')
			{
				int num = 1;
				if (av[1][i + 1] == '\'')
					num = 3;
				else if (av[1][i + 1] == '2')
					num = 2;
				cube.rotCube(av[1][i], num);
			}
	cube.print();
	cout << GREEN << "Cube shuffle complete!\n";
	Solver s(cube);

	if (s.corners[getCornerHash(cube)] == 0 && s.botEdges[getBotHash(cube)] == 0
		&& s.topEdges[getTopHash(cube)] == 0)
	{
		cout << ORANGE << "Cube not shuffled...\n";
		return 0;
	}
	int i = 0;
	while (!s.DFS(cube, 0, i))
	{
		cout << "WOW - " << i << endl;
		i++;
	}
}
