#include "../stddef/stddef.h" 
#include "string.h" 

size_t gstrlen(const char *s)
{
        size_t i = 0;
        while ( s[i] != '\0' )
                ++i;
        return i;
}


