## Executing programs

### svshm_xfr_writer & svshm_xfr_reader
Displays two processes sharing memory. Writer transfer blocks of data from stdin to sysV shared memory
segment. And reader transfer blocks of data from sysV memory segment to stdin. shmget() syscall creates
a shared memory segment, and shmat() attaches to a shared memory segment for reading.

```console
$ wc -c /etc/services
19558 /etc/services
$ ./svshm_xfr_writer < /etc/services &
[2] 31298
$ ./svshm_xfr_reader > out.txt
Received 19558 bytes (20 xfrs)      # message from reader
Sent 19558 bytes (20 xfrs)          # message from writer
$ diff /etc/services out.txt
```

