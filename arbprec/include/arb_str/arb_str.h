#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *mirror;
char *tmpmir; 
char *arb_str_add(char *, char *, char *);
char *arb_str_addition(char *, char *, char *);
void arb_str_die(char *);
int arb_str_index(char *, size_t);
char *arb_str_multiply(char *, char *, char *);
void arb_str_print_real(char *, char *);
size_t arb_str_rev(char *);
void setsign(char *);
void *arb_str_malloc(size_t);
char *arb_str_subtract(char *, char *, char *);
char *arb_str_subtraction(char *, char *, char *);
char *arb_str_divide(char *, char *, char *);
