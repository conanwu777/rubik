#ifndef CUBE_HPP
#define CUBE_HPP
#include <iostream>
#include <map>

using namespace std;

enum corner {ufl, urf, ubr, ulb, dbl, dlf, dfr, drb}; //STARTS at 0
enum edge {ub, ur, uf, ul, lb, rb, rf, lf, db, dr, df, dl}; //STARTS at 0
enum cubies 
	{DBL, DCL, DFL, CBL, CCL, CFL, UBL, UCL, UFL,
	DBC, DCC, DFC, CBC, CFC, UBC, UCC, UFC,
	DBR, DCR, DFR, CBR, CCR, CFR, UBR, UCR, UFR};
enum faces {right = 0, back = 6, front = 12, left = 18, down = 24, up = 30};

struct position{
	int x, y;
};

class Cube{
	private:
		map<corner, char[3]> cornerCubie;
		map<edge, char[2]> edgeCubie;
		char	cornerFace(corner c, int offset);
		char	edgeFace(edge e, int offset);
	public:
		corner cPos[8] = {ufl, urf, ubr, ulb, dbl, dlf, dfr, drb};
		char cOri[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		edge ePos[12] = {ub, ur, uf, ul, lb, rb, rf, lf, db, dr, df, dl};
		char eOri[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int level;
		char color[54];
		Cube();
		~Cube();
		void	rotCube(char c, int num);
		void	rotUp(int);
		void	rotDown(int);
		void	rotLeft(int);
		void	rotRight(int);
		void	rotFront(int);
		void	rotBack(int);
		void	print();
};

#endif