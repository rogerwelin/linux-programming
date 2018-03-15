
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
