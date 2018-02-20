#include "tlpi_hdr.h"

static int idata = 111;      /* allocated in data segment */

int main(int argc, char *argv[]) {
  int istack = 222;       /* allocated in stack segment */
  pid_t childPid;

  switch(childPid = fork()) {
    case -1:
      errExit("fork");

    case 0:
      idata *= 3;
      istack *= 3;
      break;

    default:
      sleep(3);           /* give the child a chance to execute */
      break;
  }

  /* Both parent and child come here */
  printf("PID=%ld %s idata=%d istack=%d\n", (long) getpid(),
      (childPid == 0) ? "(child) " : "(parent)", idata, istack);

  exit(EXIT_SUCCESS);

}

