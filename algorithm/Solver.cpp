#include "Solver.hpp"
#include <fstream>

Solver::Solver(Cube c) {

	readData("../database/CornerDatabase", corners);
	readData("../database/TopEdgeDatabase", topEdges);
	readData("../database/BotEdgeDatabase", botEdges);
	cout << GREEN << "Database import complete!\n";
}

void	Solver::readData(std::string file, unordered_map<int64_t, int> &map){
	std::ifstream input(file);

	int64_t hash;
	int moves;
	while (input >> hash >> moves){
		map[hash] = moves;
	}
}

char moves[6] = {'F','R','U','B','L','D'};

int		max(int64_t a, int64_t b, int64_t c){
	int64_t num = a;
	if (num < b)
		num = b;
	if (num < c)
		num = c;
	return num;
}

bool	Solver::DFS(Cube c, int step, int maxStep)
{	
	for (int move = 0; move < 6; move++)
	{
		for (int amount = 0; amount < 3; amount++)
		{
			c.rotCube(moves[move], 1);
			int64_t hashC = getCornerHash(c);
			int64_t hashB = getBotHash(c);
			int64_t hashT = getTopHash(c);
			if (!(hashC = corners[hashC]))
				hashC = 6;
			if (!(hashT = topEdges[hashT]))
				hashT = 7;
			if (!(hashB = botEdges[hashB]))
				hashB = 7;
			int num = hashB + hashT + hashC;
			if (num == 0){
				cout << "PERFECT BOY FOUND !!\n";
				cout << moves[move] << amount + 1 << endl;

				return 1;
			}
			if (num + step <= maxStep){
				if (DFS(c, step + 1, maxStep)){
					cout << moves[move] << amount + 1 << endl;
					return 1;
				}
			}
		}
		c.rotCube(moves[move], 1);
	}
	return 0;
}
