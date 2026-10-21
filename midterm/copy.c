#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[]){
 char c;
 FILE *fp1, *fp2;

 
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
 char c;
   FILE *fp1, *fp2;
   if (argc !=3) {
      fprintf(stderr,  "How to use: %s File1 File2\n", argv[0]);
      return 1;
   }
fp1 = fopen(argv[1], "r");
   if (fp1 == NULL) {
      fprintf(stderr, "File %s Open Error\n", argv[1]);
      return 2;
   }

   fp2 = fopen(argv[2], "w");
   while ((c = fgetc(fp1)) != EOF)
      fputc(c, fp2);
}

 close(fp1);
 close(fp2);
 return 0; 
 }

