/**
 * @file test.cpp
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
    int n = 10000000;
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
    omp_set_num_threads(4);
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++){
        sum += a[i];
    }

    printf("sum: %d\n", sum);
    endTime = clock();//计时结束
    printf("The run time is: %lf s\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}
