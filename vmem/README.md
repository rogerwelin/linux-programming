## Executing programs

### t_mprotect
Demonstrates the mprotect() syscall which changes protection on the virtual memory specified by a range.
This program creates an anonymous mapping that initially has all access denied (PROT_NONE). The program then changes the protection on the region to read plus write. 

```console
$ ./t_mprotect
Before mprotect()
7f7076178000-7f7076278000 ---s 00000000 00:04 114201                     /dev/zero (deleted)
After mprotect()
7f7076178000-7f7076278000 rw-s 00000000 00:04 114201                     /dev/zero (deleted)
```

