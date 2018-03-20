## Executing programs

### ouch
Simple demonstration how to catch signals in your program using the signal() syscall

```console
$ ./ouch
0
1
# press control-c, triggers signal
ouch!
2
3
# press ctrl+4 
Quit (core dumped)
```

### sig_sender & sig_receiver
Sending signals between processes, showing that signals are not queued

```console
$ ./sig_receiver 15 &
[2] 28972
./sig_receiver: PID is 28972
./sig_receiver: sleeping for 15 seconds

$ ./sig_sender 28972 1000000 10 2
./sig_sender: sending signal 10 to process 28972 1000000 times
./sig_sender: exiting
./sig_receiver: pending signals are:
		2 (Interrupt)
		10 (User defined signal 1)
sig_receiver: signal 10 caught 1 time
```
