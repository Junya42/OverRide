#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char    buf[100];
    int     i;

    fgets(buf, 100, stdin);
    i = 0;
    while (i < (int)strlen(buf)) {
        if (buf[i] > 0x40 && buf[i] <= 0x5a)   /* 'A'..'Z' */
            buf[i] ^= 0x20;                    /* to lowercase */
        i++;
    }
    printf(buf);
    exit(0);
}