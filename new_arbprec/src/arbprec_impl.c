#include <arbprec/arbprec.h>

/* Functions */
void *arbprec_malloc(size_t len)
{
	void *ret;
	if ( !(ret = malloc(len)) )
		die("malloc failed\n"); 
	return ret;
}

size_t arraylen(int *array, int delim)
{ 
	size_t len = 0; 
	while ( array[len] != delim ) 
		++len;
	return len;
}

int *bigflt_alloc(void)
{
	return malloc(1000 * sizeof (int));
}

void bigflt_free(int *bf)
{
	free(bf);
}

void copyarray(int *answer, int *from, size_t len)
{
	size_t i = 0;
	for ( i = 0; i < len ; i++ )
		answer[i] = from[i];
}

void die(char *message)
{
	fprintf(stderr, "%s", message);
	exit(1);
}

int hasplace(int *s, size_t idx, size_t len)
{
        if ( idx < len )
        	return s[len - idx - 1];
        return 0;
} 

int iszero(int *answer)
{
	size_t i = 0;
	for ( i = 0; answer[i] != 4242 ; i++ )
		if ( answer[i] )
			return 1;
	return 0;
}

void printarray(int *a, size_t len)
{
	size_t i = 0;
	for ( i = 0; i < len ; )
		printf("%d", a[i++]);
	printf("\n");
} 

size_t reversestr(int *x)
{
        size_t i = 0;
        char swap = 0;
        size_t lim = arraylen(x, 4242);
        size_t half = lim / 2;

        for ( ; i < half ; i++)
        {
                swap = x[i];
                x[i] = x[lim - i - 1];
                x[lim - i - 1] = swap;
        }
        return lim;
}

void setarray(int *answer, int rootcap, size_t len)
{
	size_t i = 0;
	for( i = 0; i < len; i++)
		answer[i] = 0;
	answer[0] = rootcap;
}
 
void set_array(int *array, int init, size_t dec, int sign, int terminator, size_t len)
{
	/* set_array(array, 0, 0, '+', 4242, 4099); */
	size_t i = 2;
	for( i = 2; i < len; i++)
		array[i] = init;
	array[0] = dec;
	array[1] = sign;
	array[len] = terminator;
}

int *str2ints(char *a, int *b)
{
	size_t i;
	for( i = 0 ;a[i] != '\0' ; i++)
		b[i] = a[i] - '0';
	b[i] = 4242;
	return b;
}

void verbosity(int *array, char *message, int on, size_t length)
{
	static int lever = 0;

	if ( on == 1 )
		lever = 1;
	if ( lever == 0 )
		return;
	printf("START verbosity\n");
	if ( message )
		printf("message: %s\n", message); 
	if ( array )
		printarray(array, length);
	if (message||array)
		printf("END verbosity:\n");
}

