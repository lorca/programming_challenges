/**
 * A trie library written for spell.c.
 */

#define DICT_SIZE 50000

struct dict_result_t {
    int count;
    char word[20];
};
typedef struct dict_result_t dict_result_t;

struct dict_t {
    int count;
    dict_result_t table[DICT_SIZE];
};

typedef struct dict_t dict_t;

/**
 * Finds the trie node which complets a word. 
 * Returns null if word is not found.in the trie. 
 */
dict_result_t* find_map(dict_t *dict, const char *word);

void print_map(dict_t *dict, int depth, char *word, void f(char*, void*, void*, void*), void* arg1, void* arg2, void* arg3);

void delete_map(dict_t *dict);

dict_t* create_map(char c);

void load_map(dict_t *dict, char *word);

