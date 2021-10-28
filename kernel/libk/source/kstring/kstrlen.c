#include <kstring.h>

size_t kstrlen(const char *__str)
{
    size_t len = 0;
    while (*__str++)
        len++;
    return len;
}