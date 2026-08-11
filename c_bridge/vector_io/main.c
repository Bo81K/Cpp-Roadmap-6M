#include "vector.h"

int main(void){
    IntVector v1;

    assert(vector_init(&v1) == 0);

    for(int i = 0; i < 100; ++i){
        assert(vector_push_back(&v1, i * 10) == 0);
    }

    printf("Original vector:\n");
    vector_print(&v1);

    const char *filename = "test_vector.bin";

    // Сохраняем
    assert(vector_save(&v1, filename) == 0);

    IntVector v2;
    assert(vector_load(&v2, filename) == 0);
    printf("\nLoaded vector:\n");
    vector_print(&v2);

    assert(v2.size == v1.size);

    for(size_t i = 0; i< v1.size; ++i){
        int val1 = 0 , val2 = 0;
        assert(vector_get(&v1, i, &val1) == 0);
        assert(vector_get(&v2, i, &val2) == 0);
        assert(val1 == val2);
    }

    vector_destroy(&v1);
    vector_destroy(&v2);

    printf("\nvector save/loaded tests passed\n");

    return 0;
}