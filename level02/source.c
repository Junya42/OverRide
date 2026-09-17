#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char    username[100];      /* rbp-0x70  */
    char    file_pass[41];      /* rbp-0xa0  */
    char    password[100];      /* rbp-0x110 */
    FILE    *fp;
    int     nread;

    memset(username, 0, 100);
    memset(file_pass, 0, 41);
    memset(password, 0, 100);
    fp = NULL;
    nread = 0;

    fp = fopen("/home/users/level03/.pass", "r");
    if (fp == NULL) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    nread = fread(file_pass, 1, 41, fp);
    file_pass[strcspn(file_pass, "\n")] = '\0';
    if (nread != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }
    fclose(fp);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************/");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    printf("--[ Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("--[ Password: ");
    fgets(password, 100, stdin);
    password[strcspn(password, "\n")] = '\0';

    puts("*****************************************");

    if (strncmp(file_pass, password, 41) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return 0;
    }

    printf(username);                    /* format string */
    puts(" does not have access!");
    exit(1);
}