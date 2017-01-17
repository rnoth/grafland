/*
	Copyright 2017, CM Graff, "libgen.h"
	See LICENSE for copying details
*/

/* function prototypes */
char *gbasename(char *);
char *gdirname(char *);
char *ggnu_basename(char *path);

/* functions */
char *gdirname(char *str)  /* not yet implemented */
{
	return str;
}

char *gnu_basename(char *path) /* non-POSIX GNU version of basename */
{
	char *base; 
	base = strrchr(path, '/');
	return base ? base+1 : path;
}


char *gbasename(char *path)
{
	size_t i = 0;
	int pathtab[4096] = { 0 };
	size_t npth = 0;

	for( i = 0; path[i] != '\0' && i < 4096; i++)
	{
		if ( path[i] == '/' )
			pathtab[npth++] = i;
	}
	for ( ; i > 1 && path[--i] == '/' ; )
	{
		path[i] = '\0';
		--npth;
	}
	
	if ( npth > 1)
		return path + pathtab[npth - 1] + 1; 
	else 
		return path;
}
