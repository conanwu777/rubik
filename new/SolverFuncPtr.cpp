#include "Solver.hpp"
#include <fstream>

map<int64_t, string> phaseHash;
char moves[6] = {'F','R','U','B','L','D'};
int phase = 1;

Solver::Solver(Cube c) {
	Cube tmp;

	startTime = std::chrono::duration_cast<std::chrono::milliseconds>
	(std::chrono::system_clock::now().time_since_epoch());
	for (int i = 0; i < 18; i++)
		allowedMoves[i] = 1;
	for (int i = 1 ; i <= 4; i++)
		phaseGoal[i] = getPhaseId(tmp, i);
	readData("../database/phase1");
}

void	Solver::readData(std::string file)
{
	ifstream input(file);
	int64_t hash;
	string moves;
	while (input >> hash >> moves)
		phaseHash[hash] = moves;
}

// int		max(int64_t a, int64_t b, int64_t c){
// 	int64_t num = a;
// 	if (num < b)
// 		num = b;
// 	if (num < c)
// 		num = c;
// 	return num;
// }

void Solver::nextPhase(){
	phaseHash.clear();
	switch (phase){
		case 1:
			allowedMoves[0] = 0;
			allowedMoves[2] = 0;
			allowedMoves[9] = 0;
			allowedMoves[11] = 0;
			readData("../database/phase2");
			break;
		case 2:
			// RL
			allowedMoves[3] = 0;
			allowedMoves[5] = 0;
			allowedMoves[12] = 0;
			allowedMoves[14] = 0;
			readData("../database/phase3");
			break;
		case 3:
			// UD
			allowedMoves[6] = 0;
			allowedMoves[8] = 0;
			allowedMoves[15] = 0;
			allowedMoves[17] = 0;
			readData("../database/phase4");
	}
	phase++;
}

int64_t	Solver::idPhase1(Cube c){
	int64_t id = 0; 
	for (int i = 0; i < 12; i++)
	{
		id <<= 1;
		id += c.eOri[i];
	}
	return id;
}

int64_t	Solver::idPhase2(Cube c){
	int64_t id = 0; 
	for (int i = 0; i < 8; i++)
	{
		id <<= 2;
		id += c.cOri[i];
	}
	for (int i = 0; i < 12; i++){
		id <<= 1;
		if (c.ePos[i] < 8)
			id++;
	}
	return id;
}

int64_t	Solver::idPhase3(Cube c){
	string faces = "FRUBLD";

	int64_t id = 0; 
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 3; j++){
			id <<= 1;
			char t = c.cornerNames[c.cPos[i]][(c.cOri[i] + j) % 3];
			if (!(t == c.cornerNames[i][j] ||
				t == faces[(faces.find(c.cornerNames[i][j]) + 3) % 6])){
				id++;
			}
		}			
	}
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 2; j++){
			id <<= 1;
			char t = c.edgeNames[c.ePos[i]][(c.eOri[i] + j) % 2];
			if (!(t == c.edgeNames[i][j] ||
				t == faces[(faces.find(c.edgeNames[i][j]) + 3) % 6])){
				id++;
			}
		}			
	}
	for (int i = 0; i < 8; i++)
	{
		id <<= 1;
		if (c.cPos[i] != i && c.cPos[i] != (i + 4) % 8)
			id++;
	}
	id <<= 1;
	for (int i = 0; i < 8; i++ )
		for( int j = i + 1; j < 8; j++ )
	id ^= c.cPos[i] > c.cPos[j];
	return id;
}

int64_t	Solver::idPhase4(Cube c){
	string faces = "FRUBLD";
	
	int64_t id = 0; 
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 3; j++){
			id <<= 1;
			char t = c.cornerNames[c.cPos[i]][(c.cOri[i] + j) % 3];
			if (t == faces[(faces.find(c.cornerNames[i][j]) + 3) % 6]){
				id++;
			}
		}			
	}
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 2; j++){
			id <<= 1;
			char t = c.edgeNames[c.ePos[i]][(c.eOri[i] + j) % 2];
			if (t == faces[(faces.find(c.edgeNames[i][j]) + 3) % 6]){
				id++;
			}
		}			
	}
	return id;
}

int64_t Solver::getPhaseId(Cube c, int phase){
	int64_t id = 0;
	
	id = (*this.*(idPhase[phase - 1]))(c);
	return id;
}
