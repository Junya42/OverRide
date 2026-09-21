#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s {
    char msg[140];
    char username[40];
    int  len;
};

void secret_backdoor(void)
{
    char buf[128];

    fgets(buf, 128, stdin);
    system(buf);
}

void set_username(struct s *t)
{
    char buf[128] = {0};
    int  i = 0;

    puts(">: Enter your username");
    printf(">>: ");
    fgets(buf, 128, stdin);
    while (i <= 40 && buf[i])
        t->username[i++] = buf[i];
    printf(">: Welcome, %s", t->username);
}

void set_msg(struct s *t)
{
    char buf[1024] = {0};

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(buf, 1024, stdin);
    strncpy(t->msg, buf, t->len);
}

void handle_msg(void)
{
    struct s t;

    memset(t.username, 0, 40);
    t.len = 140;
    set_username(&t);
    set_msg(&t);
    puts(">: Msg sent!");
}

int main(void)
{
    puts("--------------------------------------------\n"
         "|   ~Welcome to l33t-m$n ~    v1337        |\n"
         "--------------------------------------------");
    handle_msg();
    return 0;
}