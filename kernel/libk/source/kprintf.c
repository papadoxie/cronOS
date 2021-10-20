#include <kstdio.h>
#include <stdarg.h>
#include <kstring.h>
#include <stddef.h>

static bool_t print(const char *str, size_t len)
{
    const unsigned char *bytes = (const unsigned char *)str;

    for (size_t i = 0; i < len; i++)
    {
        if (kputchar(bytes[i]) == EOF)
        {
            return false;
        }
    }
    return true;
}

int kprintf(const char *__restrict__ __fmt_str, ...)
{
    va_list params;
    va_start(params, __fmt_str);

    int written = 0;

    // Run until we hit the end of the string
    while (*__fmt_str != '\0')
    {
        size_t remaining = __INT32_MAX__ - written;

        if (__fmt_str[0] != '%' || __fmt_str[1] == '%')
        {
            if (__fmt_str[0] == '%')
            {
                __fmt_str++;
            }
            size_t len = 1;

            while (__fmt_str[len] && __fmt_str[len] != '%')
            {
                len++;
            }

            if (remaining < len)
            {
                return EOVERFLOW;
            }

            if (!print(__fmt_str, len))
            {
                return EIO;
            }

            __fmt_str += len;
            written += len;
            continue;
        }

        const char *start = __fmt_str++;

        switch (*__fmt_str)
        {
        case 'c':
            __fmt_str++;
            char c = (char)va_arg(params, int);
            if (!remaining)
            {
                return EOVERFLOW;
            }
            if (!print(&c, 1))
            {
                return EIO;
            }
            written++;
            break;

        default:
            __fmt_str = start;
            break;
        }
        return 0;
    }

    va_end(params);
    return written;
}
