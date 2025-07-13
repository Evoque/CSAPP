

#include <stdio.h>

#define N 16
typedef int fix_matrix[N][N];

/**
 * 矩阵乘法？A的第i行与B的第k列(每一项的乘积加和)
 */
int fix_prod_ele (fix_matrix A, fix_matrix B, long i, long k) {
    long j;
    int result = 0;

    for (j = 0; j < N; j++) {
        result += A[i][j] * B[j][k];
    }

    return result;
}

/**
 * 我懂了！
 * *Aptr: i行的指针
 * *Bptr: k列的指针
 * 通过指针的移动来便利行中的所有元素和列中所有的元素（注意行、列是相等的）
 * 
 * @qa: 从`fix_prod_ele`优化成`fix_prod_ele_opt`, 哪方面提升了
 */
int fix_prod_ele_opt(fix_matrix A, fix_matrix B, long i, long k) {
    int *Aptr = &A[i][0];   /* Points to elements in row i of A */
    int *Bptr = &B[0][k];   /* Points to elements in column k of B */
    int *Bend = &B[N][k];   /* Marks stopping point for Bptr */
    int result = 0;
    do {                            /* No need for initial test */
        result += *Aptr * *Bptr;    /* Add next product to sum */
        Aptr ++;                    /* Move Aptr to next column */
        Bptr += N;                  /* Move Bptr to next row */
    } while (Bptr != Bend);         /* Test for stopping point */

    return result;
}

// ==> 结论：一图搞定，见图片"fixed-size_arrays.jpg"