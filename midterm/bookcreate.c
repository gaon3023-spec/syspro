#include <stdio.h> 
#include <stdlib.h>
#include "book.h"
int main(int argc, char* argv[])  
{ 
   struct book rec;
   FILE *fp;

   if (argc != 2) {
      fprintf(stderr, "How to use: %s FileName\n",argv[0]);
      exit(1); 
   }

   fp = fopen(argv[1], "wb");
   printf("%-2s %-10s %-10s %-4s %3s %6s\n", "Booknumber", "BookName", "auother" "year" "lent" "lent_t/f"); 
   while (scanf("%d %s %s %d %d %s", &rec.num, rec.name, rec.au, &rec.year, &rec.lent, rec.ft) == 6) 
      fwrite(&rec, sizeof(rec), 1, fp);

   fclose(fp);
   exit(0);
} 

