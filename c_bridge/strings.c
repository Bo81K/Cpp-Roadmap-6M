#include <assert.h>
#include <stddef.h>
#include <stdio.h>

size_t my_strlen(const char *s){
    assert(s != NULL);
    size_t len = 0;

    while (s[len] != '\0')
    {
        ++len;
    }
    
    return len;
}

int my_strcpy(char *dst, size_t dst_size, const char *src){
    assert(dst != NULL);
    assert(src != NULL);

    if(dst_size == 0)
        return -1;

    size_t i = 0;

    while (i + 1 < dst_size && src[i] != '\0')
    {
        dst[i] = src[i];
        ++i;
    }

    dst[i] = '\0';

    if (src[i] == '\0')
        return 0;

    return -1;
}

int my_strcmp(const char *a, const char *b){
    assert(a != NULL);
    assert(b != NULL);

    while (*a && *b && *a == *b)
    {
        ++a;
        ++b;
    }
    
    return (unsigned char) *a - (unsigned char) *b; 
}

int main(void){
    assert(my_strlen("") == 0);
    assert(my_strlen("abc") == 3);
    assert(my_strlen("hello") == 5);

    char buffer[10];

    assert(my_strcpy(buffer, sizeof(buffer), "hello") == 0);
    assert(my_strcmp(buffer, "hello") == 0);

    char small[4];
    assert(my_strcpy(small, sizeof(small), "hello") != 0);
    assert(small[3] == '\0');

    assert(my_strcmp("abc", "abc") == 0);
    assert(my_strcmp("abc", "abd") < 0);
    assert(my_strcmp("abd", "abc") > 0);
    assert(my_strcmp("", "") == 0);
    assert(my_strcmp("a", "") > 0);
    assert(my_strcmp("", "a") < 0);
    
    printf("strings tests passed\n");

    return 0;

}