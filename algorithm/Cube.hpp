#ifndef CUBE_HPP
# define CUBE_HPP

# include "rubik.hpp"

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
		int level = 0;
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