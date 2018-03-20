## Executing programs

### list_files
A ls clone which uses opendir(), readdir() and closedir() sycalls to list the contents of each dir supplied as a cmd line argument

```console
$ ./list_files /var/opt/ /tmp/
...
```

### nftw_dir_tree
Uses nftw() syscall to recursively walk through an entire directory subtree (really fast) which lets you perform some operation for each file in the subtree

```console
$ ./nftw_dir_tree /tmp/ -d
...
```

