#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include "tlpi_hdr.h"

/* Set nonzero on receipt of SIGALRM */
static volatile sig_atomic_t gotAlarm = 0;

/* Retrieve and display the real time, and (if 'includeTimer' is
 * TRUE) the current value and interval for the ITIMER_REAL timer */

static void displayTimes(const char *msg, Boolean includeTimer) {
  struct itimerval itv;
  static struct timeval start;
  struct timeval curr;
  static int callNum = 0;       /* Number of calls to this function */

  if (callNum == 0)
    if (gettimeofday(&start, NULL) == -1)
      errExit("gettimeofday");

  if (callNum % 20 == 0)        /* Print header every 20 lines */
    printf(" Elapsed Value Interval\n");

  if (gettimeofday(&curr, NULL) == -1)
    errExit("gettimeofday");
  printf("%-7s %6.2f", msg, curr.tv_sec - start.tv_sec +
      (curr.tv_usec - start.tv_usec) / 1000000.0);

  if (includeTimer) {
    if (getitimer(ITIMER_REAL, &itv) == -1)
      errExit("getitimer");
    printf("  %6.2f  %6.2f",
        itv.it_value.tv_sec + itv.it_value.tv_usec / 1000000.0,
        itv.it_interval.tv_sec + itv.it_interval.tv_usec / 1000000.0);
  }
  printf("\n");
  callNum++;
}

static void sigalrmHandler(int sig) {
  gotAlarm = 1;
}

int main(int argc, char *argv[]) {
  struct itimerval itv;
  clock_t prevClock;
  int maxSigs;            /* Number of signals to catch before exiting */
  int sigCnt;             /* Number of signals so far caught */
  struct sigaction sa;

  if (argc > 1 && strcmp(argv[1], "--help") == 0)
    usageErr("%s [secs [usecs [int-secs [int-usecs]]]]\n", argv[0]);

  sigCnt = 0;

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = sigalrmHandler;
  if (sigaction(SIGALRM, &sa, NULL) == -1)
    errExit("sigaction");

  /* Exit after 3 signals, or on first signal if interval is 0 */

  maxSigs = (itv.it_interval.tv_sec == 0 &&
      itv.it_interval.tv_usec == 0) ? 1 : 3;

  displayTimes("START:", FALSE);

  /* Set timer from the command-line arguments */

  itv.it_value.tv_sec = (argc > 1) ? getLong(argv[1], 0, "secs") : 2;
  itv.it_value.tv_usec = (argc > 2) ? getLong(argv[2], 0, "usecs") : 0;
  itv.it_interval.tv_sec = (argc > 3) ? getLong(argv[3], 0, "int-secs") : 0;
  itv.it_interval.tv_usec = (argc > 4) ? getLong(argv[4], 0, "int-usecs") : 0;

  if (setitimer(ITIMER_REAL, &itv, 0) == -1)
    errExit("setitimer");

  prevClock = clock();
  sigCnt = 0;

  for (;;) {
    /* Inner loop consumes at least 0.5 seconds CPU time */
    while (((clock() - prevClock) * 10 / CLOCKS_PER_SEC) < 5) {
      if (gotAlarm) {         /* did we get a signal? */
        gotAlarm = 0;
        displayTimes("ALARM:", TRUE);

        sigCnt++;
        if (sigCnt >= maxSigs) {
          printf("That's all folks\n");
          exit(EXIT_SUCCESS);
        }
      }
    }

    prevClock = clock();
    displayTimes("Main: ", TRUE);
  }

}


