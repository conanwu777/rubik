#ifndef CUBE_HPP
#define CUBE_HPP
#include <iostream>
#include <map>

using namespace std;

enum corner {ufl, urf, ubr, ulb, dbl, dlf, dfr, drb}; //STARTS at 0
enum edge {ub, ur, uf, ul, bl, br, fr, fl, db, dr, df, dl}; //STARTS at 0


class Cube{
	private:
		map<corner, char[3]> cornerCubie;
		map<edge, char[2]> edgeCubie;
		char	cornerFace(corner c, int offset);
		char	edgeFace(edge e, int offset);
	public:
		corner cPos[8] = {ufl, urf, ubr, ulb, dbl, dlf, dfr, drb};
		char cOri[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		edge ePos[12] = {ub, ur, uf, ul, bl, br, fr, fl, db, dr, df, dl};
		char eOri[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int level;
		string colorTabEncode = "UFRDBL";
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