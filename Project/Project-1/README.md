# Project-1
Introduction to Linux Kernel Modules

## 实验过程

### Kernel Modules Overview

查看当前运行的 kernel modules
```
lsmod
```

执行 Makefile
```
make
```

会编译出一些文件, simple.ko 表示编译出的 kernel module

### Loading and Removing Kernel Modules

Kernel Module 的 load command:
```
sudo insmod simple.ko
```
查看 kernel log buffer 来检查输出
```
dmesg
```

remove kernel module
```
sudo rmmod simple
```
可以用 dmesg 查看是否被 remove

因为 kernel log buffer 很容易满, 所以可以定期清理一下
```
sudo dmesg -c
```

由于写 kernel 程序其实 debug 没什么作用, 所以要经常做 make->load->remove->dmesg 的操作来保证正确性


由于我们现在处于 kernel mode 中, 所以可以做一些特有的操作:

- <linux/hash.h>: `printk(KERNINFO "%lu∖n", GOLDENRATIOPRIME)` 输出常数
- <linux/gcd.h>: `unsigned long gcd(unsigned long a, unsigned b)`
    调用 gcd 函数
- <asm/param.h>: 输出 const HZ
- <linux/jiffies.h>: 输出 variable jiffies
- 利用 simple_init(), simple_exit() 中 jiffies 计算模块 load->remove 经历的时间\
    T = \delta jiffies / HZ

执行 simple 的代码:
```
sudo dmesg -c
clear
make
sudo insmod simple.ko
dmesg
sudo rmmod simple
dmesg
```

### The /proc File System
/proc 是内核中的一个内存空间, proc.c 的实验目的是在 kernel 态中向 /proc buffer 区域写入 Hello World,
然后 copy 到 user_buffer 中. 并在退出内核态后从 user buffer 把 Hello world 输出.

执行 proc 的代码:
```
sudo dmesg -c
clear
make
sudo insmod proc.ko
dmesg
sudo rmmod proc
dmesg
```

### Assignment

1. 设计一个 kernel module, 创建 /proc/jiffies, 当 /proc/jiffies 被读取的时候返回 jiffies 的状态
```
sudo rmmod jiffies_module
make
sudo insmod jiffies_module.ko
cat /proc/jiffies
```


2. 设计 kernel module 创建 /proc/seconds, 当 /proc/seconds 被读取时返回从 module load 以来经历的时间
```
clear
sudo rmmod seconds_module
make
sudo insmod seconds_module.ko
cat /proc/seconds
```

