#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_INITIAL_CAPACITY 4

typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} IntVector;  

int vector_init(IntVector *v);
void vector_destroy(IntVector * v);
int vector_reserve(IntVector *v, size_t new_capacity);
int vector_push_back(IntVector *v, int value);
int vector_pop_back(IntVector *v, int * out);
int vector_get(IntVector* v, size_t index, int *out);
int vector_set(IntVector* v, size_t index, int value);
void vector_print(const IntVector* v);

#endif