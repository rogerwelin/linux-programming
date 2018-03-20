## Executing programs

### sched_view & sched_set
View and modifying scheduling policies and priorities. Syscall sched_setscheduler() is used to set the policy and priority of the process. The sched_getparam() syscall returns a process policies.

```console
$ sleep 160 &       # create a process
[2] 30920
$ ./sched_view 30920
30920: OTHER  0
$ sudo ./sched_set f 25 30920   # switch process to SCHED_FIFO policy, priority 25
$ ./sched_view 30920            # verify change
30920: FIFO  25
```

| Policy        | Description                              |
| ------------- |-----------------------------------------:|
| SCHED_FIFO    | Realtime first-in first-out |
| SCHED_RR      | Realtime round-robin |
| SCHED_OTHER   | Standard round-robin time-sharing |
| SCHED_BATCH   | Similar to SCHED_OTHER, but intended for batch execution |
| SCHED_IDLE    | Similar to SCHED_OTHER, but with priority even lower than nice value +19 |
