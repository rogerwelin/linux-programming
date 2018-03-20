## Executing programs

### rlimit_nproc.c
Program uses setrlimit() syscall to set soft and hard limits on the number of processes that a user may create. In example below we are only able to create 23 childs because the user were already running 4

```console
$ ./rlimit_nproc 30 100
Initial maximum process limits:  soft=3841; hard=3841
New maximum process limits:       soft=30; hard=100
Child 1 (PID=30986) started
Child 2 (PID=30987) started
Child 3 (PID=30988) started
....
Child 22 (PID=31007) started
Child 23 (PID=31008) started
ERROR [EAGAIN/EWOULDBLOCK Resource temporarily unavailable] fork
```

