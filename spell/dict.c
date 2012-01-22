/**
 * A trie library written for spell.c.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dict.h"
#include "fnv_hash.h"


dict_result_t* lookup(dict_t *dict, const char *word) {
    dict_result_t* result;
    unsigned int probe, mod_hash_val;
    int hash_val = hash((char*)word);
    probe = 0;
    while (1) {
        mod_hash_val = (hash_val + probe) % DICT_SIZE;
        result = &(dict->table[mod_hash_val]);
        if (result->count > 0) {
            if (!strcmp(result->word, word)) {
               break; 
            } else {
              // printf("Hash collision: %s %s\n", word, result->word);
            }
        } else {
            break;
        } 
        ++probe; 
    }
    return result;
}

/**
 * Finds the trie node which complets a word. 
 * Returns null if word is not found.in the trie. 
 */
dict_result_t* find_map(dict_t *dict, const char *word) {
    dict_result_t* result = lookup(dict, word);
    if (result->count > 0) {
        return result; 
    }
    return NULL;
}

void print_map(dict_t *dict, int depth, char *word, void f(char*, void*, void*, void*), void* arg1, void* arg2, void* arg3) {
    int i;
    for (i=0; i < DICT_SIZE; ++i) {
        if (dict->table[i].count) {
            f(dict->table[i].word, arg1, arg2, arg3);
        }
    }
}

void delete_map(dict_t *dict) {
    free(dict);
}

dict_t* create_map(char c) {
    return malloc(sizeof(dict_t));
}

void load_map(dict_t *dict, char *word) {
    int word_len = strlen(word);
    dict_result_t *result = lookup(dict, word);
    if (result->count == 0) {
        strncpy(result->word, word, word_len);
    }
    ++result->count;
}

