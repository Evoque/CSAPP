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

/** Optimized C code 1 */
// void fix_set_diag_opt(fix_matrix A, int val) {
//     int *Ptr = &A[0][0];
//     int *Bend = &A[N][N];
//     do {
//         *Ptr = val;
//         Ptr += 68;
//     } while (Ptr != Bend);
// }

/** Optimized C code 2 */
void fix_set_diag_opt(fix_matrix A, int val) {
    int *Abase = &A[0][0];
    // i 作为要赋值的matrix的索引
    int i = 0;
    long iEnd = N * (N + 1);
    do {
        Abase[i] = val;
        i += N + 1;
    } while (i < N);
}

void test_array_pointer(fix_matrix A){
    int *Abase = &A[0][0];

    printf("A: %p\n", A);
    printf("Abase: %p\n", Abase);

    printf("A: %p\n", &A[0][1]);
    printf("Abase[1]: %p\n", &Abase[1]);
}

int main() {
    fix_matrix A = {{0, 0}, {1, 1}};
    test_array_pointer(A);

    return 0;
}