/*
 * buffer overflow error-prone program
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

void checkName(char *name) {
        if (strlen(name) >= BUFSIZE) {
                printf("Error, your name is too long\n");
                exit(1);
        }
}

void setGradeToD(void * addr) {
        grade = 'D';
        return;
}

void dummy(void (**f)())
{
        return;
}

void readString(char *s, int r, void f()) {
   char buf[BUFSIZE + r];
   int i = 0; 
   int c;

   dummy(&f);

#ifdef DEBUG
   printf("s %x buf %x i %x r %d\n", s, buf, &i, r);
#endif

   for (;;) {
      c = fgetc(stdin);
      if ((c == EOF) || (c == '\n'))
         break;
      buf[i++] = c;
   }
   buf[i] = 0;

   for (i = 0; i < BUFSIZE; i++) 
      s[i] = buf[i];

   f(s);
#ifdef DEBUG
   printf("grade %c\n", grade);
#endif   
}

int main(int argc, char *argv[]) {
   int r = 0;

   srand(getpid());
   if (argc > 1 && argv[1][0] == 'r')
     r = rand() % 32;

   mprotect((void*)((unsigned int)Name & 0xfffff000), 1,
            PROT_READ | PROT_WRITE | PROT_EXEC);

#ifdef DEBUG
   printf("grade %x Name %x r %d\n", grade, Name, r);
#endif

   printf("What is your name?\n");
   readString(Name, r, checkName);

   if (strcmp(Name, "Andrew Appel") == 0) 
      grade = 'C';

   printf("Thank you, %s.\n", Name);
   printf("I recommend that you get a grade of %c on this assignment.\n", 
          grade);

   exit(0);
}
