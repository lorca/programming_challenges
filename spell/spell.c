/**
 * A spelling corrector written in C which uses tries.
 *
 * To compile and run do: 
 *   gcc spell.c trie.c
 *   wget http://norvig.com/big.txt
 *   ./a.out speling < big.txt
 *
 * See http://norvig.com/spell-correct.html 
 *
 * Steve A <iradik@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "map.h"

/* Note: Biggest word in big.txt is 18 characters. */
#define WORD_LEN_MAX 1024

void fatal(char *error) {
    printf("Fatal error %s\n", error);
    exit(-1); 
}

void scopy(char *dest, const char* src, int len) {
   strncpy(dest, src, len);
   dest[len]='\0';
}

void find_max(char* word, void* arg1, void* arg2, void* arg3) {
    result_t* found;
    map_t* map = (map_t*)arg1;
    int* max = (int*) arg2;
    char*max_word = (char*)arg3;

    if (found = find_map(map, word)) {
       if (found->count > *max) {
           *max = found->count;
           scopy(max_word, word, strlen(word));
       }
       //printf("%s\n", word);
    }
}

/** Counts words from STDIN into the map. */ 
void train(map_t *map) {
    static char word[WORD_LEN_MAX];
    char c;
    int i = 0;
    while ((c = tolower(getchar())) != EOF) {
       if (i > WORD_LEN_MAX) goto err;
       if (c < 'a' || c > 'z') {
               word[i] = '\0';
               load_map(map,word);
               i = 0;
       } else word[i++] = c;
    }
    return;
    err: fatal("WORD_LEN_MAX exceeded!");
}

void calc_edits1(const char *word, map_t* edits, void load_f(map_t*,char*)) {
   int word_len, i;
   char c;
   word_len = strlen(word);
   
   char *temp = malloc(word_len+3 * sizeof(char));
   char split[2][WORD_LEN_MAX];

   for (i=0; i < word_len+1; ++i) {
       /** split */
       scopy(split[0], word, i);
       scopy(split[1], &word[i], word_len - i);
       /** delete */
       if (i < word_len) {
           scopy(temp, split[0], i);
           scopy(&temp[i], &split[1][1], word_len - i - 1);
           load_f(edits, temp);
       }
       /** inserts */
       if (i < word_len+1) {
           for (c='a'; c <= 'z'; ++c) {
              scopy(temp, split[0], i);
              temp[i] = c;
              scopy(&temp[i+1], split[1], word_len - i);
              load_f(edits, temp);
           }
       }
       /** replaces */
       if (i < word_len) {
           for (c='a'; c <= 'z'; ++c) {
               scopy(temp, split[0], i);
               temp[i] = c;
               scopy(&temp[i+1], &split[1][1], word_len - i - 1);
               load_f(edits, temp);
           } 
       }
       /** transpose */
       if (i < word_len-1) {
           scopy(temp, split[0], i);
           temp[i] = split[1][1]; 
           temp[i+1] = split[1][0]; 
           scopy(&temp[i+2], &split[1][2], word_len - i - 2);
           load_f(edits, temp);
       }
   }

   free(temp);
}

static map_t* s_known_words;

void known_load_map(map_t* map, char *word) {
    if (find_map(s_known_words, word)) {
        load_map(map, word); 
    }    
}

void calc_edits2(char* edit1_word, void* arg1, void* arg2, void* arg3) {
    map_t* edits2 = (map_t*)arg1;
    calc_edits1(edit1_word, edits2, known_load_map);
}

void correct(map_t* known_words, char *word) {
   map_t *edits, *edits2;

   if (find_map(known_words, word)) {
       printf("%s\n", word);
       return;
   } 

   edits = create_map();
   calc_edits1(word, edits, load_map);

   int max = 0;
   char max_word[WORD_LEN_MAX];
  
   traverse_map(edits, 0, "", find_max, known_words, &max, max_word);

   if (!max) {
       edits2 = create_map();
       traverse_map(edits, 0, "", calc_edits2, edits2, NULL, NULL);
       traverse_map(edits2, 0, "", find_max, known_words, &max, max_word);
       delete_map(edits2);
   }
   delete_map(edits);

   printf("%s %d\n", max_word, max);   
}

int main(int argc, char **argv) {
   map_t *known_words = create_map();
   train(known_words);
   s_known_words = known_words;

   char *word = argv[1];
   correct(known_words, word);

   delete_map(known_words);
}

