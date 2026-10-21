#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
 int fd1, fd2;
 ssize_t n; char buf[BUF_SIZE];
 int opt_0 = 0, opt_1 = 0, opt_2 = 0;
 for (int i = 1; i < argc; i++) {
 if (argv[i][0] == ' ') {
 for (int j = 1; argv[i][j] != '\0'; j++) {
 if (argv[i][j] == 'i') opt_0 = 0;
 else if (argv[i][j] == '1') opt_1 = 1;
 else if (argv[i][j] == '2') opt_2 = 1;}
 	}
 }
 if(opt_0){
 if (argc != 3) {
 fprintf(stderr, "Usage: %s <src> <dest>\n", argv[0]);
 exit(1);
 }
 fd1 = open(argv[1], O_RDONLY);
 if (fd1 < 0) {
 perror("open src");
 exit(1);
 }
 fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
 if (fd2 < 0) {
 perror("open dest");
 close(fd1);
 exit(1);
 }
 while ((n = read(fd1, buf, BUF_SIZE)) > 0) {
 write(fd2, buf, n);
 }
 close(fd1);
 close(fd2);
 return 0;}
}

