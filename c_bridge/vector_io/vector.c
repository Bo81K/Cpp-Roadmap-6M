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

int vector_save(const IntVector *v, const char *filename){
    if(v == NULL || filename == NULL)
        return -1;

    FILE *f = fopen(filename, "wb");
    if(f == NULL)
        return -1;

    // Записываем size (записываем количество элементов)
    if(fwrite(&v->size, sizeof(size_t), 1, f) != 1){
        fclose(f);
        return -1;
    }

    // Записываем данные (записываем сами элементы)
    if(v->size > 0){
        if(fwrite(v->data, sizeof(int), v->size, f) != v->size){
            fclose(f);
            return -1;
        }
    }

    fclose(f);
    return 0;
}

int vector_load(IntVector *v, const char *filename){
    if(v == NULL || filename == NULL)
        return -1;

    FILE *f = fopen(filename, "rb");
    if(f == NULL)
        return -1;

    // Читаем size
    size_t size = 0;
    if(fread(&size, sizeof(size_t), 1, f) != 1){
        fclose(f);
        return -1;
    }

    vector_destroy(v);

    if(vector_init(v) !=0){
        fclose(f);
        return -1;
    }

    // Резервируем место
    if(size > 0){
        if(vector_reserve(v, size) !=0){
            fclose(f);
            return -1;
        }
        
        if(fread(v->data, sizeof(int), size, f) != size){
            fclose(f);
            vector_destroy(v);
            return -1;
        }
        
        v->size = size;
    }

    fclose(f);
    return 0;
}