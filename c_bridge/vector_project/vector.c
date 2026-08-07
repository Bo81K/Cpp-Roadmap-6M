#include "vector.h"

int vector_init(IntVector *v){
    assert(v != NULL);
    v->size = 0;
    v->capacity = VECTOR_INITIAL_CAPACITY;
    v->data = malloc(sizeof(int) * v->capacity);

    if (v->data == NULL){
        v->capacity = 0;
        return -1;  //почему -1???
    }

    return 0;
}

void vector_destroy(IntVector * v){
    if(v == NULL)
        return;

    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

int vector_reserve(IntVector *v, size_t new_capacity){
    assert(v != NULL);

    if(new_capacity <= v->capacity)
        return 0;

    int *new_data = realloc(v->data, sizeof(int) * new_capacity);

    if(new_data == NULL)
        return -1;

    v->data = new_data;
    v->capacity = new_capacity;

    return 0;
}

int vector_push_back(IntVector *v, int value){
    assert(v != NULL);

    if(v->size == v->capacity){
        size_t new_capacity = (v->capacity == 0) ? VECTOR_INITIAL_CAPACITY : v->capacity * 2;

        if(vector_reserve(v, new_capacity) != 0)
            return -1;
    }

    v->data[v->size] = value;
    ++v->size;

    return 0;    
}

int vector_pop_back(IntVector *v, int * out){
    assert(v != NULL);

    if(v->size == 0)
        return -1;

    --v->size;

    if (out != NULL)
    {
        *out = v->data[v->size];
    }

    return 0;    
}

int vector_get(IntVector* v, size_t index, int *out){
    assert(v != NULL);

    if(index >= v->size)
        return -1;

    if(out != NULL)
        *out = v->data[index];

    return 0;
}

int vector_set(IntVector* v, size_t index, int value){
    assert(v != NULL);

    if(index >= v->size)
        return -1;

    v->data[index] = value;

    return 0;
}

void vector_print(const IntVector* v){
    assert(v != NULL);

    printf("[");

    for(size_t i = 0; i < v->size; ++i){
        printf("%d", v->data[i]);

        if (i + 1 < v->size)
            printf(", ");
    } 

    printf("]\n");
}