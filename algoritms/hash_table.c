#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 16

typedef struct HashEntry
{
    char *key;
    int value;
    struct HashEntry *next; //следующая ячейка ключ-значение в контексте разрешения коллизий методом цепочек
}HashEntry;

typedef struct
{
    HashEntry *buckets[HASH_TABLE_SIZE];
}HashTable;

size_t hash_function(const char *key){
    size_t hash = 0;

    while (*key)
    {
        hash = hash * 31 + (unsigned char)*key;
        ++key;
    }
    
    return hash % HASH_TABLE_SIZE;
}

int hash_table_init(HashTable *table){
    for(size_t i = 0; i < HASH_TABLE_SIZE; ++i){
        table->buckets[i] = NULL;
    }

    return 0;
}

void hash_table_destroy(HashTable *table){
    for(size_t i = 0; i < HASH_TABLE_SIZE; ++i){
        HashEntry * entry = table->buckets[i];

        while (entry != NULL)
        {
            HashEntry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
        
        table->buckets[i] = NULL;
    }
}

int hash_table_insert(HashTable *table, const char * key, int value){
    size_t index = hash_function(key);                // 1. Вычисляем индекс
    HashEntry *entry = table->buckets[index];         // 2. Берём голову списка для этого индекса

    while (entry != NULL) {                           // 3. Идём по цепочке
        if (strcmp(entry->key, key) == 0) {           // 4. Если нашли ключ
            entry->value = value;                     //    обновляем значение
            return 0;                                 //    и выходим
        }
        entry = entry->next;                          // 5. Иначе переходим к следующему узлу
    }

    // Если дошли сюда — ключ не найден, создаём новый узел
    HashEntry *new_entry = malloc(sizeof(HashEntry)); // 6. Выделяем память под структуру
    if (new_entry == NULL) return -1;                 //    проверка ошибки

    new_entry->key = malloc(strlen(key) + 1);         // 7. Выделяем память под копию строки-ключа
    if (new_entry->key == NULL) {                     //    если не удалось
        free(new_entry);                              //    освобождаем структуру
        return -1;
    }

    strcpy(new_entry->key, key);                      // 8. Копируем строку
    new_entry->value = value;                         // 9. Сохраняем значение
    new_entry->next = table->buckets[index];          // 10. Новый узел указывает на старую голову
    table->buckets[index] = new_entry;                // 11. Теперь новый узел — голова списка

    return 0;
}

int hash_table_get(HashTable *table, const char *key, int *out){
    size_t index = hash_function(key);

    HashEntry *entry = table->buckets[index];

    while (entry != NULL)
    {
        if(strcmp(entry->key, key) == 0){
            if(out !=NULL)
                *out = entry->value;
            return 0;
        }
        entry = entry->next;
    }

    return -1;
}

int main(void){
    HashTable table;

    assert(hash_table_init(&table) == 0);
    assert(hash_table_insert(&table, "apple", 5) == 0);
    assert(hash_table_insert(&table, "banana", 10) == 0);
    assert(hash_table_insert(&table, "cherry", 15) == 0);

    int value = 0;

    assert(hash_table_get(&table, "apple", &value) == 0);
    assert(value == 5);

    assert(hash_table_get(&table, "banana", &value) == 0);
    assert(value == 10);
    
    assert(hash_table_get(&table, "cherry", &value) == 0);
    assert(value == 15);

    assert(hash_table_get(&table, "no_exist", &value) == -1);

    assert(hash_table_insert(&table, "apple", 100) == 0);
    assert(hash_table_get(&table, "apple", &value) == 0);
    assert(value == 100);

    hash_table_destroy(&table);

    printf("hash_table tests passed\n");

    return 0;
}