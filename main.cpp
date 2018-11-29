#include "Cube.hpp"
#include "Solver.hpp"
#include "Display.hpp"
#include "Rubik.hpp"

Cube cube;

void printExplanation(int phase)
{
	cout << YELLO << "Now doing phase " << phase << " :" << endl;
	switch (phase){
		case 1:
			cout << WHITE << "First, make sure all edge pieces are correctly oriented" << endl;
			cout << "\ti.e. it takes even number of moves to bring each edge to it's goal position\n";
			cout << ORANGE << "Target subgroup : <F2, B2, L, R, U, D>\n";
			break ;
		case 2:
			cout << WHITE << "Now we make sure all top and bottom colors are in the top and bottom face\n";
			cout << "\ti.e. middle level will only contain edge pieces belonging to the middle\n";
			cout << ORANGE << "Target subgroup : <F2, B2, L2, R2, U, D>\n";
			break ;
		case 3:
			cout << WHITE << "Then we make sure all faces only have its own color or color of the opposite side\n";
			cout << "\tin addition, overall number of swapped edge pieces must be even\n";
			cout << "\tand coner pieces must be either in place or swapped in specific pairs\n";
			cout << ORANGE << "Target subgroup : <F2, B2, L2, R2, U2, D2>\n";
			break ;
		default:
			cout << WHITE << "Finally, we solve the remaining with only half-turns!\n";
			cout << ORANGE << "Target subgroup : {I}\n";
			break ;
	}
}

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

string mergeExtras(string moves){
	char prev = 0;
	int num = 0;
	string out = "";
	for (int i = 0; i < moves.size(); i+=2){
		if (moves[i] == prev){
			num = (num + moves[i + 1] - '0') % 4;
			out = out.substr(0,out.size() - 2);
		}
		else{
			prev = moves[i];
			num = moves[i + 1] - '0';
		}
		if (num != 0){
			out += moves[i];
			out += (num + '0');
		}
		else{
			prev = 0;
		}
	}
	return out;
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

void hashSolve(Cube *solverCube, Solver *s, string *output, Display *display)
{
	char	face;
	int		num;
	int		i = 0;
	Cube 	c;
	for (int phase = 1; phase <= 4; phase++)
	{
		printExplanation(phase);
		cout << YELLO << "Phase moves: " << endl;
		while (s->getPhaseId(*solverCube, phase) != s->phaseGoal[phase])
		{
			string path = phaseHash[phase -1][s->getPhaseId(*solverCube, phase)];
			if (path == "")
			{
				cout << RED << "Solution not found" << endl;
				exit(1);				
			}
			cout << WHITE << '\t' << translate(path) << endl;
			if (path[0] != 'E')
			{
				display->waitlist.append(path + '+');
				output->append(path);
				while (!path.empty())
				{
					face = path[0];
					num = path[1] - '0';
					solverCube->rotCube(face, num);
					path = path.substr(2);
				}
			}
		}
		if (*solverCube == c)
			return ;
		s->nextPhase();
	}
}

void bfsSolve(Cube *solverCube, Solver *s, string *output, Display *display)
{
	for (int phase = 1; phase <= 4; phase++)
	{
		printExplanation(phase);
		int i = 0;
		queue<Cube> queue;
		queue.push(*solverCube);
		*solverCube = s->BFS(0, queue);
		solverCube->getColor();
		output->append(solverCube->path);
		display->waitlist.append(solverCube->path + '+');
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
			bfsSolve(&solverCube, &s, &output, &display);
		else
			hashSolve(&solverCube, &s, &output, &display);
		chrono::milliseconds time
		= chrono::duration_cast<chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()) - startTime;
		cout << GREEN << "Final output:" << endl;
		cout << WHITE << translate(mergeExtras(output)) << endl;
		cout << GREEN << "Total steps: " << WHITE << mergeExtras(output).size() / 2 << endl;
		cout << GREEN << "Time to find solution: " << WHITE
		<< static_cast<float>(time.count()) / 1000 << " seconds\n";
	}
	while (!glfwWindowShouldClose(display.window))
		display.loop();
}
