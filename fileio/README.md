## Running programs

### Copy
Is a cp clone. Demonstrates open(), read() & write() syscalls

```console
$ ./copy oldfile.txt newfile.txt 
```

### seek_io
seek offset using lseek() syscall to 100,000, write "abc". Seek offset to 10,000, read 5 bytes from hole

```console
$ touch apa.txt
$ ./seek_io apa.txt s100000 wabc
s100000: seek succeeded
wabc: wrote 3 bytes
$ ./seek_io apa.txt s10000 R5
s10000: seek succeeded
R5: 00 00 00 00 00
```
### t_readv
Performing scatter input with readv() syscall. readv() reads atomically in a single process, reads from fd into memory buffers (scatters into buffers defined by iov[])

```console
$ ./t_readv Makefile
total bytes requested: 248; bytes read: 248
```
