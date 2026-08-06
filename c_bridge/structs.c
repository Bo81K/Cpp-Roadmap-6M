#include <assert.h>
#include <stddef.h>
#include <stdio.h>

struct Point
{
    int x;
    int y;
};

int abs_int(int value){
    return value < 0 ? -value : value;
}

int point_manhattan(const struct Point *a, const struct Point *b){
    assert(a != NULL);
    assert(b != NULL);

    int dx = abs_int(a->x - b->x);
    int dy = abs_int(a->y - b->y);

    return dx + dy;
}

size_t nearest_to_origin(const struct Point *points, size_t count){
    assert(points !=NULL);
    assert(count > 0);

    struct Point origin = {0, 0};

    size_t best_index = 0;

    int best_distanse = point_manhattan(&points[0], &origin);

    for(size_t i = 1; i < count; ++i){
        int distance = point_manhattan(&points[i], &origin);

        if(distance < best_distanse){
            best_distanse = distance;
            best_index = i;
        }
    }

    return best_index;
}

int main(void){
    struct Point points[] = {
        {3, 4},
        {1, 1},
        {-2, 2},
        {0, 5}
    };
    
    size_t count = sizeof(points) / sizeof(points[0]);

    size_t nearest = nearest_to_origin(points, count);

    assert(nearest == 1);

    printf(
        "nearest index = %zu, point = (%d, %d)\n",
        nearest,
        points[nearest].x,
        points[nearest].y
    );

    printf("structs tests passed\n");

    return 0;
}