/**
 * @file parallel.cpp
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
    
    // openMP
    /* Fork a team of threads giving them their own copies of variables */
    double start = omp_get_wtime( );
    int sum = 0;
    omp_set_num_threads(4);
    #pragma omp parallel for num_threads(4) reduction(+:sum)
    for(int i = 0; i < n; i++){
        sum += a[i];
    }

    double end = omp_get_wtime();
    // double wtick = omp_get_wtick( );
    

    printf("sum: %d\n", sum);
    printf("start = %.4g\nend = %.4g\n", start, end);
    printf("diff = %.4g\n", end - start);
    return 0;
}
