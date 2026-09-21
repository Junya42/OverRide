#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void clear_stdin(void)
{
    char c = 0;

    while (1) {
        c = getchar();
        if (c == '\n' || c == (char)0xff)   /* EOF */
            break;
    }
}

unsigned int get_unum(void)
{
    unsigned int n = 0;

    fflush(stdout);
    scanf("%u", &n);
    clear_stdin();
    return n;
}

void prog_timeout(void)
{
    /* sys_exit(1) */
    asm("mov $1, %eax; mov $1, %ebx; int $0x80");
}

int store_number(unsigned int *tab)
{
    unsigned int value = 0;
    unsigned int index = 0;

    printf(" Number: ");
    value = get_unum();
    printf(" Index: ");
    index = get_unum();

    if (index % 3 == 0 || (value >> 24) == 0xb7) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }
    tab[index] = value;
    return 0;
}

int read_number(unsigned int *tab)
{
    unsigned int index = 0;

    printf(" Index: ");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, tab[index]);
    return 0;
}

int main(int argc, char **argv, char **envp)
{
    unsigned int tab[100];
    char cmd[20];
    int  ret;
    int  i;

    for (i = 0; i < 100; i++)
        tab[i] = 0;
    memset(cmd, 0, 20);
    ret = 0;

    while (*argv) {
        memset(*argv, 0, strlen(*argv));
        argv++;
    }
    while (*envp) {
        memset(*envp, 0, strlen(*envp));
        envp++;
    }

    puts(
    "----------------------------------------------------\n"
    "  Welcome to wil's crappy number storage service!   \n"
    "----------------------------------------------------\n"
    " Commands:                                          \n"
    "    store - store a number into the data storage    \n"
    "    read  - read a number from the data storage     \n"
    "    quit  - exit the program                        \n"
    "----------------------------------------------------\n"
    "   wil has reserved some storage :>                 \n"
    "----------------------------------------------------\n");

    while (1) {
        printf("Input command: ");
        ret = 1;
        fgets(cmd, 20, stdin);
        cmd[strlen(cmd) - 1] = 0;

        if (strncmp(cmd, "store", 5) == 0)
            ret = store_number(tab);
        else if (strncmp(cmd, "read", 4) == 0)
            ret = read_number(tab);
        else if (strncmp(cmd, "quit", 4) == 0)
            break;

        if (ret)
            printf(" Failed to do %s command\n", cmd);
        else
            printf(" Completed %s command successfully\n", cmd);
        memset(cmd, 0, 20);
    }
    return 0;
}