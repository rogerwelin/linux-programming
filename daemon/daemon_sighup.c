#include <sys/stat.h>
#include <signal.h>
#include "become_daemon.h"
#include "tlpi_hdr.h"

static const char *LOG_FILE = "/tmp/ds.log";
static const char *CONFIG_FILE = "/tmp/ds.conf";

/* Set nonzero on receipt of SIGHUP */
static volatile sig_atomic_t hupReceived = 0;

#include <time.h>
#include <stdarg.h>

static FILE *logfp;                 /* Log file stream */

static void logMessage(const char *format, ...) {
    va_list argList;
    const char *TIMESTAMP_FMT = "%F %X";        /* = YYYY-MM-DD HH:MM:SS */
#define TS_BUF_SIZE sizeof("YYYY-MM-DD HH:MM:SS")       /* Includes '\0' */
    char timestamp[TS_BUF_SIZE];
    time_t t;
    struct tm *loc;

    t = time(NULL);
    loc = localtime(&t);
    if (loc == NULL ||
           strftime(timestamp, TS_BUF_SIZE, TIMESTAMP_FMT, loc) == 0)
        fprintf(logfp, "???Unknown time????: ");
    else
        fprintf(logfp, "%s: ", timestamp);

    va_start(argList, format);
    vfprintf(logfp, format, argList);
    fprintf(logfp, "\n");
    va_end(argList);
}

/* Open the log file 'logFilename' */
static void logOpen(const char *logFilename) {
    mode_t m;

    m = umask(077);
    logfp = fopen(logFilename, "a");
    umask(m);

    /* If opening the log fails we can't display a message... */

    if (logfp == NULL)
        exit(EXIT_FAILURE);

    setbuf(logfp, NULL);                    /* Disable stdio buffering */

    logMessage("Opened log file");
}

/* Close the log file */
static void logClose(void) {
    logMessage("Closing log file");
    fclose(logfp);
}

static void readConfigFile(const char *configFilename) {
    FILE *configfp;
#define SBUF_SIZE 100
    char str[SBUF_SIZE];

    configfp = fopen(configFilename, "r");
    if (configfp != NULL) {                 /* Ignore nonexistent file */
        if (fgets(str, SBUF_SIZE, configfp) == NULL)
            str[0] = '\0';
        else
            str[strlen(str) - 1] = '\0';    /* Strip trailing '\n' */
        logMessage("Read config file: %s", str);
        fclose(configfp);
    }
}

static void sighupHandler(int sig) {
  hupReceived = 1;
}

int main(int argc, char *argv[]) {
  const int SLEEP_TIME = 15;              /* time to sleep between messages */
  int count = 0;                          /* number of completed SLEEP_TIME interval */
  int unslept;
  struct sigaction sa;                    /* time remaining in sleep interval */

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = sighupHandler;
  // 2
  if (sigaction(SIGHUP, &sa, NULL) == -1)
    errExit("sigaction");

  // 3
  if (becomeDaemon(0) == -1)
    errExit("becomeDaemon");

  // 4
  logOpen(LOG_FILE);
  // 5
  readConfigFile(CONFIG_FILE);

  unslept = SLEEP_TIME;

  for (;;) {
    // 6
    unslept = sleep(unslept);             /* Returns > 0 if interrupted */

    // 7
    if (hupReceived) {                    /* If we got SIGHUP... */
      logClose();
      logOpen(LOG_FILE);
      readConfigFile(CONFIG_FILE);
      hupReceived = 0;                    /* Get ready for next SIGHUP */
    }

    if (unslept == 0) {                   /* on completed interval */
      count++;
      // 8
      logMessage("Main: %d", count);
      unslept = SLEEP_TIME;               /* Reset interval */
    
    }
  }
}
