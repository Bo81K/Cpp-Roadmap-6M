#include "vector.h"

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