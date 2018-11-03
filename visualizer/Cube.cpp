#include "Cube.hpp"

Cube::Cube(){
	strcpy(cornerCubie[ufl], "UFL");
	strcpy(cornerCubie[urf], "URF");
	strcpy(cornerCubie[ubr], "UBR");
	strcpy(cornerCubie[ulb], "ULB");
	strcpy(cornerCubie[dbl], "DBL");
	strcpy(cornerCubie[dlf], "DLF");
	strcpy(cornerCubie[dfr], "DFR");
	strcpy(cornerCubie[drb], "DRB");

	strcpy(edgeCubie[ub], "UB");
	strcpy(edgeCubie[ur], "UR");
	strcpy(edgeCubie[uf], "UF");
	strcpy(edgeCubie[ul], "UL");
	strcpy(edgeCubie[bl], "BL");
	strcpy(edgeCubie[br], "BR");
	strcpy(edgeCubie[fr], "FR");
	strcpy(edgeCubie[fl], "FL");
	strcpy(edgeCubie[db], "DB");
	strcpy(edgeCubie[dr], "DR");
	strcpy(edgeCubie[df], "DF");
	strcpy(edgeCubie[dl], "DL");

	for (char c = 0; c < 6; c++)
		for (int i = 0; i < 9; i++)
			color[c * 9 + i] = colorTabEncode[c];
}

Cube::~Cube(){
}

void	Cube::rotCube(char c, int amount){
	switch (c){
		case 'F':
			rotFront(amount);
			break;
		case 'R':
			rotRight(amount);
			break;
		case 'U':
			rotUp(amount);
			break;
		case 'B':
			rotBack(amount);
			break;
		case 'L':
			rotLeft(amount);
			break;
		case 'D':
			rotDown(amount);
	}
}


void	Cube::rotUp(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[0];
		cPos[0] = cPos[1];
		cPos[1] = cPos[2];
		cPos[2] = cPos[3];
		cPos[3] = tmp;
		
		char tOri = cOri[0];
		cOri[0] = cOri[1];
		cOri[1] = cOri[2];
		cOri[2] = cOri[3];
		cOri[3] = tOri;

		tOri = eOri[3];
		eOri[3] = eOri[2];
		eOri[2] = eOri[1];
		eOri[1] = eOri[0];
		eOri[0] = tOri;

		edge tmp2 = ePos[3];
		ePos[3] = ePos[2];
		ePos[2] = ePos[1];
		ePos[1] = ePos[0];
		ePos[0] = tmp2;
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
		eOri[7] = eOri[3];
		eOri[3] = eOri[4];
		eOri[4] = eOri[11];
		eOri[11] = tOri;

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
		eOri[1] = eOri[6];
		eOri[6] = eOri[9];
		eOri[9] = eOri[5];
		eOri[5] = tOri;

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
		eOri[6] = 1 - eOri[2];
		eOri[2] = 1 - eOri[7];
		eOri[7] = 1 - eOri[10];
		eOri[10] = 1 - tOri;

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
		eOri[4] = 1 - eOri[0];
		eOri[0] = 1 - eOri[5];
		eOri[5] = 1 - eOri[8];
		eOri[8] = 1 - tOri;

		edge tmp2 = ePos[4];
		ePos[4] = ePos[0];
		ePos[0] = ePos[5];
		ePos[5] = ePos[8];
		ePos[8] = tmp2;
	}
}

char	Cube::cornerFace(corner c, int offset)
{
	return (cornerCubie[cPos[c]][(offset + cOri[c]) % 3]);
}

char	Cube::edgeFace(edge e, int offset)
{
	return (edgeCubie[ePos[e]][(offset + eOri[e]) % 2]);
}

void	Cube::print()
{
	int pos = 0;
	color[pos++] = cornerFace(ulb, 0);
	color[pos++] = edgeFace(ub, 0);
	color[pos++] = cornerFace(ubr, 0);
	color[pos++] = edgeFace(ul, 0);
	color[pos++] = 'U';
	color[pos++] = edgeFace(ur, 0);
	color[pos++] = cornerFace(ufl, 0);
	color[pos++] = edgeFace(uf, 0);
	color[pos++] = cornerFace(urf, 0);

	color[pos++] = cornerFace(dlf, 2);
	color[pos++] = edgeFace(fl, 0);
	color[pos++] = cornerFace(ufl, 1);
	color[pos++] = edgeFace(df, 1);
	color[pos++] = 'F';
	color[pos++] = edgeFace(uf, 1);
	color[pos++] = cornerFace(dfr, 1);
	color[pos++] = edgeFace(fr, 0);
	color[pos++] = cornerFace(urf, 2);

	color[pos++] = cornerFace(drb, 1);
	color[pos++] = edgeFace(dr, 1);
	color[pos++] = cornerFace(dfr, 2);
	color[pos++] = edgeFace(br, 1);
	color[pos++] = 'R';	
	color[pos++] = edgeFace(fr, 1);
	color[pos++] = cornerFace(ubr, 2);
	color[pos++] = edgeFace(ur, 1);
	color[pos++] = cornerFace(urf, 1);

	color[pos++] = cornerFace(dbl, 0);
	color[pos++] = edgeFace(db, 0);
	color[pos++] = cornerFace(drb, 0);
	color[pos++] = edgeFace(dl, 0);
	color[pos++] = 'D';
	color[pos++] = edgeFace(dr, 0);
	color[pos++] = cornerFace(dlf, 0);
	color[pos++] = edgeFace(df, 0);
	color[pos++] = cornerFace(dfr, 0);

	color[pos++] = cornerFace(dbl, 1);
	color[pos++] = edgeFace(bl, 0);
	color[pos++] = cornerFace(ulb, 2);
	color[pos++] = edgeFace(db, 1);
	color[pos++] = 'B';
	color[pos++] = edgeFace(ub, 1);
	color[pos++] = cornerFace(drb, 2);
	color[pos++] = edgeFace(br, 0);
	color[pos++] = cornerFace(ubr, 1);

	color[pos++] = cornerFace(dbl, 2);
	color[pos++] = edgeFace(dl, 1);
	color[pos++] = cornerFace(dlf, 1);
	color[pos++] = edgeFace(bl, 1);
	color[pos++] = 'L';
	color[pos++] = edgeFace(fl, 1);
	color[pos++] = cornerFace(ulb, 1);
	color[pos++] = edgeFace(ul, 1);
	color[pos++] = cornerFace(ufl, 2);

}
