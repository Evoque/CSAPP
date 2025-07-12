#include <stdio.h>

struct rect {
    long llx;
    long lly;
    long arr[2];
};

long area(struct rect r) {
    return r.arr[0] * r.arr[1];
}

long area2(struct rect *r) {
    return r->arr[0] * r->arr[1];
}

int main() {
    struct rect r;
    r.llx = 2;
    r.lly = 3;
    r.arr[0] = 4;
    r.arr[1] = 5;

    printf("r.llx: %ld\n", area(r));
    return 0;
}






