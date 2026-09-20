#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char buf[100];   /* 0x28(%esp) */
    int  i;          /* 0x8c(%esp) */

    fgets(buf, 100, stdin);

    i = 0;
    while (i < (int)strlen(buf)) {
        /* cmp $0x40 / jle  +  cmp $0x5a / jg  →  'A'..'Z' */
        if (buf[i] > 0x40 && buf[i] <= 0x5a)
            buf[i] ^= 0x20;   /* to lowercase */
        i++;
    }

    printf(buf);     /* format string — no "%s", 10th argument */
    exit(0);
}