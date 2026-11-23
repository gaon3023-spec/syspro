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
    char option[20];

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

    printf("File read success\n");
    printf("Total Line : %d\n", lines);
    printf("You can choose 1 ~ %d Line\n", lines);
    printf("Pls 'Enter' the line to select : ");
    
    scanf("%s", option);

	if (option[0] == '*') {
        for (i = 0; i < lines; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if (option[1] == '-') {
		int start = option[0] - '0';
        int end = option[2] - '0';
        for (i = start - 1; i < end && i < lines; i++) {
            printf("%s\n", savedText[i]);
        }
    } else {
		int lineNum = option[0] - '0';
        if (lineNum > 0 && lineNum <= lines) {
            printf("%s\n", savedText[lineNum - 1]);
        }
    }

    exit(0);
}
