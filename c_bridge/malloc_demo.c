#include <stdio.h>
#include <stdlib.h>

int main(void){
    size_t count = 5;

    int* arr = malloc(count * sizeof(int));

    if (arr == NULL){
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    for(size_t i = 0; i < count; ++i)
        arr[i] = (int)(i * 10);

    for(size_t i = 0; i < count; ++i)
        printf("arr[%zu] = %d\n", i, arr[i]);

    free(arr);

    return 0;
}