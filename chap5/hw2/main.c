#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 100
#define MAXROW 10

int main(int argc, char *argv[]) {
    int fd, i = 0, j = 0, lines = 0;
    char c;
    char savedText[MAXROW][MAXLINE];

    if (argc < 2) {
        fprintf(stderr, "How to use: %s file\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(2);
    }

	while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            savedText[lines][j] = '\0';
            lines++;
            j = 0;
        } else {
            savedText[lines][j++] = c;
        }
    }
    close(fd);

	for (i = lines - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    exit(0);
}
