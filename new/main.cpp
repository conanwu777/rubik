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

void shuffle(int ac, char **av)
{
	if (ac == 1 || ac > 3){
		cout << ORANGE << "Usage: Rubik \"shuffle string\" [-m | -r]\n";
		cout << "\tShuffle string: F B U D L R with variations F F' F2\n";
		cout << "\t-m: manually solve the cube with user input\n";
		cout << "\t-r: solve the cube without hashing\n";
		exit(1);
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
}

void hashSolve(Cube *solverCube, Solver *s, string *output)
{
	char	face;
	int		num;
	int		i = 0;
	Cube 	c;
	for (int phase = 1; phase <= 4; phase++)
	{
		while (s->getPhaseId(*solverCube, phase) != s->phaseGoal[phase])
		{
			string path = phaseHash[s->getPhaseId(*solverCube, phase)];
			if (path == "")
			{
				cout << RED << "Solution not found" << endl;
				exit(1);				
			}
			cout << YELLO << "Phase " << phase << " completed: " << endl;
			cout << WHITE << '\t' << translate(path) << endl;
			if (path[0] != 'E')
			{
				output->append(path);
				while (!path.empty())
				{
					face = path[0];
					num = path[1] - '0';
					solverCube->rotCube(face, num);
					cout << "id: " << s->getPhaseId(*solverCube, phase) << endl;
					path = path.substr(2);
				}
			}
		}
		if (*solverCube == c)
			return ;
		s->nextPhase();
	}
}

void bfsSolve(Cube *solverCube, Solver *s, string *output)
{
	for (int phase = 1; phase <= 4; phase++)
	{
		int i = 0;
		queue<Cube> queue;
		queue.push(*solverCube);
		*solverCube = s->BFS(0, queue);
		solverCube->getColor();
		output->append(solverCube->path);
		cout << YELLO << "Phase " << phase << " completed: " << endl;
		cout << WHITE << '\t' << translate(solverCube->path) << endl;
		solverCube->path = "";
	}
}

int main(int ac, char **av){
	shuffle(ac, av);
	string output;
	Cube solverCube;
	Display display;
	if (ac == 2 || strcmp(av[2], "-m"))
	{
		chrono::milliseconds startTime
		= chrono::duration_cast<chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch());
		solverCube = cube;
		Solver s(solverCube);
		if (ac == 3 && !strcmp(av[2], "-r"))
			bfsSolve(&solverCube, &s, &output);
		else
			hashSolve(&solverCube, &s, &output);
		chrono::milliseconds time
		= chrono::duration_cast<chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()) - startTime;
		cout << GREEN << "Final output:" << endl;
		cout << WHITE << translate(output) << endl;
		cout << GREEN << "Total steps: " << WHITE << output.size() / 2 << endl;
		cout << GREEN << "Time to find solution: " << WHITE
		<< static_cast<float>(time.count()) / 1000 << " seconds\n";
		display.waitlist.append(output);
	}
	while (!glfwWindowShouldClose(display.window))
		display.loop();
}
