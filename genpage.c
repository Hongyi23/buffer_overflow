#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i;

  if (argc != 3) {
    printf("use: genpage <id> <n>\n where <id> is a unique ID and <n> is the number of nop instations to generate\n");
    exit(1);
  }

  printf("void align%d(void) {\n", atoi(argv[1]));
  for (i = 0; i < atoi(argv[2]); i++)
    printf("  asm(\"nop\");\n");
  printf("}\n");

  return 0;
}

