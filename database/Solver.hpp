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
		int64_t (Solver::*idPhase[4])(Cube) = {
			&Solver::idPhase1,
			&Solver::idPhase2,
			&Solver::idPhase3,
			&Solver::idPhase4
		};
		int64_t	idPhase1(Cube c);
		int64_t	idPhase2(Cube c);
		int64_t	idPhase3(Cube c);
		int64_t	idPhase4(Cube c);
		Cube	BFS(int step, queue<Cube>);
		int64_t 	getPhaseId(Cube c, int phase);
		void	nextPhase();
		Solver(Cube c);
		void	readData(std::string file, unordered_map<int64_t, int> &map);
		void	printBoard(PTR b);
};

#endif