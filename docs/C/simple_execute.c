#include <unistd.h>

int main(int argc, char **argv)
{
	/* usage: ./simple_execute ls -la */
	if (argc > 1)
	{
		++argv;
		execvp(*argv, argv);
	}
	return 0;
}

