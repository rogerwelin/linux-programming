## Executing programs

### mmcat
Demonstrates the syscall mmap() to create private file mapping. Simple version of cat, it maps the entire file named in its command-line argument, and then writes the contents of the mapping to standard output.

```console
$ ./mmcat Makefile
# file content of Makefile
```


