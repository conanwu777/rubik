#ifndef SOLVER_HPP
# define SOLVER_HPP

# include "rubik.hpp"
# include "Cube.hpp"
# include <iomanip>
# include <unistd.h>
# include <queue>
# include <unordered_set>
# include <chrono>

# define PTR std::shared_ptr<Cube>
# define MPTR(y) std::make_shared<Cube>(y)

class Solver
{
	public:
		bool allowedMoves[18];
		unordered_set<int> middleSlice = {fr, fl, bl, br};
		int64_t phaseGoal[5];
		int size;
		PTR st;
		PTR end;
		char flag;
		char heur;
		Cube	BFS(int step, queue<Cube>);
		int64_t 	getPhaseId(Cube c, int phase);
		void	nextPhase();
		Solver(Cube c);
		void	readData(std::string file, unordered_map<int64_t, int> &map);
		void	printBoard(PTR b);
};

#endif