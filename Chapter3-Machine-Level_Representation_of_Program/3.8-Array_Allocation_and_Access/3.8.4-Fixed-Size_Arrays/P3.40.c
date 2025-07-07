#include <stdio.h>

#define N 16
typedef int fix_matrix[N][N];

/** Original C code */
void fix_set_diag(fix_matrix A, int val) { 
    long i;
    for (i = 0; i < N; i++) {
        A[i][i] = val;
    }
}

/** Optimized C code */
void fix_set_diag_opt(fix_matrix A, int val) {
    int *Ptr = &A[0][0];
    int *Bend = &A[N][N];
    do {
        *Ptr = val;
        Ptr += 68;
    } while (Ptr != Bend);
}