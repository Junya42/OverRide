#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void log_wrapper(FILE *log, char *prefix, char *filename)
{
    char buf[264];

    strcpy(buf, prefix);
    snprintf(buf + strlen(buf), 254 - strlen(buf), filename);
    buf[strcspn(buf, "\n")] = 0;
    fprintf(log, "LOG: %s\n", buf);
}

int main(int argc, char **argv)
{
    char dest[112];
    char c = 0xff;
    int  fd = -1;
    FILE *src;
    FILE *log;

    if (argc != 2)
        printf("Usage: %s filename\n", argv[0]);

    log = fopen("./backups/.log", "w");
    if (!log) {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    log_wrapper(log, "Starting back up: ", argv[1]);

    src = fopen(argv[1], "r");
    if (!src) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    strcpy(dest, "./backups/");
    strncat(dest, argv[1], 0x63 - strlen(dest));

    fd = open(dest, O_WRONLY | O_CREAT | O_EXCL, 0660);
    if (fd < 0) {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
    }

    while ((c = fgetc(src)) != (char)0xff)
        write(fd, &c, 1);

    log_wrapper(log, "Finished back up ", argv[1]);
    fclose(src);
    close(fd);
    return 0;
}