#include <stdio.h>

int main(void)
{
    int x = 0;
    int *n = &x;
    *n = 1;
    printf("x = %d\n", x);
    printf("n = %d\n", *n);

    int a = 5;
    int b = 10;

    printf("a = %d\n", a);
    printf("b = %d\n", b);

    int *c = &a;
    int *d = &b;

    *c = 10;
    *d = 5;


    printf("a = %d\n", a);
    printf("b = %d\n", b);
    
    int arr[5] = {10, 20, 30, 40, 50};

    int *arr_ptr = arr;
    printf("\nОбход массива через указатель\n");
    for (int i = 0; i < 5; ++i)
    {
        printf("arr[%d] = %d\n", i, *(arr_ptr + i));
    }
    
    return 0;
}