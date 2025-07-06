

``` c
int A[5][3];
```
is equivalent to the declaration
```c
typedef int row3_t[3];
row3_t A[5];
```

----------------------
|[0][0]|    |        |   
----------------------
|      |    |        |   
----------------------
|      |    |        |   
----------------------
|      |    |        |   
----------------------
|      |    |A[4][2] |   
----------------------
The array elements are ordered in memory in `row-major` order.
实际在存储的视角
        ------------
A[0]    |  A[0][0]  |  Xa
        ------------
        |  A[0][1]  |  Xa+4   
        ------------
        |  A[0][2]  |  Xa+8 
        ------------       
A[1]    |  A[1][0]  |  ... 
        ------------
        |  A[1][1]  |       
        ------------       
        |  A[1][2]  |       
        ------------       
        
T D[R][C]:
array element D[i][j] is at memory address:
```assemble
&D[i][j] = xd + L(C*i + j)
```

