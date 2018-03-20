## Executing programs

### process_time
Program loops and and uses clock() and times() to retive on CPU time during the loop

```console
$ ./process_time 10000000
CLOCKS_PER_SEC=1000000 sysconf(_SC_CLK_TCK)=100

At program start:
 clock() returns: 1286 clocks-per-sec (0.00 secs)
 times() yields: user CPU=0.00; system CPU: 0.00
After getppid() loop:
 clock() returns: 6356248 clocks-per-sec (6.36 secs)
 times() yields: user CPU=2.86; system CPU: 3.49
```

