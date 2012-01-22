/**
 * A trie library written for spell.c.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

#define CHAR_SIZE 256

/**
 * Finds the trie node which complets a word. 
 * Returns null if word is not found.in the trie. 
 */
trie_t* find_map(trie_t *trie, const char *word) {
    char c;
    trie_t *child;
    while (c = *(word++)) {
        for (child=trie->children; child && child->c != c; child=child->next);
        if (!child) return 0;
        trie = child;
    }
    if (trie->count) return trie;
    return NULL;
}

void traverse_map(trie_t *trie, int depth, char *word, void f(char*, void*, void*, void*), void* arg1, void* arg2, void* arg3) {
    int i, c;
    trie_t *child, **trie_buf;
    char *temp = word;
    if (trie) {
        word = malloc((depth + 1) * sizeof(char));
        trie_buf = calloc(CHAR_SIZE, sizeof(trie_t*));

        strcpy(word, temp);
        word[depth + 1] = '\0';

        word[depth] = trie->c;
        if (trie->count) {
            f(&word[1], arg1, arg2, arg3);
        }
        for (c=0; c < CHAR_SIZE; c++) {
            trie_buf[c] = NULL;
        }
        for (child=trie->children; child; child=child->next) {
            trie_buf[child->c] = child;
        }
        /** sort the tries. unnecessary but fun. */
        for (c=0; c < CHAR_SIZE; c++) {
            if(trie_buf[c]) {
                child = trie_buf[c];
                traverse_map(child, depth+1, word, f, arg1, arg2, arg3); 
            }
        }
        free(trie_buf);
        free(word);
    }
}

void delete_map(trie_t *trie) {
    trie_t* child;
    if (trie) {
        for (child=trie->children; child; child=child->next) {
            delete_map(child);
        }
        free(trie);
    }
}

trie_t* init_map(char c) {
    trie_t* trie = malloc(sizeof(trie_t));
    trie->c = c;
    trie->count = 0;
    return trie;
}

trie_t* create_map() {
    return init_map(' ');
}

void load_map(trie_t *trie, char *word) {
    char c;
    trie_t *child;
    while (c = *(word++)) {
        for (child=trie->children; child && child->c != c; child=child->next);
        if (!child) {
            child = init_map(c);
            child->next = trie->children;  
            trie->children = child;
        }
        trie = child;
    }
    ++trie->count;
}

