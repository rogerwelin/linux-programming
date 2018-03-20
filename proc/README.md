## Executing programs

### mem_segments
Demonstrates variables in different memory segments (text segment, data segment, heap segment)

```console
$ ./mem_segment
The square of 9973 is 99460729
```

### necho
Demonstrates how cmd-line args work, see int argc and char `*argv[]

```console
$ ./necho hello world
argv[0] = ./necho
argv[1] = hello
argv[2] = world
```

### display_env
Prints all environment variables in the shell using the global variable __extern char **environ__

```console
$ ./display_env
TERM=xterm-256color
SHELL=/bin/bash
...
```

