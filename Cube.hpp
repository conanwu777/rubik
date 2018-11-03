#ifndef CUBE_HPP
#define CUBE_HPP
#include <iostream>
#include <map>
#include "rubik.hpp"

using namespace std;


enum corner {urf, ubr, dlf, dfr, ulb, ufl, drb, dbl};
enum edge {uf, ur, ub, ul, df, dr, db, dl, fr, br, bl, fl};

class Cube{
	private:
		char	cornerFace(corner c, int offset);
		char	edgeFace(edge e, int offset);
	public:
		corner cPos[8] = {urf, ubr, dlf, dfr, ulb, ufl, drb, dbl};
		char cOri[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		edge ePos[12] = {uf, ur, ub, ul, df, dr, db, dl, fr, br, bl, fl};
		char eOri[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		string cornerNames[8] = {"URF", "UBR", "DLF", "DFR", "ULB", "UFL", "DRB", "DBL"};
		string edgeNames[12] = {"UF", "UR", "UB", "UL", "DF", "DR", "DB", "DL", "FR", "BR", "BL", "FL"};
		string colorTabEncode = "UFRDBL";
		char color[54];
		string path;
		Cube();
		~Cube();
		Cube& 	operator=(const Cube& a);
		bool	operator==(const Cube& a);
		void	rotCube(char c, int num);
		void	rotUp(int);
		void	rotDown(int);
		void	rotLeft(int);
		void	rotRight(int);
		void	rotFront(int);
		void	rotBack(int);
		void	getColor();
};

#endif