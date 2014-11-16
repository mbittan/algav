#ifndef BRIANDAIS_H_
#define BRIANDAIS_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct _briandais_ {
  char key;
  struct _briandais_ *son;
  struct _briandais_ *brother;
  int cpt;
} briandais_t;

/* Create a new instance of a Briandais trie */
briandais_t* new_briandais(char key, briandais_t *son, briandais_t *brother);

/* Create an empty Briandais trie with a '\0' key */
briandais_t* new_empty_briandais();

/* Checks whether tree is an empty Briandais trie or not */
int is_empty_briandais(briandais_t *tree);

/* Insert word in tree */
/* word must contain a trailing '\0' */
/* if tree=NULL, a new tree is created */
briandais_t* insert_briandais(briandais_t *tree, char* word);

/* Remove word from tree */
/* word must contain a trailing '\0' */
/* Returns -1 if word isn't in tree, 0 if suppression goes well */
int delete_briandais(briandais_t **tree, char* word);

/* Destroy the Briandais trie tree */
int destroy_briandais(briandais_t **tree);

/* Print Briandais trie */
void print_briandais(briandais_t *tree);

/* Checks whether word is in tree */
int is_in_briandais(briandais_t *tree, char *word);

#endif
