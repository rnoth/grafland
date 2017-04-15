#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <arbprec/arbprec.h>

size_t cardinal;         /* All array functions must have the same length (cardinality) */
int base = 10;                   /* Default to base 10 */

int main(int argc, char **argv)
{
	int *a;
	int *b;
	int *c;

	printf("allocating some big floats...");
	fflush(stdout);

	a = bigflt_alloc();
	b = bigflt_alloc();
	c = bigflt_alloc();

	if (!a || !b) abort();

	printf("done\n");

	printf("testing addition..\n");

	printf("\tpreforming some basic addition...");
	fflush(stdout);
	str2ints("3", a);
	str2ints("4", b);
	addition(a, b, c);
	assert(isequal_to(c, 7));
	printf("done\n");

	printf("\tadding some large numbers...");
	fflush(stdout);
	str2ints("532153", a);
	str2ints("3356544", b);
	addition(a, b, c);
	assert(isequal_to(c, 3888697));
	printf("done\n");

	printf("done (testing addition)\n");

	printf("freeing the big floats...");
	bigflt_free(a);
	bigflt_free(b);
	bigflt_free(c);
	printf("done\n");
	fflush(stdout);

	return 0;
}

#if 0
int main(int argc, char **argv)
{
	int *hold;	/* Copy of bigint1 */
	int *hold2;	/* Copy of bigint2 */
	double a = 0;
	double b = 0;
	int o = 0;
	size_t carda;
	size_t cardb; 
	int *bigint1;			/* Copy of argument 1 */
	int *bigint2;			/* Copy of argument 2 */

	while ((o = getopt(argc, argv, "vb:")) != -1)
		switch (o) { 
			case 'v':
				verbosity(NULL, NULL, 1);
				break;
			case 'b': /* Override base */
				base = strtoul(optarg, 0, 10);
				break; 
			default: 
				break;
		}

	argv += optind;
	argc -= optind;


	if ( argc < 2 )
		die("Needs 2 args\n");

	a = strtod(argv[0], 0);
	b = strtod(argv[1], 0);

	printf("  %20lf\n", a);

	printf("  %20lf\n", b);
	printf("  %20s\n", "-------------------");
	printf("+ %20lf\n", a + b);
	printf("- %20lf\n", a - b);
	printf("* %20lf\n", a * b);
	printf("/ %20lf\n", a / b);
	

	mirror = strallocate(1000 * sizeof(int));
	result = strallocate(1000 * sizeof(int));
	tmpmir = strallocate(1000 * sizeof(int));
	bigint1 = strallocate(1000 * sizeof(int));
	bigint2 = strallocate(1000 * sizeof(int));

	/* arb divide */
	printf("division\n");
	carda = strlen(argv[0]);
	cardb = strlen(argv[1]);
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold[carda] = base;
	hold2[cardb] = base;
	divide(hold, hold2, result);

	/* arb multiply */
	printf("multiplication\n");

	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	multiply(hold, hold2, result);

	/* arb addition */
	printf("addition\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold = addition_r(hold, hold2, result);
	printarray(hold, cardinal);
	
	/* arb subtraction */
	printf("subtraction\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	hold = subtraction_r(hold, hold2, result);
	printarray(hold, cardinal);
	
	/* arb addition */
	printf("simple addition\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	addition(hold, hold2);
	printarray(hold, cardinal);

	/* arb subtract */
	printf("simple subtraction\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	subtract(hold, hold2);
	printarray(hold, cardinal);
	
	/* arb setarray, arb iszero, arb copyarray */
	printf("setarray. iszero, copyarray\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	setarray(hold, 0);
	setarray(hold2, 1);
	printarray(hold, cardinal);
	printarray(hold2, cardinal);
	if ( iszero(hold) == 0 )
		printf("hold is zero\n");
	if ( iszero(hold2) != 0 )
		printf("hold2 is not zero\n");
	copyarray(hold2, hold);
	if ( iszero(hold2) == 0 )
		printf("hold2 is now zero\n");

	/* single digit arb multiplication */
	printf("short multiplication\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	short_multiply(hold, hold2[0]);
	printarray(hold, cardinal);
	
	/* single digit arb short_short_divide */
	printf("short division\n");
	hold = str2ints(argv[0], bigint1);
	hold2 = str2ints(argv[1], bigint2);
	short_divide(hold, hold2[0]);
	printarray(hold, cardinal);

	return 0;
} 

#endif
