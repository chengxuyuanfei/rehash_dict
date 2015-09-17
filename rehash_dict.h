#ifndef REHASH_DICT_H
#define REHASH_DICT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include "murmurhash.h"

#define DICT_HT_INIT_SIZE 4
#define MMHASH_SEED 1024
#define INTTYPE 0
#define DECIMALTYPE 1
#define STRINGTYPE 2
#define OBJECTTYPE 3


typedef struct dictEntry{
    char *key;
    int value_type;
    union {
	char *string_value;
	long num_value;
	double decimal_value;
	void *object_value;
    }value;
    struct dictEntry *next;
}dictEntry;

typedef struct dictType{
    unsigned int (*murmur_hash)(void *key);
    void *(*key_copy)(void *private_data, void *key);
    void *(*value_copy)(void *private_data, void *obj);  //obj ???
    int (*key_compare)(void *private_data, void *key1, void *key2);
    void (*key_destory)(void *private_data, void *key);
    void (*value_destory)(void *private_data, void *obj);
}dictType;

typedef struct dictHT{
    dictEntry **table;
    unsigned long size;
    unsigned long size_mask;
    unsigned long used;
}dictHT;

typedef struct dict {
    dictHT hash_table[2];
    int rehash_index;
    int iterators;
}dict;

typedef struct dictIterator{
    dict *d;
    int table, index, safe;
    dictEntry *entry, *next_entry;
}dictIterator;

dict *create_dic(void);
bool add_dict(dict *d, char *key, int type, ...);
bool replace_dict_value(dict *d, char *key, int type, ...);
bool fetch_dict_value(dict *d, char *key, int type, ...);
bool delete_dict_key(dict *d, char *key, int type);
bool release_dict(dict *d);
bool single_rehash_dict(dict *d);
bool exist_key(dict *d, char *key);




















#endif // REHASH_DICT_H








