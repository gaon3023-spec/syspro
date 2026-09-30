#include <stdio.h>
#include <string.h>
#include "copy.h"

int main() {
    char lines[5][MAXLINE];
    char temp[MAXLINE];

    for(int i = 0; i < 5; i++) {
        if(fgets(lines[i], MAXLINE, stdin) != NULL) {
            lines[i][strcspn(lines[i], "\n")] = '\0';
        }
    }

    for(int i = 0; i < 4; i++) {
        for(int j = i + 1; j < 5; j++) {
            if(strlen(lines[i]) < strlen(lines[j])) {
                copy(lines[i], temp);
                copy(lines[j], lines[i]);
                copy(temp, lines[j]);
            }
        }
    }

    for(int i = 0; i < 5; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}
