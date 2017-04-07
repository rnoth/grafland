#include <gstddef.h>
#include <gstring.h>

size_t gstrcspn(const char *s1, const char *reject)
{
        size_t i = 0;
        size_t j = 0;
        for ( ; *(s1+i) ; i++)
	{ 
                for (j = 0 ; *(reject+j) ; j++)
                        if(*(s1+i) == *(reject+j))
                                return i;
        }
        return i;
}

