#include "become_daemon.h"
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    becomeDaemon(0);

    /* Normally a daemon would live forever; we just sleep for a while */

    sleep((argc > 1) ? getInt(argv[1], GN_GT_0, "sleep-time") : 20);

    exit(EXIT_SUCCESS);
}

