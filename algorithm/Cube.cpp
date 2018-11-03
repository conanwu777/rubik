#include "Cube.hpp"

Cube::Cube(){
	path = "";
	for (char c = 0; c < 6; c++)
		for (int i = 0; i < 9; i++)
			color[c * 9 + i] = colorTabEncode[c];
}

Cube& Cube::operator=(const Cube& a){
	for (int i = 0; i < 8; i++){
		cPos[i] = a.cPos[i];
		cOri[i] = a.cOri[i];
	}
	for (int i = 0; i < 12; i++){
		ePos[i] = a.ePos[i];
		eOri[i] = a.eOri[i];
	}
	path = a.path;
	return *this;
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
		corner tmp = cPos[urf];
		cPos[urf] = cPos[ubr];
		cPos[ubr] = cPos[ulb];
		cPos[ulb] = cPos[ufl];
		cPos[ufl] = tmp;
		
		char tOri = cOri[urf];
		cOri[urf] = cOri[ubr];
		cOri[ubr] = cOri[ulb];
		cOri[ulb] = cOri[ufl];
		cOri[ufl] = tOri;

		tOri = eOri[ub];
		eOri[ub] = eOri[ul];
		eOri[ul] = eOri[uf];
		eOri[uf] = eOri[ur];
		eOri[ur] = tOri;

		edge tmp2 = ePos[ub];
		ePos[ub] = ePos[ul];
		ePos[ul] = ePos[uf];
		ePos[uf] = ePos[ur];
		ePos[ur] = tmp2;
	}
}
		
void	Cube::rotDown(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[dfr];
		cPos[dfr] = cPos[dlf];
		cPos[dlf] = cPos[dbl];
		cPos[dbl] = cPos[drb];
		cPos[drb] = tmp;

		char tOri = cOri[dfr];
		cOri[dfr] = cOri[dlf];
		cOri[dlf] = cOri[dbl];
		cOri[dbl] = cOri[drb];
		cOri[drb] = tOri;

		tOri = eOri[df];
		eOri[df] = eOri[dl];
		eOri[dl] = eOri[db];
		eOri[db] = eOri[dr];
		eOri[dr] = tOri;

		edge tmp2 = ePos[df];
		ePos[df] = ePos[dl];
		ePos[dl] = ePos[db];
		ePos[db] = ePos[dr];
		ePos[dr] = tmp2;
	}
}

void	Cube::rotLeft(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[dlf];
		cPos[dlf] = cPos[ufl];
		cPos[ufl] = cPos[ulb];
		cPos[ulb] = cPos[dbl];
		cPos[dbl] = tmp;

		char tOri = cOri[dlf];
		cOri[dlf] = (2 + cOri[ufl]) % 3;
		cOri[ufl] = (1 + cOri[ulb]) % 3;
		cOri[ulb] = (2 + cOri[dbl]) % 3;
		cOri[dbl] = (1 + tOri) % 3;

		tOri = eOri[bl];
		eOri[bl] = eOri[dl];
		eOri[dl] = eOri[fl];
		eOri[fl] = eOri[ul];
		eOri[ul] = tOri;

		edge tmp2 = ePos[bl];
		ePos[bl] = ePos[dl];
		ePos[dl] = ePos[fl];
		ePos[fl] = ePos[ul];
		ePos[ul] = tmp2;
	}
}

void	Cube::rotRight(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[urf];
		cPos[urf] = cPos[dfr];
		cPos[dfr] = cPos[drb];
		cPos[drb] = cPos[ubr];
		cPos[ubr] = tmp;

		char tOri = cOri[urf];
		cOri[urf] = (2 + cOri[dfr]) % 3;
		cOri[dfr] = (1 + cOri[drb]) % 3;
		cOri[drb] = (2 + cOri[ubr]) % 3;
		cOri[ubr] = (1 + tOri) % 3;

		tOri = eOri[fr];
		eOri[fr] = eOri[dr];
		eOri[dr] = eOri[br];
		eOri[br] = eOri[ur];
		eOri[ur] = tOri;

		edge tmp2 = ePos[fr];
		ePos[fr] = ePos[dr];
		ePos[dr] = ePos[br];
		ePos[br] = ePos[ur];
		ePos[ur] = tmp2;
	}
}

