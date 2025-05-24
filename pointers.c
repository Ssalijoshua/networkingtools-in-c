#include <stdio.h>
#include <stdlib.h>


int main(void) {
    
    int x = 5;
    int *y = &x;  // Pointer to x
    int **z = &y; // Pointer to pointer to x

    printf("Value of x: %d\n", **z);



}