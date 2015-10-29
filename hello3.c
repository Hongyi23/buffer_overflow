/*
 * main module
 */

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 36

char grade = 'F';
char Name[BUFSIZE];

extern void init_sandbox(void);

int main(int argc, char *argv[]) {
   int r = 0;

   srand(getpid());
   if (argc >= 2 && argv[1][0] == 'r' || argc == 3 && argv[2][0] == 'r')
     r = rand() % 32;

   mprotect((void*)((unsigned int)Name & 0xfffffffffffff000), 1,
            PROT_READ | PROT_WRITE /* | PROT_EXEC */); // cannot execute !!!

   if (argc >= 2 && argv[1][0] == 's' || argc == 3 && argv[2][0] == 's')
     init_sandbox();

#ifdef DEBUG
   printf("grade %x Name %x r %d\n", grade, Name, r);
#endif

   printf("What is your name?\n");
   readString(Name, r);

   if (strcmp(Name, "Andrew Appel") == 0) 
      grade = 'C';

   printf("Thank you, %s.\n", Name);
   printf("I recommend that you get a grade of %c on this assignment.\n", 
          grade);

   exit(0);
}
