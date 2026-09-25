#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

int sum_recursive(const int *arr, size_t count){
    if(count == 0)
        return 0;

    return arr[0] + sum_recursive(arr + 1, count - 1);
}

int max_recursive(const int *arr, size_t count){
    assert(arr != NULL);
    assert(count > 0);

    if(count == 1)
        return arr[0];

    int max_of_rest = max_recursive(arr + 1, count - 1);

    if(arr[0] > max_of_rest)
        return arr[0];

    return max_of_rest;
}

static size_t binary_search_recursive(const int *arr, size_t left, size_t right, int target){
    if(left >= right)
        return SIZE_MAX;

    size_t mid = left + (right - left) / 2;

    if(arr[mid] == target)
        return mid;

    if(arr[mid] < target)
        return binary_search_recursive(arr, mid + 1, right, target);

    return binary_search_recursive(arr, left, mid, target);
}

size_t binary_search(const int *arr, size_t count, int target){
    assert(arr != NULL || count == 0);

    return binary_search_recursive(arr, 0, count, target);
}

int main(void){
    int arr[] = {1, 3, 5, 7, 9, 11};
    size_t count = sizeof(arr) / sizeof(arr[0]);

    assert(sum_recursive(arr, count) == 36);
    assert(max_recursive(arr, count) == 11);

    assert(binary_search(arr, count, 1) == (size_t)0);
    assert(binary_search(arr, count, 11) == (size_t)5);
    assert(binary_search(arr, count, 5) == (size_t)2);
    assert(binary_search(arr, count, 4) == SIZE_MAX);
    assert(binary_search(arr, count, 0) == SIZE_MAX);
    assert(binary_search(arr, count, 12) == SIZE_MAX);

    assert(binary_search(NULL, 0, 1) == SIZE_MAX);

    printf("recursion tests passed\n");

    return 0;
}