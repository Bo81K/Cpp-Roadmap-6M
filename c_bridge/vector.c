#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_INITIAL_CAPACITY 4

typedef struct  // что в данной структуре за что отвечает? 
{
    int *data;
    size_t size;
    size_t capacity;
}IntVector;     // Почему здесь, а не сверху?

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

int main(void){

    int value = 0;
    IntVector empty;

    assert(vector_init(&empty) == 0);

    assert(vector_pop_back(&empty, &value) == -1);
    assert(vector_get(&empty, 0, &value) == -1);
    assert(vector_set(&empty, 0, 123) == -1);

    vector_destroy(&empty);

    IntVector vec;

    assert(vector_init(&vec) == 0);
    assert(vector_push_back(&vec, 10) == 0);

    assert(vector_get(&vec, 1, &value) == -1);
    assert(vector_set(&vec, 1, 567) == -1);

    vector_destroy(&vec);

    IntVector bigVec;

    assert(vector_init(&bigVec) == 0);

    for(int i = 0 ; i < 1000; ++i){
        assert(vector_push_back(&bigVec, i) == 0);
    }

    assert(bigVec.size == 1000);
    assert(bigVec.capacity >= bigVec.size);

    assert(vector_get(&bigVec, 999, &value) == 0);
    assert(value == 999);

    vector_destroy(&bigVec);

    IntVector v;

    assert(vector_init(&v) == 0);

    for(int i = 0; i < 20; ++i){
        assert(vector_push_back(&v, i * 10) == 0);
    }
    
    assert(v.size == 20);
    assert(v.capacity >= v.size);


    assert(vector_get(&v, 0, &value) == 0);
    assert(value == 0);

    assert(vector_get(&v, 19, &value) == 0);
    assert(value ==190);

    assert(vector_set(&v, 0, 123) == 0);
    assert(vector_get(&v, 0, &value) == 0);
    assert(value == 123);

    assert(vector_pop_back(&v, &value) == 0);
    assert(value == 190);
    assert(v.size == 19);

    assert(vector_get(&v, 19, &value) == -1);

    vector_print(&v);

    vector_destroy(&v);

    printf("vector tests passed\n");

    return 0;
}