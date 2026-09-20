#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int serial)
{
    int i;
    int len;
    int hash;

    login[strcspn(login, "\n")] = 0;
    len = strnlen(login, 32);
    if (len <= 5)
        return 1;

    if (ptrace(0, 0, 1, 0) == -1) {   /* PTRACE_TRACEME */
        puts("!! TAMPERING DETECTED !!");
        return 1;
    }

    hash = ((signed char)login[3] ^ 0x1337) + 0x5eeded;  /* 4919 + 6221293 */

    for (i = 0; i < len; i++) {
        if ((unsigned char)login[i] <= 31)
            return 1;
        hash += ((signed char)login[i] ^ hash) % 1337;
    }

    return serial != (unsigned int)hash;  /* 0 = ok */
}

int main(void)
{
    char login[32];
    unsigned int serial;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");
    printf("-> Enter Login: ");
    fgets(login, 32, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");
    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    if (!auth(login, serial)) {
        puts("Authenticated!");
        system("/bin/sh");
        return 0;
    }
    return 1;
}