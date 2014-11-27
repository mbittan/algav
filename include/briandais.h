#ifndef BRIANDAIS_H_
#define BRIANDAIS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gestion_fichier.h"

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
int search_briandais(briandais_t *tree, char *word);

/* Count the number of words in tree */
int count_briandais(briandais_t *tree);

/* Count the number of null pointers in tree */
int count_null_briandais(briandais_t *tree);

/* List words in Briandais tree */
void list_briandais(briandais_t *tree, char **list);

/* Returns the height of the Briandais trie tree */
int height_briandais(briandais_t *tree);

/* Checks how many words in tree word is the prefix */
int prefix_briandais(briandais_t *tree, char *word);

/* Merge two Briandais trees */
briandais_t* merge_briandais(briandais_t *A, briandais_t *B);

/* Export to LaTeX */
void export_to_latex(briandais_t *tree, char* filename);

#endif
