#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clear_stdin(void)
{
    char c = 0;

    while (1) {
        c = getchar();
        if (c == '\n' || c == (char)0xff)
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

void decrypt(int key)
{
    char cipher[17];
    unsigned int i;
    unsigned int len;

    /* little-endian immediates: 51 7d 7c 75 60 73 66 67 7e 73 66 7b 7d 7c 61 33 00 */
    memcpy(cipher, "Q}|u`sfg~sf{c|a3", 16);
    cipher[16] = '\0';

    len = strlen(cipher);
    for (i = 0; i < len; i++)
        cipher[i] ^= key;

    if (memcmp(cipher, "Congratulations!", 17) == 0)
        system("/bin/sh");
    else
        puts("\nInvalid Password");
}

void test(int input, int magic)
{
    int diff = magic - input;

    switch (diff) {
    case 1: case 2: case 3: case 4: case 5:
    case 6: case 7: case 8: case 9:
    case 16: case 17: case 18: case 19: case 20: case 21:
        decrypt(diff);
        break;
    default:                 /* 0, 10-15, and anything > 21 */
        decrypt(rand());
        break;
    }
}

int main(void)
{
    int n;

    srand(time(NULL));
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password:");
    scanf("%d", &n);
    test(n, 0x1337d00d);
    return 0;
}