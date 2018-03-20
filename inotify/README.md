## Executing programs

### demo_inotify
Uses the inotify API to monitor file events

```console
$ ./demo_inotify tags.txt
Watching tags using wd 1
# sleeps here until we trigger operation on file tags.txt for example wirte to the file
Read 16 bytes from inotify fd
    wd = 1; mask = IN_MODIFY
Read 16 bytes from inotify fd
    wd = 1; mask = IN_OPEN
Read 16 bytes from inotify fd
    wd = 1; mask = IN_MODIFY
Read 16 bytes from inotify fd
    wd = 1; mask = IN_CLOSE_WRIT
```

