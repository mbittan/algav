#include "briandais.h"

briandais_t* new_briandais(char key, briandais_t *son, briandais_t *brother) {
  briandais_t *tree = malloc(sizeof(briandais_t));

  tree->key = key;
  tree->son = son;
  tree->brother = brother;
  tree->cpt = 1;

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
  //printf("%s : \t", word);
  if(tree == NULL) {
    //printf("*tree=null && ");
    if(*word == '\0') {
      //printf("*word=epsilon\n");
      return new_empty_briandais();
    }
    //printf("*word!=epsilon\n");
    return new_briandais(*word,
			 insert_briandais(NULL, word+1),
			 NULL);
  }
  if(*word == '\0') {
    if(tree->key != '\0') {
      //printf("*word=epsilon && tree->key!=epsilon\n");
      B = new_empty_briandais();
      B->brother = tree;
      return B;
    }
    //printf("*word=epsilon && tree->key=epsilon\n");
    return tree;
  }
  else if(*word < tree->key) {
    //printf("*word < tree->key : %c < %c\n", *word, tree->key);
    return new_briandais(*word, insert_briandais(NULL, word+1), tree);
  }
  else if(*word == tree->key) {
    //printf("*word == tree->key : %c = %c\n", *word, tree->key);
    tree->cpt++;
    tree->son = insert_briandais(tree->son, word+1);
    return tree;
  }
  else {
    //printf("*word > tree->key : %c > %c\n", *word, tree->key);
    tree->brother = insert_briandais(tree->brother, word);
    return tree;
  }
  if(is_empty_briandais(tree)) {
    //printf("tree is empty : %p\n", tree);
    tree->brother = new_briandais(*word, insert_briandais(NULL, word+1), NULL);
    return tree;
  }
  return tree;
}

int delete_briandais(briandais_t **tree, char* word) {
  int r;
  briandais_t *bros_bro, *sons_bro;

  //printf("%s : ", word);
  if(is_empty_briandais(*tree)) {
    //printf("tree is empty ");
    if(*word == '\0') {
      //printf("word is $\n");
      destroy_briandais(tree);
      *tree = NULL;
      return 1;
    }
    //printf("word is not empty (-1)\n");
    return -1;
  }
  if(*word == '\0') {
    //printf("tree not empty and word=$ (-1)\n");
    return -1;
  }

  if(*word == (*tree)->key) {
    //printf("*word = tree->key : %c = %c\n", *word, (*tree)->key);
    sons_bro = (*tree)->son->brother;
    //if(sons_bro != NULL)
      //printf("sons_bro->key = %c\n", sons_bro->key);
    if((r = delete_briandais(&((*tree)->son), word+1)) != -1) {
      (*tree)->cpt--;
      if(r == 1)
	(*tree)->son = sons_bro;
      // printf("deletion ok : %c->cpt = %d\n", (*tree)->key, (*tree)->cpt);
      if((*tree)->cpt == 0) {
	//printf("destroy from %s\n", word);
	destroy_briandais(tree);
	*tree = NULL;
	return 1;
      }
      return 0;
    }
  }
  else if(*word > (*tree)->key) {
    //printf("*word > tree->key : %c > %c\n", *word, (*tree)->key);
    if((*tree)->brother != NULL)
      bros_bro = (*tree)->brother->brother;
    r = delete_briandais(&((*tree)->brother), word);
    if(r == 1)
      (*tree)->brother = bros_bro;
    return r;
  }
  else {
    //printf("*word < tree->key : %c < %c\n", *word, (*tree)->key);
    return -1;
  }
  return -1;
}

int destroy_briandais(briandais_t **tree) {
  if(*tree != NULL) {
    if((*tree)->son != NULL)
      destroy_briandais(&((*tree)->son));
    free(*tree);
  }
  *tree = NULL;
  return 0;
}

void print_briandais_rec(briandais_t *tree, int height) {
  int i;
  if(tree == NULL)
    return;
  if(tree->key == '\0')
    printf("$");
  else
    printf("%c", tree->key);
  print_briandais_rec(tree->son, height+1);
  if(tree->brother != NULL) {
    printf("\n");
    for(i=0; i<height; i++)
    printf(" ");
  }
  print_briandais_rec(tree->brother, height);
}

void print_briandais(briandais_t *tree) {
  printf("Printing Briandais tree :\n");
  print_briandais_rec(tree, 0);
  printf("\n");
}

int search_briandais(briandais_t *tree, char *word) {
  if(tree->key == '\0') {
    if(*word == '\0')
      return 1;
    return 0;
  }
  if(*word == '\0')
    return 0;
  if(tree->key == *word)
    return search_briandais(tree->son, word+1);
  if(tree->key < *word)
    return search_briandais(tree->brother, word);
  return 0;
}

int count_briandais(briandais_t *tree) {
  if(tree == NULL)
    return 0;
  if(tree->key == '\0')
    return 1 + count_briandais(tree->brother);
  return count_briandais(tree->son) + count_briandais(tree->brother);
}



int main() {
  briandais_t *tree=NULL;

  int fd = ouvrir_fichier(DATA_DIR"exemple_de_base");
  char mot[50];
  
  while(mot_suivant(fd, mot) != 0) {
    tree = insert_briandais(tree, mot);
  }
  
  print_briandais(tree);

  printf("\n\nTesting search :\n");
  printf("Search redevables : %d\n", search_briandais(tree, "redevables"));
  printf("Search redevable : %d\n", search_briandais(tree, "redevable"));
  printf("Search saperlipopette : %d\n", search_briandais(tree, "saperlipopette"));
  printf("Search puisque : %d\n", search_briandais(tree, "puisque"));
  printf("Search un : %d\n", search_briandais(tree, "un"));

  printf("\n\nTesting count :\n");
  printf("Count (should be 34) : %d\n", count_briandais(tree));
  
  destroy_briandais(&tree);

  return EXIT_SUCCESS;
}
