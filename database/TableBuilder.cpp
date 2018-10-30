#include "rubik.hpp"
#include <queue>
#include <array>
#include <fstream>

ofstream ofs;
map<int64_t, int> corners;
map<int64_t, int> topEdges;
map<int64_t, int> botEdges;

char moves[6] = {'F','R','U','B','L','D'};

bool	inCornerDatabase(Cube c){
	int64_t hash = 0;
	for (int i = 0; i < 8; i++){
		hash <<= 3;
		hash += c.cPos[i];
	}
	for (int i = 0; i < 8; i++){
		hash <<= 2;
		hash += c.cOri[i];
	}
	return corners.find(hash) == corners.end() ? 0 : 1;
}

void	addToCorner(Cube c){
	int64_t hash = 0;

	for (int i = 0; i < 8; i++){
		hash <<= 3;
		hash += c.cPos[i];
	}
	for (int i = 0; i < 8; i++){
		hash <<= 2;
		hash += c.cOri[i];
	}
	corners[hash] = c.level;
	ofs << hash << " " << c.level << endl;
}

bool	inTopEdgeDatabase(Cube c){
	int64_t hash = 0;
	for (int i = 0; i < 6; i++){
		hash <<= 3;
		hash += c.ePos[i];
	}
	for (int i = 0; i < 6; i++){
		hash <<= 2;
		hash += c.eOri[i];
	}
	return corners.find(hash) == corners.end() ? 0 : 1;
}

bool	inBotEdgeDatabase(Cube c){
	int64_t hash = 0;
	for (int i = 6; i < 12; i++){
		hash <<= 3;
		hash += c.ePos[i];
	}
	for (int i = 6; i < 12; i++){
		hash <<= 2;
		hash += c.eOri[i];
	}
	return corners.find(hash) == corners.end() ? 0 : 1;
}

void	addToTopEdge(Cube c){
	int64_t hash = 0;

	for (int i = 0; i < 6; i++){
		hash <<= 3;
		hash += c.ePos[i];
	}
	for (int i = 0; i < 6; i++){
		hash <<= 2;
		hash += c.eOri[i];
	}
	corners[hash] = c.level;
	ofs << hash << " " << c.level << endl;
}

void	addToBotEdge(Cube c){
	int64_t hash = 0;

	for (int i = 6; i < 12; i++){
		hash <<= 3;
		hash += c.ePos[i];
	}
	for (int i = 6; i < 12; i++){
		hash <<= 2;
		hash += c.eOri[i];
	}
	corners[hash] = c.level;
	ofs << hash << " " << c.level << endl;
}

void createTable(void (*addTo)(Cube), bool (*inDatabase)(Cube), int limit)
{
	queue<Cube> queue;
	Cube c;
	addTo(c);

	queue.push(c);
	while(!queue.empty())
	{
		c = queue.front();
		if (c.level == limit)
			break ;
		queue.pop();
		for (int move = 0; move < 6; move++)
		{
			c.level++;
			for (int amount = 0; amount < 3; amount++)
			{
				c.rotCube(moves[move], 1);
				if (!inDatabase(c))
				{
					queue.push(c);
					addTo(c);
				}
			}
			c.level--;
			c.rotCube(moves[move], 1);
		}
	}
}

int main(){
	ofs.open("CornerDatabase");
	createTable(addToCorner, inCornerDatabase, 5);
	ofs.close();
	ofs.open("TopEdgeDatabase");
	createTable(addToTopEdge, inTopEdgeDatabase, 6);
	ofs.close();
	ofs.open("BotEdgeDatabase");
	createTable(addToBotEdge, inBotEdgeDatabase, 6);
	ofs.close();
}
