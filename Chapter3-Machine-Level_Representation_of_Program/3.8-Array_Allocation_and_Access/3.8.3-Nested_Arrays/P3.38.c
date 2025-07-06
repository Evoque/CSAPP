

#include <stdio.h>


// where M and N are constants declared with '#define'

#define M 5
#define N 7

long P[M][N];
long Q[N][M];

long sum_element(long i, long j) {
    return P[i][j] + Q[j][i];
}

/**
 * long sum_element(long i, long j)
 * i in %rdi, j in %rsi
 * 
 * sum_element:
 *  
 * 
 * 
 */