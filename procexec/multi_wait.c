#include <sys/wait.h>
#include <time.h>
#include "curr_time.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
  int numDead;        /* number of children so far waited for */
  pid_t childPid;     /* PID of waited for child */
  int j;

  if (argc < 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s sleep-time...\n", argv[0]);

  setbuf(stdout, NULL);           /* disable buffering of stdout */

  for (j = 1; j < argc; j++) {    /* create one child for each argument */
    switch (fork()) {
      case -1:
        errExit("fork");
      case 0:                     /* child sleeps for a while then exits */
        printf("[%s] child %d started with PID %ld, sleeping %s "
            "seconds\n", currTime("%T"), j, (long) getpid(), argv[j]);
        sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
        _exit(EXIT_SUCCESS);
      default:                    /* Parent just continues around loop */
        break;
    }
  }

  numDead = 0;
  for (;;) {                      /* parent waits for each child to exit */
    childPid = wait(NULL);
    if (childPid == -1) {
      if (errno == ECHILD) {
        printf("No more children - bye!\n");
        exit(EXIT_SUCCESS);
      } else {
        errExit("wait");
      }
    }

    numDead++;
    printf("[%s] wait() returned child PID %ld (numDead=%d)\n",
        currTime("%T"), (long) childPid, numDead);
  }
}
