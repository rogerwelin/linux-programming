#include <sys/wait.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 10

int main(int argc, char *argv[]) {
  int pfd[2];                       /* pipe file descriptors */
  char buf[BUF_SIZE];
  ssize_t numRead;

  if (argc != 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s string\n", argv[0]);

  // 1
  if (pipe(pfd) == -1)
    errExit("pipe");

  // 2
  switch (fork()) {
    case -1:
      errExit("fork");
    case 0:                     /* Child - reads from pipe */
      //3
      if (close(pfd[1]) == -1)  /* write end is unused */
        errExit("close - child");

      for (;;) {                /* read data from pipe, echo on stdout */
        // 4
        numRead = read(pfd[0], buf, BUF_SIZE);
        if (numRead == -1)
          errExit("read");
        // 5
        if (numRead == 0)       /* EOF */
          break;
        // 6
        if (write(STDOUT_FILENO, buf, numRead) != numRead)
          fatal("child - partial/failed write");
      }

      // 7
      write(STDOUT_FILENO, "\n", 1);
      if (close(pfd[0]) == -1)
        errExit("close");
      _exit(EXIT_SUCCESS);

    default:                    /* Parent - writes to pipe */
      // 8
      if (close(pfd[0]) == -1)
        errExit("close - parent");

      // 9
      if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
        fatal("parent - partial/failed write");

      // 10
      if (close(pfd[1]) == -1)    /* child will see EOF */
        errExit("close");
      wait(NULL);                 /* wait for child to finish */
      exit(EXIT_SUCCESS);
  }
}
