#include "rubik.hpp"

char		*filetostr(char *filename)
{
	char	buf[1000];
	char	*ret;
	FILE	*ptr;
	int		i;

	ret = (char*)calloc(1000, 1);
	ptr = fopen(filename, "r");
	i = 0;
	while (fgets(buf, 999, ptr))
	{
		ret = (char*)realloc(ret, strlen(ret) + strlen(buf) + 1);
		strcpy(ret + i, buf);
		i += strlen(buf);
	}
	fclose(ptr);
	return (ret);
}

void	mult(float *a, float *b, float *p)
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			p[i * 4 + j] = 0;
			k = -1;
			while (++k < 4)
				p[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
		}
	}
}