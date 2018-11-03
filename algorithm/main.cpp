#include "Cube.hpp"
#include "Solver.hpp"
#include "Display.hpp"
#include "Rubik.hpp"

Cube cube;

int main(int ac, char **av){
	Cube solverCube;
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
	solverCube = cube;
	cout << GREEN << "Cube shuffle complete!\n";
	Display display;
	Solver s(solverCube);

	for (int phase = 1; phase <= 4; phase++){
		int i = 0;
		queue<Cube> queue;
		queue.push(solverCube);
		solverCube = s.BFS(0, queue);
		cout << "path: " << solverCube.path << endl;
	}
	solverCube.print();
	display.waitlist.append(solverCube.path);
	// display.waitlist.append("U1");
	while (!glfwWindowShouldClose(display.window))
		display.loop();
}
