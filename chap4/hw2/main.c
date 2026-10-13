#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[MAXLINE];
    int line_num = 1;

    if (argc < 2) {
        fprintf(stderr, "how to use: %s <FileName>\n", argv[0]);
        exit(1);
    }

	fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("FileOpenError");
        exit(2);
    }

    while (fgets(line, MAXLINE, fp) != NULL) {
        printf("%3d: %s", line_num++, line);
    }

    fclose(fp);
    return 0;
}
