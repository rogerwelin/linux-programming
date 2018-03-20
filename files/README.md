## Executing programs

### t_stat
Demonstrates how to use the stat() syscall to retrieve information about a file. If using the -l flag then lstat() syscall will be used instead. 

```console
$ ./t_stat -l Makefile
File type:                regular file
Device containint i-node: major=0   minor=25
I-node number:      3678
Mode:               100644 (rw-r--r--)
Number of (hard) links  1
Ownership:              UID=1000   GID=1000
File size:                    238 bytes
Optimal I/O block size:       4096 bytes
512b blocks allocated:        8
Last file access:             Tue Mar 20 20:32:49 2018
Last file modification:       Mon Feb 19 21:10:44 2018
Last status change:           Mon Feb 19 21:10:44 2018
```

