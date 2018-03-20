## Executing programs

### t_fork
Demonstrate how to fork a child process using the fork() syscall. Program shows that a child process gets its own copy of the stack and data segments at the time of the fork(), and is able to modify variables in these segments without affecting the parent

```console
$ ./t_fork
PID=29102 (child)  idata=333 istack=666
PID=29101 (parent) idata=111 istack=222
```

### fork_file_sharing
When fork() is performed child receives all parents open file descriptors. These are shared, so if the child updates the file offset in one file descriptor, the change is visible for the parent. Program demonstrates this.

```console
$ ./fork_file_sharing
File offset before fork(): 0
O_APPEND flag before fork() is: off
Child has exited
File offset in parent: 1000
O_APPEND flag in parent is: on
```

### fork_whos_on_first
After a fork(), it is indeterminate which process—the parent or the child—next has access to the CPU. Program performs a fork(), after each fork parent and child prints loop counter and string indicating if parent or child. 99.9% the parent should get CPU time first

```console
$ ./fork_whos_on_first 1000000
# analyze output
```

### fork_sig_sync
Demonstrates how to avoid race condition by synchronizing with signals. Calls fork(), child doing some work, after completed send a signal to parent which resumes work. 

```console
$ ./fork_sig_sync
[22:03:19 30232] Parent about to wait for signal
[22:03:19 30233] Child started - doing some work
[22:03:21 30233] Child about to signal parent
[22:03:21 30232] Parent got signal
```

