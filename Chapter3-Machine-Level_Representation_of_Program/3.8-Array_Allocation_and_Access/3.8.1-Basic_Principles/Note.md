

Arrays in C are one means of aggregating 'scalar data' into larger data types. 


## Practice PProblem 3.36
Consider the following declarations: 
```
int P[5];
short Q[2];
int **R[9];
double *S[10];
short *T[2];
```
Fill in the following table describing the element size, the total size, and the address of element i for each of these arrays.

Array   Element size    Total size      Address    Element i
--------------------------------------------------------------------------------------
  P     4 bytes         4 * 5 bytes      xp        xp + i*4
  Q     2 bytes         2 * 2 bytes      xq        xq + i*2
  R     8 bytes         8 * 9 bytes      xr        xr + i*8       
  S     8 bytes         8 * 10 bytes     xs        xs + i*8
  T     8 bytes         8 * 2 bytes      xt        xt + i*8