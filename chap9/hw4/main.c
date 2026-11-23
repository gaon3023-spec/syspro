#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 64

int main(void) {
    char buf[MAXLINE];
    char *args[MAXARG];

    while (1) {
        printf("[Shell] ");
        fflush(stdout);

        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\n");
            break;
        }

        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0)
            continue;

        if (strcmp(buf, "exit") == 0)
            break;

        int argc = 0;
        char *saveptr = NULL;
        char *tok = strtok_r(buf, " \t", &saveptr);
        while (tok != NULL && argc < MAXARG - 1) {
            args[argc++] = tok;
            tok = strtok_r(NULL, " \t", &saveptr);
        }
        args[argc] = NULL;

        if (argc == 0)
            continue;

        int background = 0;
        if (strcmp(args[argc - 1], "&") == 0) {
            background = 1;
            args[argc - 1] = NULL;
            argc--;
        }

        if (argc == 0)
            continue;

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork error");
            continue;
        }

        if (pid == 0) {
            printf("[%d] Child process start\n", getpid());
            execvp(args[0], args);
            perror("execvp error");
            _exit(127);
        }

        if (!background) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            printf("[%d] Running in background\n", pid);
        }
    }

    return 0;
}
