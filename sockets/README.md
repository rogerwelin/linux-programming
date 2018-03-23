
A prefix identifies the socket domain in which the program operates, 
and the socket type employed. The socket domain is indicated by one
or two letters:


| Prefix        | Protocol               |
| ------------- |:----------------------:|
| u             | UNIX                   |
| i             | Internet (IPv4 + IPv6) |
| i6            | Internet (IPv6 only    |


The socket type is one of the following:

* d     datagram
* s     socket


The suffix indicates whether the program is client or server.

Example: id_echo_sv.c --> server that uses datagram sockets in internet domain

### us_xfr_sv & us_xfr_cl
A simple unix domain socket server + client. Server does the following:
create a socket with socket() syscall, bind the socket to an address, mark socket as listening, execute infinite loop to handle incoming client requests (accept connection, read data from the connected socket & write to stdout, close the connection)

The client creates a socket, contruct address for the server and connect to that socket.

```console
$ ./us_xfr_sv &
$ ls -lF /tmp/us_xfr
srwxrwxr-x 1 vagrant vagrant 0 Mar 23 18:42 /tmp/us_xfr=      #examine socket file
$ ./us_xfr_cl < us_xfr.h
$ # server will now pring the content that the client sent it
```

### ud_ucase_sv & ud_ucase_cl
Simple unix domain datagram server and client. Same as above but using UDP

```console
$ ./ud_ucase_sv &
[1] 20113
$ ./ud_ucase_cl hello world                           # Send 2 messages to server 
Server received 5 bytes from /tmp/ud_ucase_cl.20150
Response 1: HELLO
Server received 5 bytes from /tmp/ud_ucase_cl.20150
Response 2: WORLD
$ ./ud_ucase_cl 'long message'                        # Send 1 longer message to server 
Server received 10 bytes from /tmp/ud_ucase_cl.20151
Response 1: LONG MESSA
```

### i6d_ucase_dv i6d_ucase_cl
Server client example using datagram, AF_INET6 socket type and datagram sockets.

```console
$ ./i6d_ucase_sv &
[1] 31047
$ ./i6d_ucase_cl ::1 ciao             # send to server
Server received 4 bytes from (::1, 32770) Response 1: CIAO
```


### is_seqnum_sv & is_seqnum_cl
An iterative server that uses a stream socket (TCP) to communicate with clients.

```console
$ ./is_seqnum_sv &
[2] 31838
$ ./is_seqnum_cl localhost
Connection from (localhost, 59401)
Sequence number: 0
$ ./is_seqnum_cl localhost 10
Connection from (localhost, 59402)
Sequence number: 1
$ ./is_seqnum_cl localhost
Connection from (localhost, 59403)
Sequence number: 11
$ nc localhost 50000
Connection from (localhost, 59404)
1
12
```

### t_gethostbyname
Using the gethostbyname() syscall to retrieve host information:

````console
$ ./t_gethostbyname www.github.com
Canonical name: github.com
        alias(es):      www.github.com
        address type:   AF_INET
        address(es):    192.30.253.112 192.30.253.113
```

