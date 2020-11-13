/**
 * @file openMP_hello.cpp
 * @brief 
 * @author WeixiongLin (wx_lin@outlook.com)
 * @version 1.0
 * @date 2020-11-13
 * 
 * @copyright Copyright (c) 2020  WeixiongLin
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-11-13 <td>1.0     <td>WeixiongLin     <td>
 * </table>
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<vector>
using namespace std;


int main()
{
    int nthreads, tid;
    int n = 100000000;
    // 求和的目标 vector
    vector<int> a;
    for(int i = 0; i < n; i++)
        a.push_back(i);
    
    // 计时模块
    clock_t start, finish;
    clock_t startTime,endTime;
    double duration;
    startTime = clock();//计时开始
    

    // openMP
    /* Fork a team of threads giving them their own copies of variables */
    int sum = 0;
    #pragma omp parallel private(nthreads, tid)
    {
        /* Obtain thread number */
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);
        printf("nthreads: %d \n", nthreads);
        
        /* Only master thread does this */
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

    }  /* All threads join master thread and disband */

    printf("sum: %d\n", sum);
    endTime = clock();//计时结束
    printf("The run time is: %lf s\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}
