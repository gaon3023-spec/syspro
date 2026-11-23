#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARGS 64

/* Trim leading and trailing whitespace */
static char *trim_ws(char *s) {
    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r')
        s++;
    if (*s == '\0')
        return s;
    char *end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        end--;
    }
    return s;
}

/* Execute a single command segment with optional '&', '>', and '<' */
static void run_single_cmd(char *segment) {
    char *line = trim_ws(segment);
    if (*line == '\0')
        return;

    int background = 0;
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '&') {
        background = 1;
        line[len - 1] = '\0';
        line = trim_ws(line);
        if (*line == '\0')
            return;
    }

    char *infile = NULL;
    char *outfile = NULL;
    char *args[MAXARGS];
    int argc = 0;

    char *saveptr = NULL;
    char *tok = strtok_r(line, " \t", &saveptr);
    while (tok != NULL && argc < MAXARGS - 1) {
        if (strcmp(tok, "<") == 0) {
            tok = strtok_r(NULL, " \t", &saveptr);
            if (tok != NULL)
                infile = tok;
        } else if (strcmp(tok, ">") == 0) {
            tok = strtok_r(NULL, " \t", &saveptr);
            if (tok != NULL)
                outfile = tok;
        } else {
            args[argc++] = tok;
        }
        tok = strtok_r(NULL, " \t", &saveptr);
    }
    args[argc] = NULL;

    if (argc == 0)
        return;

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return;
    }

    if (pid == 0) {
        if (infile != NULL) {
            int fd_in = open(infile, O_RDONLY);
            if (fd_in < 0) {
                perror("open input file error");
                _exit(1);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        if (outfile != NULL) {
            int fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("open output file error");
                _exit(1);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        execvp(args[0], args);
        perror("execvp error");
        _exit(127);
    }

    if (!background) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        printf("[Background pid %d] started\n", pid);
    }
}

int main(void) {
    char buf[MAXLINE];

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\n");
            break;
        }

        buf[strcspn(buf, "\n")] = '\0';
        char *trimmed = trim_ws(buf);
        if (strcmp(trimmed, "exit") == 0)
            break;

        /* Split sequential commands separated by ';' */
        char *cmd_save = NULL;
        char *cmd = strtok_r(buf, ";", &cmd_save);
        while (cmd != NULL) {
            run_single_cmd(cmd);
            cmd = strtok_r(NULL, ";", &cmd_save);
        }
    }

    return 0;
}
