#ifndef RUBIK_HPP
# define RUBIK_HPP

# include <iostream>
# include <map>
# include <unordered_map>
# include "Cube.hpp"

char	*filetostr(char *filename);
void	mult(float *a, float *b, float *p);

# define RED "\e[1;38;2;225;20;20m"
# define WHITE "\e[1;38;2;255;251;214m"
# define YELLO "\e[1;38;2;255;200;0m"
# define ORANGE "\e[1;38;2;255;120;10m"
# define GREEN "\e[1;38;2;0;175;117m"

class Cube;
extern Cube cube;
extern std::ofstream ofs;
extern std::map<int64_t, std::string> phaseHash[5];

#endif
