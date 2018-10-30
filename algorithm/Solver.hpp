#ifndef SOLVER_HPP
# define SOLVER_HPP

# include "rubik.hpp"
# include "Cube.hpp"
# include <iomanip>
# include <unistd.h>
# include <queue>
# include <vector>
# include <unordered_set>
# include <chrono>

# define PTR std::shared_ptr<Cube>
# define MPTR(y) std::make_shared<Cube>(y)


class Solver
{
	public:
		unordered_map<int64_t, int> corners;
		unordered_map<int64_t, int> topEdges;
		unordered_map<int64_t, int> botEdges;
		int size;
		PTR st;
		PTR end;
		char flag;
		char heur;
		bool	DFS(Cube c, int step, int maxStep);
		Solver(Cube c);
		void	readData(std::string file, unordered_map<int64_t, int> &map);
		void	printBoard(PTR b);
};

#endif