void	Cube::rotFront(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[urf];
		cPos[urf] = cPos[ufl];
		cPos[ufl] = cPos[dlf];
		cPos[dlf] = cPos[dfr];
		cPos[dfr] = tmp;

		char tOri = cOri[urf];
		cOri[urf] = (2 + cOri[ufl]) % 3;
		cOri[ufl] = (1 + cOri[dlf]) % 3;
		cOri[dlf] = (2 + cOri[dfr]) % 3;
		cOri[dfr] = (1 + tOri) % 3;

		tOri = eOri[uf];
		eOri[uf] = 1 - eOri[fl];
		eOri[fl] = 1 - eOri[df];
		eOri[df] = 1 - eOri[fr];
		eOri[fr] = 1 - tOri;

		edge tmp2 = ePos[uf];
		ePos[uf] = ePos[fl];
		ePos[fl] = ePos[df];
		ePos[df] = ePos[fr];
		ePos[fr] = tmp2;
	}
}

void	Cube::rotBack(int amount){
	if (amount == -1)
		amount = 3;

	for (int i = 0; i < amount; i++){
		corner tmp = cPos[ulb];
		cPos[ulb] = cPos[ubr];
		cPos[ubr] = cPos[drb];
		cPos[drb] = cPos[dbl];
		cPos[dbl] = tmp;

		char tOri = cOri[ulb];
		cOri[ulb] = (2 + cOri[ubr]) % 3;
		cOri[ubr] = (1 + cOri[drb]) % 3;
		cOri[drb] = (2 + cOri[dbl]) % 3;
		cOri[dbl] = (1 + tOri) % 3;

		tOri = eOri[br];
		eOri[br] = 1 - eOri[db];
		eOri[db] = 1 - eOri[bl];
		eOri[bl] = 1 - eOri[ub];
		eOri[ub] = 1 - tOri;

		edge tmp2 = ePos[br];
		ePos[br] = ePos[db];
		ePos[db] = ePos[bl];
		ePos[bl] = ePos[ub];
		ePos[ub] = tmp2;
	}
}

char	Cube::cornerFace(corner c, int offset)
{
	return (cornerNames[cPos[c]][(offset + cOri[c]) % 3]);
}

char	Cube::edgeFace(edge e, int offset)
{
	return (edgeNames[ePos[e]][(offset + eOri[e]) % 2]);
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

	int i = 0;
	cout << "Front face\n";
	cout << cornerFace(ufl, 1) << edgeFace(uf, 1) << cornerFace(urf, 2) << endl;
	cout << edgeFace(fl, 0) << 'F' << edgeFace(fr, 0) << endl;
	cout << cornerFace(dlf, 2) << edgeFace(df, 1) << cornerFace(dfr, 1) << endl;

	cout << "\nRight face\n";
	cout << cornerFace(urf, 1) << edgeFace(ur, 1) << cornerFace(ubr, 2) << endl;
	cout << edgeFace(fr, 1) << 'R' << edgeFace(br, 1) << endl;
	cout << cornerFace(dfr, 2) << edgeFace(dr, 1) << cornerFace(drb, 1) << endl;

	cout << "\nLeft face\n";
	cout << cornerFace(ulb, 1) << edgeFace(ul, 1) << cornerFace(ufl, 2) << endl;
	cout << edgeFace(bl, 1) << 'L' << edgeFace(fl, 1) << endl;
	cout << cornerFace(dbl, 2) << edgeFace(dl, 1) << cornerFace(dlf, 1) << endl;

	cout << "\nUp face\n";
	cout << cornerFace(ulb, 0) << edgeFace(ub, 0) << cornerFace(ubr, 0) << endl;
	cout << edgeFace(ul, 0) << 'U' << edgeFace(ur, 0) << endl;
	cout << cornerFace(ufl, 0) << edgeFace(uf, 0) << cornerFace(urf, 0) << endl;

	cout << "\nDown face\n";
	cout << cornerFace(dbl, 0) << edgeFace(db, 0) << cornerFace(drb, 0) << endl;
	cout << edgeFace(dl, 0) << 'D' << edgeFace(dr, 0) << endl;
	cout << cornerFace(dlf, 0) << edgeFace(df, 0) << cornerFace(dfr, 0) << endl;

	cout << "\nBehind face\n";
	cout << cornerFace(ulb, 2) << edgeFace(ub, 1) << cornerFace(ubr, 1) << endl;
	cout << edgeFace(bl, 0) << 'B' << edgeFace(br, 0) << endl;
	cout << cornerFace(dbl, 1) << edgeFace(db, 1) << cornerFace(drb, 2) << endl;

	cout << endl << endl;
}
