#include <stdio.h>

int main() {
    
    int arr[5] = {1, 2, 3, 4, 5};

    printf("arr: %p\n", arr);                   // => 0x16bd16f50
    printf("arr+1: %p\n", arr+1);               // => 0x16bd16f54
    printf("arr+5: %p\n", arr+5);               // => 0x16bd16f64
    printf("&arr[5]-arr: %ld\n", &arr[4]-arr);  // => 4
    printf("&arr[5]-arr: %p\n", &arr[4]);       // => 0x16d976f60
    printf("&arr[5]-arr: %d\n", arr[4]);        // => 5
    return 0;
}
