## Executing programs

### posix mq programs
Programs described below demonstrates how to send messages on a POSIX message queue. Example send message in different priorities which are read first.

```console
$ ./pmsg_create -cx /mq
$ ./pmsg_send /mq msg-a 5 
$ ./pmsg_send /mq msg-b 0 
$ ./pmsg_send /mq msg-c 10
$ ./pmsg_receive /mq
Read 5 bytes; priority = 10 msg-c
$ ./pmsg_receive /mq
Read 5 bytes; priority = 5 msg-a
$ ./pmsg_receive /mq
Read 5 bytes; priority = 0 msg-b
$ ./pmsg_unlink /mq       # remove message queue
```

