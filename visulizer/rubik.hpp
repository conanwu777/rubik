#ifndef RUBIK_HPP
# define RUBIK_HPP

# include <math.h>
# include <fcntl.h>
# include "Cube.hpp"
# include "Display.hpp"
# include <iostream>

using namespace std;

char	*filetostr(char *filename);
void	mult(float *a, float *b, float *p);

extern Cube cube;

#endif
