#include <stdio.h>
#include <string.h>

char username[256]; /* BSS @ 0x804a040 */

int verify_user_name(void)
{
    puts("verifying username....\n");
    return memcmp(username, "dat_wil", 7);
}

int verify_user_pass(char *password)
{
    return memcmp(password, "admin", 5);
}

int main(void)
{
    char    password[64];   /* [esp+0x1c] */
    int     result;         /* [esp+0x5c] */

    memset(password, 0, 64);
    result = 0;

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(username, 256, stdin);

    result = verify_user_name();
    if (result != 0) {
        puts("nope, incorrect username...\n");
        return 1;
    }

    puts("Enter Password: ");
    fgets(password, 100, stdin);    /* 100 in 64 → overflow */

    result = verify_user_pass(password);
    if (result || !result) {
            return 0;
    }
    puts("nope, incorrect password...\n");
    return 1;
}