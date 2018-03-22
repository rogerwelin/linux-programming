## Executing programs

### pshm_create
This program creates a shared memory object whose size is specified by a command-line argument, and maps the object into the process’s virtual address space.

```console
$ ./pshm_create -c /demo_shm 1000
$ ls -l /dev/shm
lrwxrwxrwx 1 root root 8 Feb 20 21:30 /dev/shm -> /run/shm
```

### pshm_write & pshm_read
Writes and read from the shared memory object created by pshm_create program

```console
$ ./pshm_write /demo_shm 'hello'
Resized to 5 bytes
copying 5 bytes
$ ./pshm_read /demo_shm
hello
```

