## Executing programs

### real_timer
A timer allows a process to schedule a notification for itself to occur at some time in the future.
Program uses setitimer() and getitimer() sycalls 

```console
$ ./real_timer 4
 Elapsed Value Interval
START:    0.00
Main:     1.00    3.00    0.00
Main:     2.00    2.00    0.00
Main:     3.00    1.00    0.00
ALARM:    4.00    0.00    0.00
That's all folks
```

