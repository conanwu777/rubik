#include "Cube.hpp"
#include "Solver.hpp"
#include "Display.hpp"
#include "Rubik.hpp"

Cube cube;

string translate(string path)
{
	string ret;

	for (int i = 0; path[i]; i++)
	{
		if (path[i] == '1')
			ret += " ";
		else if (path[i] == '3')
			ret += "\' ";
		else if (path[i] == '2')
			ret += "2 ";
		else
			ret += path[i];
	}
	return ret;
}

int main(int ac, char **av){
	char	face;
	int		num;

	string output;
	Cube solverCube;
	if (ac < 2){
		cout << RED << "Cube not shuffled.\n";
	}
	if (ac >= 2)
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
	cube.getColor();
	cout << GREEN << "Cube shuffle complete!\n";
	Display display;
	if (ac == 2 || strcmp(av[2], "-m"))
	{
		solverCube = cube;
		Solver s(solverCube);
		for (int phase = 1; phase <= 4; phase++){
			int i = 0;

			string path = phaseHash[s.getPhaseId(solverCube, phase)];
			cout << path << endl;
			if (path[0] != 'E')
				output.append(path);
			while (!path.empty() && path[0] != 'E')
			{
				face = path[0];
				num = path[1] - '0';
				solverCube.rotCube(face, num);
				path = path.substr(2);
			}
			s.nextPhase();
		}
		cout << GREEN << "Final output:" << endl;
		cout << WHITE << translate(output) << endl;
		cout << GREEN << "Total steps: " << WHITE << output.size() / 2 << endl;
		cout << GREEN << "Time to find solution: " << WHITE
		<< static_cast<float>(s.time.count()) / 1000 << " seconds\n";
		display.waitlist.append(output);
	}
	while (!glfwWindowShouldClose(display.window))
		display.loop();
}
