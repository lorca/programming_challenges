/**
 * A trie library written for spell.c.
 */

struct trie_t {
    int count;
    char c;
    struct trie_t* children;
    struct trie_t* next;
};

typedef struct trie_t trie_t;

/**
 * Finds the trie node which complets a word. 
 * Returns null if word is not found.in the trie. 
 */
trie_t* find_map(trie_t *trie, const char *word);

void traverse_map(trie_t *trie, int depth, char *word, 
   void f(char*, void*, void*, void*),
          void* arg1, void* arg2, void* arg3);


void delete_map(trie_t *trie);

trie_t* create_map();

void load_map(trie_t *trie, char *word);
