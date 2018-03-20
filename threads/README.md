## Executing programs

### simple_thread
Program creates another thread then joins it; it uses pthread_create() syscall to create a new thread and pthread_join() to join it.

```console
$ ./simple_thread
Message from main()
Hello world
Thread returned 12
```

### thread_incr
Shows how concurrent programming can be hard. To threads incrementing a global variable without using mutex which leads to faulty behaviour. To avoid the problems that can occur when threads try to update a shared variable, we must use a mutex (short for mutual exclusion) to ensure that only one thread at a time can access the variable.

```console
$ ./thread_incr 100000
glob = 200000
$ ./thread_incr 1000000
glob = 1473724
```

### thread_incr_mutex
Same as above, but this program uses a mutex to protect access to the global variable glob

```console
$ ./thread_incr_mutex 1000000
glob = 2000000
```

### thread_cancel
Demonstrates the pthread_cancel() syscall. The main program creates a thread that executes an infinite loop, sleeping for a second and printing the value of a loop counter. Meanwhile, the main program sleeps for 3 seconds, and then sends a cancellation request to the thread that it created.

```console
$ ./thread_cancel
New thread started
Loop 1
Loop 2
Loop 3
Thread was canceled
```
