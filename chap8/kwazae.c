#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <-e|-u|-g|-i|-p> [args]\n", argv[0]);
        exit(1);
    }

    if (argv[1][0] == '-') {
        switch (argv[1][1]) {
            case 'e':
                if (argc > 2) {
                    char *val = getenv(argv[2]);
                    if (val) printf("%s = %s\n", argv[2], val);
                } else {
                    for (char **ptr = environ; *ptr != 0; ptr++)
                        printf("%s\n", *ptr);
                }
                break;
            case 'u':
                printf("My Realistic User ID : %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
                printf("My Valid User ID : %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
                break;
            case 'g':
                printf("My Realistic Group ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
                printf("My Valid Group ID : %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
                break;
            case 'i':
                printf("My process number : [%d]\n", getpid());
                break;
            case 'p':
                printf("My parent process number : [%d]\n", getppid());
                break;
            default:
                fprintf(stderr, "Unknown option: %s\n", argv[1]);
        }
    }
    return 0;
}
