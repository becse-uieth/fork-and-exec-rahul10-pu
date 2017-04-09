#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
main()
{
    char buf[1024];
    char *args[64];
    for (;;) {
        printf("Command: ");
        if (gets(buf) == NULL) {
            printf("\n");
            exit(0);
        }
        parse(buf, args);
        execute(args);
    }
}
parse(buf, args)
char *buf;
char **args;
{
    while (*buf != NULL) {
        while ((*buf == ' ') || (*buf == '\t'))
            *buf++ = NULL;
        *args++ = buf;
        while ((*buf != NULL) && (*buf != ' ') && (*buf != '\t'))
            buf++;
    }

    *args = NULL;
}
execute(args)
char **args;
{
    int pid, status;
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        execvp(*args, args);
        perror(*args);
        exit(1);
    }
    while (wait(&status) != pid);
}