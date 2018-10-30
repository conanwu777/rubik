#include "Cube.hpp"

Cube::Cube(){
	level = 0;
}

Cube::~Cube(){
}

void	Cube::rotCube(char c, int amount){
	switch (c){
		case 'F':
			rotFront(amount);
		case 'R':
			rotRight(amount);
		case 'U':
			rotUp(amount);
		case 'B':
			rotBack(amount);
		case 'L':
			rotLeft(amount);
		case 'D':
			rotDown(amount);
	}
}


void	Cube::rotUp(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[3];
		cPos[3] = cPos[2];
		cPos[2] = cPos[1];
		cPos[1] = cPos[0];
		cPos[0] = tmp;
		
		char tOri = cOri[3];
		cOri[3] = cOri[0];
		cOri[0] = cOri[1];
		cOri[1] = cOri[2];
		cOri[2] = tOri;

		tOri = eOri[0];
		eOri[0] = eOri[3];
		eOri[3] = eOri[2];
		eOri[2] = eOri[1];
		eOri[1] = tOri;

		edge tmp2 = ePos[0];
		ePos[0] = ePos[1];
		ePos[1] = ePos[2];
		ePos[2] = ePos[3];
		ePos[3] = tmp2;
	}
}
		
void	Cube::rotDown(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[7];
		cPos[7] = cPos[6];
		cPos[6] = cPos[5];
		cPos[5] = cPos[4];
		cPos[4] = tmp;

		char tOri = cOri[4];
		cOri[4] = cOri[7];
		cOri[7] = cOri[6];
		cOri[6] = cOri[5];
		cOri[5] = tOri;

		tOri = eOri[11];
		eOri[11] = eOri[8];
		eOri[8] = eOri[9];
		eOri[9] = eOri[10];
		eOri[10] = tOri;

		edge tmp2 = ePos[8];
		ePos[8] = ePos[9];
		ePos[9] = ePos[10];
		ePos[10] = ePos[11];
		ePos[11] = tmp2;
	}
}

void	Cube::rotLeft(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[0];
		cPos[0] = cPos[3];
		cPos[3] = cPos[4];
		cPos[4] = cPos[5];
		cPos[5] = tmp;

		char tOri = cOri[0];
		cOri[0] = (2 + cOri[3]) % 3;
		cOri[3] = (1 + cOri[4]) % 3;
		cOri[4] = (2 + cOri[5]) % 3;
		cOri[5] = (1 + tOri) % 3;

		tOri = eOri[7];
		eOri[7] = 1 - eOri[3];
		eOri[3] = 1 - eOri[4];
		eOri[4] = 1 - eOri[11];
		eOri[11] = 1 - tOri;

		edge tmp2 = ePos[7];
		ePos[7] = ePos[3];
		ePos[3] = ePos[4];
		ePos[4] = ePos[11];
		ePos[11] = tmp2;
	}
}

void	Cube::rotRight(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[2];
		cPos[2] = cPos[1];
		cPos[1] = cPos[6];
		cPos[6] = cPos[7];
		cPos[7] = tmp;

		char tOri = cOri[2];
		cOri[2] = (2 + cOri[1]) % 3;
		cOri[1] = (1 + cOri[6]) % 3;
		cOri[6] = (2 + cOri[7]) % 3;
		cOri[7] = (1 + tOri) % 3;

		tOri = eOri[1];
		eOri[1] = 1 - eOri[6];
		eOri[6] = 1 - eOri[9];
		eOri[9] = 1 - eOri[5];
		eOri[5] = 1 - tOri;

		edge tmp2 = ePos[5];
		ePos[5] = ePos[1];
		ePos[1] = ePos[6];
		ePos[6] = ePos[9];
		ePos[9] = tmp2;
	}
}

void	Cube::rotFront(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[5];
		cPos[5] = cPos[6];
		cPos[6] = cPos[1];
		cPos[1] = cPos[0];
		cPos[0] = tmp;

		char tOri = cOri[1];
		cOri[1] = (2 + cOri[0]) % 3;
		cOri[0] = (1 + cOri[5]) % 3;
		cOri[5] = (2 + cOri[6]) % 3;
		cOri[6] = (1 + tOri) % 3;

		tOri = eOri[6];
		eOri[6] = eOri[2];
		eOri[2] = eOri[7];
		eOri[7] = eOri[10];
		eOri[10] = tOri;

		edge tmp2 = ePos[6];
		ePos[6] = ePos[2];
		ePos[2] = ePos[7];
		ePos[7] = ePos[10];
		ePos[10] = tmp2;
	}
}

void	Cube::rotBack(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[3];
		cPos[3] = cPos[2];
		cPos[2] = cPos[7];
		cPos[7] = cPos[4];
		cPos[4] = tmp;

		char tOri = cOri[3];
		cOri[3] = (2 + cOri[2]) % 3;
		cOri[2] = (1 + cOri[7]) % 3;
		cOri[7] = (2 + cOri[4]) % 3;
		cOri[4] = (1 + tOri) % 3;

		tOri = eOri[4];
		eOri[4] = eOri[0];
		eOri[0] = eOri[5];
		eOri[5] = eOri[8];
		eOri[8] = tOri;

		edge tmp2 = ePos[4];
		ePos[4] = ePos[0];
		ePos[0] = ePos[5];
		ePos[5] = ePos[8];
		ePos[8] = tmp2;
	}
}
