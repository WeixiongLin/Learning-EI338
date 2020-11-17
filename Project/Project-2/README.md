# Project-2
Implementation of a shell interface with C program. It accepts commands and run in seperate process.

有一说一 @github.com/keithnull 确实是强, project 2 我自己做完之后去看了他的代码.
然后羞愧难当, 就把自己写的删了. 差距体现在两个方面:
1. 程序结构: 和 keithnull 结构还是不够清晰
2. 鲁棒性: 很多细节没考虑, 比如用户可能输入 `!!&*@`, 这时候就应该用 `strncmp` 而不是 `strcmp` (指定要毕竟前两位)


## Unix Shell

### Overview
Terminal 给出提示符 `osh>`, 用户在后面输入命令.
```
osh>cat prog.c &
```
通常用一个 parent process `fork()` 一个 child process 执行指令, parent prosess 等待 child 执行结束.
如果希望 parent 和 child 并发执行, 需要在 command 结尾加 `&`.

After reading user input, the steps are:
(1) fork a child process using fork()
(2) the child process will invoke execvp()
(3) parent will invoke wait() unless command included &

#### Executing Command in a Child Process
读入 command 之后, 应该把 command 解析成 token 存放在 args 中.
然后执行函数 execvp(char *command, char *params[]), 在当前项目中为 exevp(args[0], args).
记得检查 command 末尾有无 `&`, 来决定是否 `wait()`.

#### Creating a History Feature
用户可以通过输入 `!!` 再次执行刚刚执行过的指令, 要求把 `!!` 对应的指令 echo 到 terminal 中.
`!!` 执行的指令也要被放到 History 中, 如果没有 Recent commands 要返回 "No commands in history."

#### Redirecting Input and Output
支持用户使用 `> <` 把 ouput 和 input 重定向. 例如:
```
osh>ls > out.txt
osh>sort < in.txt
```
这样操作需要用到 `dup2(fd, STDOUTFILENO)`, fd 是 output.txt 的 file descriptor.

#### Communication via a pipe
我们希望一个 command 的输出作为另一个 command 的输入.
```
osh>ls -l | less
```
把 `ls -l` 的输出作为 `less` 的输入, 实现方式是:
parent process 创建 process 执行 `ls -l`, 它也创建自己的 child process 执行 `less`,
并用 pipe 进行连接.


## Linux Kernel Module for Task Information

