#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int flags, accessMode, fd;

int main() {
  fd = open("tags", O_RDONLY);
  if (fd == -1)
    errExit("open");

  flags = fcntl(fd, F_GETFL);  /* third arg is not required */
  if (flags == -1)
    errExit("fnctl");

  if (flags & O_SYNC)
    printf("writes are synchronized\n");

  accessMode = flags & O_ACCMODE;
  if (accessMode == O_RDONLY)
    printf("file is not writable\n");

  /* add flag to already opened file */
  flags |= O_APPEND;
  if (fcntl(fd, F_SETFL, flags) == -1)
    errExit("fnctl");

}
