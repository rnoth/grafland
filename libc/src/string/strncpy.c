#include <gstddef.h>

#include <gstring.h>

char *gstrncpy(char *dest, const char *src, size_t n)
{
        size_t i = 0;

        for (; i < n && src[i] != '\0'; i++)
                dest[i] = src[i];
        for (; i < n; i++)
                dest[i] = '\0';

        return dest;
}

