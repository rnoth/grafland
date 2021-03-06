#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _arbprec_h_
#define _arbprec_h_

/* Macros */
#define MAX(a,b) ((a) > (b) ? a : b)

/* Function protoypes */
int *addition(int *, int *, int *);		/* Add two arrays */
void *arbprec_malloc(size_t);			/* Memory allocater with error */
size_t arraylen(int *, int);			/* Similiar to strlen except it searches for the specified token */
int *bigflt_alloc(void);			/* alloc a bigflt */
void bigflt_free(int *);			/* free a bigflt */
void copyarray(int *, int *, size_t);		/* Copy an array of ints to another array of ints */ 
void die(char *);				/* Kill and error message */
int iszero(int *);				/* Returns true if an entire array is zero */ 
int *divide(int *, int *, int *);		/* Multiply arrays of integers (long multiplication) */ 
int *multiply(int *, int *, int *);		/* Multiply arrays of integers (long multiplication) */ 
size_t reversestr(int *);			/* Reverse an integer array */
void setarray(int *, int, size_t);		/* Set an array of ints to all zeros or a magnitude thereof */
int *subtraction(int *, int *, int *);		/* Subtract two arrays */
int *str2ints(char *, int *);			/* Convert a string into an integer array */ 
void printarray(int *, size_t len);		/* Print an array of integers */
int hasplace(int *, size_t, size_t);		/* Return an indice position if it exists, if not, return 0 */
void verbosity(int *, char *, int, size_t);	/* Verbosity function */

/* Globals */
extern size_t cardinal;				/* All array functions must have the same length (cardinality) */
extern int base; 				/* Default to base 10 */
int *mirror; 

#endif /* _arbprec_h_ */

