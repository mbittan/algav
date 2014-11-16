#include "briandais.h"

briandais_t* new_briandais(char key, briandais_t *son, briandais_t *brother) {
  briandais_t *tree = malloc(sizeof(briandais_t));

  tree->key = key;
  tree->son = son;
  tree->brother = brother;

  return tree;
}

briandais_t* new_empty_briandais() {
  return new_briandais('\0', NULL, NULL);
}

int is_empty_briandais(briandais_t *tree) {
  return (tree->key == '\0') && (tree->son == NULL) && (tree->brother == NULL);
}

briandais_t* insert_briandais(briandais_t *tree, char* word) {
  briandais_t *B;
  printf("%s : \t", word);
  if(tree == NULL) {
    printf("*tree=null && ");
    if(*word == '\0') {
      printf("*word=epsilon\n");
      return new_empty_briandais();
    }
    printf("*word!=epsilon\n");
    return new_briandais(*word,
			 insert_briandais(NULL, word+1),
			 NULL);
  }
  if(is_empty_briandais(tree)) {
    printf("tree is empty : %p\n", tree);
    tree->brother = new_briandais(*word, insert_briandais(NULL, word+1), NULL);
    return tree;
  }
  if(*word == '\0') {
    if(tree->key != '\0') {
      printf("*word=epsilon && tree->key!=epsilon\n");
      B = new_empty_briandais();
      B->brother = tree;
      return B;
    }
    printf("*word=epsilon && tree->key=epsilon\n");
    return tree;
  }
  else if(*word < tree->key) {
    printf("*word < tree->key : %c < %c\n", *word, tree->key);
    return new_briandais(*word, insert_briandais(NULL, word+1), tree);
  }
  else if(*word == tree->key) {
    printf("*word == tree->key : %c = %c\n", *word, tree->key);
    tree->son = insert_briandais(tree->son, word+1);
    return tree;
  }
  printf("*word > tree->key : %c > %c\n", *word, tree->key);
  tree->brother = insert_briandais(tree->brother, word);
  return tree;
}

/* int delete_briandais(briandais_t *tree, char* word) { */
/*   if(is_empty_briandais(tree)) { */
/*     if(*word == '\0') { */
      
/*       return 1; */
/*     } */
/*     return -1; */
/*   } */
  
/* } */

void print_briandais_rec(briandais_t *tree, int height) {
  int i;
  if(tree == NULL)
    return;
  for(i=0; i<height; i++)
    printf(" ");
  if(tree->key == '\0')
    printf("$\n");
  else
    printf("%c\n", tree->key);
  print_briandais_rec(tree->son, height+1);
  print_briandais_rec(tree->brother, height);
}

void print_briandais(briandais_t *tree) {
  printf("Printing Briandais tree :\n");
  print_briandais_rec(tree, 0);
}

int main() {
  briandais_t *tree=NULL;
  char *m1, *m2, *m3;

  //tree = new_empty_briandais();
  m1 = malloc(6*sizeof(char));
  m2 = malloc(10*sizeof(char));
  m3 = malloc(6*sizeof(char));

  sprintf(m1, "salam");
  sprintf(m2, "bonjour");
  sprintf(m3, "salim");

  print_briandais(tree);

  tree = insert_briandais(tree, m1);
  print_briandais(tree);
  tree = insert_briandais(tree, m2);
  print_briandais(tree);
  tree = insert_briandais(tree, m3);
  print_briandais(tree);

  free(m1);
  free(m2);
  free(m3);
  //  destroy_briandais(tree);

  return EXIT_SUCCESS;
}
