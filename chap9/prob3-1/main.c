#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( ) 
{
   printf("parental process start\n");
   if (fork( ) == 0) {
      execl("/bin/echo", "echo", "hello", NULL);
      fprintf(stderr,"First execution failed"); 
      exit(1);
   }
   printf("parental process end\n");
   exit(0);
}

