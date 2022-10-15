#include <kstring.h>

char * kitoa(unsigned int integer) {

    int n = integer;
    int count = 0;
    do {    // count the number of digits
        n /= 10;
        ++count;
    } while (n);

    char * buffer = malloc((sizeof(unsigned int))*count);
    char * p = buffer + 11; //go to the end of the buffer
    *p = '\0';              //null terminate the string
    do {
        *--p = '0' + (integer % 10);//add digit to the string
        integer /= 10;              //remove the digit from the integer
    } while (integer);              //while there are still digits
    return p;
}

// Write implementation after writing malloc