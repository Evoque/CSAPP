#include <stdio.h>

typedef int row3_t[3];


int main() {
    // 声明一个5行3列的二维数组
    row3_t A[5];
    
    // 输出类型信息
    printf("数组A的类型信息：\n");
    printf("========================\n");
    printf("sizeof(A) = %zu 字节\n", sizeof(A));
    printf("\n");
    
    // 填充样例数据
    // 使用嵌套循环填充数据
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            A[i][j] = (i + 1) * 10 + (j + 1);  // 生成有规律的数据
        }
    }
    
    // 打印数组内容
    printf("二维数组 A[5][3] 的内容：\n");
    printf("========================\n");
    
    for (int i = 0; i < 5; i++) {
        printf("第 %d 行: ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
    
    
    return 0;
}
