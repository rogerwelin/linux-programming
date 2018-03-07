#include "curr_time.h"
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
  int pfd[2];
  int j, dummy;

  if (argc < 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s sleep-time...\n", argv[0]);

  setbuf(stdout, NULL);

  printf("%s Parent started\n", currTime("%T"));

  // 1
  if (pipe(pfd) == -1)
    errExit("pipe");

  for (j = 1; j < argc; j++) {
    // 2
    switch (fork()) {
      case -1:
        errExit("fork %d", j);
      case 0:                     /* child */
        // 3
        if (close(pfd[0]) == -1)  /* read end is unused */
          errExit("close");

        /* Child does some work, and lets parent know it's done */
        sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
        printf("%s Child %d (PID=%ld) closing pipe\n",
            currTime("%T"), j, (long) getpid());
        // 4
        if (close(pfd[1]) == -1)
          errExit("close");

        /* Child now carries on to do other things... */
        _exit(EXIT_SUCCESS);
      default:                    /* Parent loops to create next child */
        break;
    }
  }

  /* Parent comes here; close write end of pipe so we can see EOF */
  if (close(pfd[1]) == -1)
    errExit("close");

  /* Parent may do other work, then synchronizes with children */
  // 5
  if (read(pfd[0], &dummy, 1) != 0)
    fatal("parent didn't get EOF");
  printf("%s Parent ready to go\n", currTime("%T"));

  /* Parent can now carry on to do other things... */
  exit(EXIT_SUCCESS);
}
