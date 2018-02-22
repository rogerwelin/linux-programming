#include "tlpi_hdr.h"

/* pipe this to file: ./fork_stdio_buf > a.txt
 * both child and parent buffer are written */

int main(int argc, char *argv[]) {
  printf("Hello World\n");
  write(STDOUT_FILENO, "Ciao\n", 5);

  if (fork() == -1)
    errExit("fork");

  /* Both child and parent continue execution here */

  exit(EXIT_SUCCESS);

}
