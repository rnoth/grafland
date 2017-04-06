#include <gstddef.h>
#include <gstring.h>

void *gmemcpy(void *destination, const void *source, size_t len)
{
        size_t i = 0;
        char *d = destination;
        const char *s = source;
        for (; i < len; i++)
                d[i] = s[i];
        return destination;
}

