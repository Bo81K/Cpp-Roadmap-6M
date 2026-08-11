#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//в этой функции мы проходим от самого левого элемента массива до опорного и при этом меняем элементы местами, если они меньше опорного
size_t partition(int *arr, size_t left, size_t right){
    int privot = arr[right];
    size_t i = left;

    for(size_t j = left; j < right; ++j){
        if(arr[j] <= privot){
            swap(&arr[i], &arr[j]);
            ++i;
        }
    }

    swap(&arr[i],&arr[right]);

    return i;
}

void quicksort_impl(int *arr, size_t left, size_t right){
    if(left >= right)
        return;

    size_t privot_idex = partition(arr, left, right);

    if(privot_idex > 0)
        quicksort_impl(arr, left, privot_idex - 1);

    quicksort_impl(arr, privot_idex + 1, right);
}

void quicksort(int *arr, size_t count){
    if (count == 0)
        return;

    quicksort_impl(arr, 0, count - 1);
}

void print_array(int *arr, size_t count){
    for(size_t i = 0; i < count; ++i){
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main(void){
    int arr1[] = {5, 3, 8, 4, 2, 7, 1, 6};

    size_t count1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Before: ");
    print_array(arr1, count1);

    quicksort(arr1, count1);

    printf("After: ");
    print_array(arr1, count1);

    for(size_t i = 1; i < count1; ++i){
        assert(arr1[i-1] <= arr1[i]);
    }

    int arr2[] = {1};
    quicksort(arr2, 1);

    assert(arr2[0] == 1);

    int arr3[] = {2, 1};
    quicksort(arr3, 2);
    assert(arr3[0] == 1);
    assert(arr3[1] == 2);

    // Проверка с пустым массивом (указатель может быть NULL, т.к. длина 0)
    quicksort(NULL, 0);

    printf("quicksort tests passed\n");

    return 0;
}