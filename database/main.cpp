#include "Cube.hpp"
#include "Solver.hpp"
#include "rubik.hpp"
#include <fstream>

ofstream ofs;
map<int64_t, string> phaseHash[5];

int main(){
	Cube solverCube;
	Solver s(solverCube);
	string name = "phase ";
	for (int phase = 1; phase <= 4; phase++){
		name[5] = '0' + phase;
		ofs.open(name);
		int i = 0;
		queue<Cube> queue;
		queue.push(solverCube);
		s.BFS(0, queue);
		solverCube.getColor();
		cout << YELLO << "Phase " << phase << " completed." << endl;
		solverCube.path = "";
		ofs.close();
	}
	cout << GREEN << "Database files saved!" << endl;
}
