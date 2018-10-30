#ifndef RUBIK_HPP
# define RUBIK_HPP

# include <iostream>
# include <map>
# include <unordered_map>

using namespace std;

enum corner {ufl, urf, ubr, ulb, dbl, dlf, dfr, drb}; //STARTS at 0
enum edge {ub, ur, uf, ul, lb, rb, rf, lf, db, dr, df, dl}; //STARTS at 0

# define RED "\e[1;38;2;225;20;20m"
# define WHITE "\e[1;38;2;255;251;214m"
# define YELLO "\e[1;38;2;255;200;0m"
# define ORANGE "\e[1;38;2;255;120;10m"
# define GREEN "\e[1;38;2;0;175;117m"

class Cube;

int64_t getCornerHash(Cube c);
int64_t	getTopHash(Cube c);
int64_t	getBotHash(Cube c);

#endif
