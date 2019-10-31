# kfifo

kfifo, a generic userspace FIFO implementation, port from Linux kernel

https://blog.csdn.net/liigo/article/details/100993236

----

## original source


The original source files come from Linux kernel tree (v5.3):

- https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/lib/kfifo.c
- https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/kfifo.h

The latest [git logs](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/log/lib/kfifo.c):

| Age | Commit message (Expand) | Author | Files | Lines |
| ---------|---------------------------------------------------------------------|-------------------|-----|--------|
2019-08-30  |Partially revert "kfifo: fix kfifo_alloc() and kfifo_init()"        |Linus Torvalds     |1    |-1/+2
2019-05-24  |treewide: Replace GPLv2 boilerplate/reference with SPDX - rule 61   |Thomas Gleixner    |1    |-15/+1
2018-06-12  |treewide: kmalloc() -> kmalloc_array()                              |Kees Cook          |1    |-1/+1
2018-03-27  |kfifo: fix inaccurate comment                                       |Martin Kelly       |1    |-1/+1
2014-08-08  |kfifo: use BUG_ON                                                   |Himangi Saraogi    |1    |-4/+2
2013-11-15  |kfifo: kfifo_copy_{to,from}_user: fix copied bytes calculation      |Lars-Peter Clausen |1    |-2/+2
2013-02-27  |kfifo: fix kfifo_alloc() and kfifo_init()                           |Stefani Seibold    |1    |-4/+2
2013-02-27  |kfifo: move kfifo.c from kernel/ to lib/                            |Stefani Seibold    |1    |-0/+609
