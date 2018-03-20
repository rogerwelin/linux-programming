## Executing programs

### simple_pipe
Pipes can be used to communicate between processes, an IPC mechanism. Program uses a pipe to communicate between parent and child process. pipe() syscall to create a pipe, child reads from pipe and parent writes to the pipe

### pipe_sync
Pipes can also be used as a means of process synchronization. To perform the synchronization, the parent builds a pipe before creating the child processes. Each child inherits a file descriptor forkthe write end of the pipe and closes this descriptor once it has completed its action. After all ofthe children have closed their file descriptors for the write end of the pipe, the parent’s read() from the pipe will complete, returning end-of-file. At this point, the parent is free to carry on to do other work.

```console
$ ./pipe_sync 4 2 6
23:17:20 Parent started
23:17:22 Child 2 (PID=31088) closing pipe
23:17:24 Child 1 (PID=31087) closing pipe
23:17:26 Child 3 (PID=31089) closing pipe
23:17:26 Parent ready to go
```

