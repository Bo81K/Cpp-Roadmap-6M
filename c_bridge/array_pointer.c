#include <stdio.h>
#include <stddef.h>

void print_array(const int* arr, size_t size){
    for (size_t i = 0; i < size; ++i){
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int sum_array (const int* arr, size_t size){
    int sum = 0;
    for (size_t i = 0; i < size; ++i){
        sum += arr[i];
    }
    
    return sum;
}

int main(void){
    int arr[5] = {10, 20, 30, 40, 50};
    print_array(arr, 5);
    int *p = arr; // arr в выражении преобразуется в указатель на свой первый элемент

    printf ("arr[0] = %d\n", arr[0]);
    printf ("*p= %d\n", *p);
    printf ("*(p + 2) = %d\n", *(p + 2));
    printf ("p[3] = %d\n", p[3]);
    printf ("sum_array = %d\n", sum_array(arr, 5));

    return 0;
}