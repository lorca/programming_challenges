/**
 * A map library written for spell.c.
 */

struct result_t {
    int count;
};

struct map_t {
    int count;
};

typedef struct map_t map_t;
typedef struct result_t result_t;

/**
 * Finds the map node which complets a word. 
 * Returns null if word is not found.in the map. 
 */
result_t* find_map(map_t *map, const char *word);

void print_map(map_t *map, int depth, char *word, 
   void f(char*, void*, void*, void*),
          void* arg1, void* arg2, void* arg3);


void delete_map(map_t *map);

map_t* create_map();

void load_map(map_t *map, char *word);
