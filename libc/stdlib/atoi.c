#include "stdlib.h"

int gatoi(const char *s)
{
	int i, n;
	i = n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10 * n + (s[i] - '0');
	return n;
} 
