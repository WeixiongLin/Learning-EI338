# Homework 8

## 环境配置

- 安装 gcc, g++
- 配置 tasks.json: 由于 openMP 的使用命令形式为
    ```shell
    g++ test.cpp -o test -fopenmp
    2 ./test
    ```
    因此为了不用每次都在命令行中 compile->run, 需要修改 tasks.json["args"]


## Issues
- 想要正确计算出 vector 的和, 累加变量 sum 需要加 lock.
- 本次实验需要比较得出 time acceleration ratio。而 clock 函数计算的是程序的 CPU 总时间, 所以结果上不会有加速。
    
    应该使用 omp_get_wtime() 统计时间。


## 项目结构

Homework8/
    |--.vscode/: vscode config
    |--bin/: executable files
    |--serial.cpp: serial sum function on Linux
    |--parallel.cpp: parallel sum fuction on Linux
    |--parallel_clock.cpp: use clock for time caculation
    |--gongchen.cpp: Gongchen's solution on Window OS
    |--openMP_hello.cpp: testing use of openMP
    |--README.md
