/**
 * @file gongchen.cpp
 * @brief 
 * @author gongchen
 * @version 1.0
 * @date 2020-11-13
 * 
 * @copyright Copyright (c) 2020  gongchen
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-11-13 <td>1.0     <td>gongchen    <td>内容
 * </table>
 */

#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <vector>

using namespace std;


int size = 100000;

int main() {
    vector<int> x(size, 1);
    LARGE_INTEGER tc,t1,t2,t3,t4;
    QueryPerformanceFrequency(&tc);
    cout<<"The size of the vector is "<<size<<endl;
    long long sum1 = 0;
    QueryPerformanceCounter(&t1);
    #   pragma omp parallel for num_threads(4) reduction(+: sum1)
    for (int i = 0; i < size; i++)
        sum1 += x[i];
    QueryPerformanceCounter(&t2);
    double time1 = (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart;

    cout << "The result of parallelism: " << sum1 << endl;
    cout << "Running time with parallelism: " << time1 << " s" << endl;

    // test the process without parallelism
    long long sum2 = 0;
    QueryPerformanceCounter(&t3);
    for (int i = 0; i < size; i++)
        sum2 += x[i];
    QueryPerformanceCounter(&t4);
    cout << "The result of without parallelism: " << sum2 << endl;
    double time2 = (double)(t4.QuadPart-t3.QuadPart)/(double)tc.QuadPart;
    cout << "Running time without parallelism: " << time2 << " s" << endl;

    // present the speedup ratio
    double speedup = (double)(time2) / (time1);
    cout << "The speedup ratio is: " << speedup << endl;

    // check the correctness of parallelism
    string s = (sum1 == sum2) ? "Correct" : "Wrong";
    cout << "The answer of parallelism is " << s;
    return 0;
}
