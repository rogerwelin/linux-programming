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

### multi_wait
Utilizes the wait() syscall that waits for one or more children to terminate. This program creates multiple child processes, one per (integer) command-line argument. Each child sleeps for the number of seconds specified in the corresponding command-line argument and then exits. In the meantime, after all children have been created, the parent process repeatedly calls wait() to monitor the termination of its children. This loop continues until wait() returns –1

```console
$ ./multi_wait 7 1 4
[22:10:28] child 2 started with PID 30326, sleeping 1 seconds
[22:10:28] child 3 started with PID 30327, sleeping 4 seconds
[22:10:28] child 1 started with PID 30325, sleeping 7 seconds
[22:10:29] wait() returned child PID 30326 (numDead=1)
[22:10:32] wait() returned child PID 30327 (numDead=2)
[22:10:35] wait() returned child PID 30325 (numDead=3)
No more children - bye!
```

### child_status
Uses waitpid() syscall to retrieve status of child process. Also demonstrate send signal ABRT to core dump process

```console
$ ulimit -c unlimited   # allow core cumps
$ ./child_status &
[2] 30330
Child started with PID = 30331
$ kill -ABRT 30331
waitpid() returned: PID=30331; status=0x0086 (0,134)
child killed by signal 6 (Aborted) (core dumped)
```

### make_zombie
Demonstrates how to create a zombie process. Zombies are created if the parent exits and fails to calling wait()

```console
$ ./make_zombie
Parent PID=30684
Child (PID=30685) exiting
30684 pts/0    00:00:00 make_zombie
30685 pts/0    00:00:00 make_zombie <defunct>
After sending SIGKILL to zombie (PID=30685):
30684 pts/0    00:00:00 make_zombie
30685 pts/0    00:00:00 make_zombie <defunct>
```

### make_zombie
Demonstrates how to create a zombie process. Zombies are created if the parent exits and fails to calling wait()

```console
$ ./make_zombie
Parent PID=30684
Child (PID=30685) exiting
30684 pts/0    00:00:00 make_zombie
30685 pts/0    00:00:00 make_zombie <defunct>
After sending SIGKILL to zombie (PID=30685):
30684 pts/0    00:00:00 make_zombie
30685 pts/0    00:00:00 make_zombie <defunct>
```

### t_execve & t_envargs
Uses  execve() syscall; execve() loads a new program into a process memory. execve() is also used by interpreted languages using the shebang (#!)

```console
$ ./t_execve ./t_envargs      # all the output is printed by t_envargs
argv[0] = t_envargs
argv[1] = hello world
argv[2] = goodbye
environ: GREET=salut
environ: BYE=adieu
```
