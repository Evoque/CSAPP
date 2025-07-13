- A function that returns a floating-point value does so in register %xmm0.
- All XMM registers are caller saved. The callee may overwrite any of these
registers without first saving it.
- 参数中最多能携带8个浮点数参数，是不是说通过寄存器最多能传递14个参数（6个通用+8个XMM）


有样例funct
```c
double funct (double a, float x, double b, int i) {
    return a*x - b/i;
}
```

```Assembly
double funct (double a, float x, double b, int i)
a in %xmm0, x in %xmm1, b in %xmm2, i in %edi

funct:
    - The following two instructions convert x to double
    vunpcklps     %xmm1, %xmm1, %xmm1
    vcvtps2pd     %xmm1, %xmm1
    vmulsd     %xmm0, %xmm1, %xmm0     - Multiply a by x
    vcvtsi2sd  %edi,  %xmm1, %xmm1     - Convert i to double
    vdivsd     %xmm1, %xmm2, %xmm2     - Compute b/i
    vsubsd     %xmm2, %xmm0, %xmm0     - Subtract from a*x
    ret
```

- AVX floating-point operations cannot have *immediate values* as operands. Instead, the compiler must allocate and initialize storage for any *constant values*.