#include "briandais.h"

#define MAX(a,b) ((a) < (b) ? (b) : (a))

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
  if(tree == NULL) {
    return;
  }
  if(tree->key == '\0')
    printf("$");
  else
    printf("%c", tree->key);
  print_briandais_rec(tree->son, height+1);
  if(tree->brother != NULL) {
    printf("\n");
    for(i=0; i<height-1; i++)
      printf(" ");
    if(height>0)
      printf("|");
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

int count_null_briandais(briandais_t *tree) {
  if(tree == NULL)
    return 1;
  return count_null_briandais(tree->son) + count_null_briandais(tree->brother);
}

void list_briandais(briandais_t *tree, char **list) {
  
}

int height_briandais(briandais_t *tree) {
  int bro, son;
  if(tree == NULL)
    return 0;
  son = height_briandais(tree->son) + 1;
  bro = height_briandais(tree->brother);
  return MAX(son, bro);
}

int prefix_briandais(briandais_t *tree, char *word) {
  int n=0;
  if(tree == NULL)
    return 0;
  if(*word == '\0')
    return -1;
  if(tree->key == *word)
    n = prefix_briandais(tree->son, word+1);
  if(tree->key < *word)
    n = prefix_briandais(tree->brother, word);
  if(n == -1)
    return tree->cpt;
  if(n > 0)
    return n;
  return 0;
}

briandais_t* merge_briandais(briandais_t *A, briandais_t *B) {
  if(B == NULL)
    return A;
  if(A == NULL)
    return B;

  if(A->key > B->key) {
    B->brother = A;
    return B;
  }

  if(A->key == B->key) {
    A->brother = merge_briandais(A->brother, B->brother);
    A->son = merge_briandais(A->son, B->son);
  }

  if(A->key < B->key) {
    A->brother = merge_briandais(A->brother, B);
  }

  return A;
}

int export_to_latex_rec(briandais_t *tree, FILE* f, int height) {
  static int offset = 0;
  static int node_id = 1;
  int id, relative_id;

  if(tree != NULL) {
    id = node_id;
    fprintf(f, "\\node at (%dpt,-%dpt) (%d) ",\
	    offset*5, height*5, node_id++);
    if(tree->key == '\0')
      fprintf(f, "{$\\varepsilon$};\n");
    else
      fprintf(f, "{%c};\n", tree->key);
    relative_id = export_to_latex_rec(tree->son, f, height+1);
    if(relative_id) {
      fprintf(f, "\\draw (%d) -- (%d);\n", id, relative_id);
    }
    if(tree->brother != NULL)
      offset++;
    relative_id = export_to_latex_rec(tree->brother, f, height);
    if(relative_id) {
      fprintf(f, "\\draw (%d) -- (%d);\n", id, relative_id);
    }
    return id;
  }
  return 0;
}

void export_to_latex(briandais_t *tree, char* filename) {
  FILE *f;

  if((f = fopen(filename,"w")) == NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  /* Header of LaTeX file */
  fprintf(f,"\\documentclass[fontsize=1pt]{scrartcl}\n\
\\usepackage{tikz}\n\
\\usepackage[graphics, active, tightpage]{preview}\n\
\\PreviewEnvironment{tikzpicture}\n\
\\begin{document}\n\
\\begin{tikzpicture}[->]\n");

  /* Body */
  export_to_latex_rec(tree, f, 0);

  /* End of file */
  fprintf(f,"\\end{tikzpicture}\n\
\\end{document}\n");

  fclose(f);
}

int main() {
  briandais_t *tree=NULL;
  briandais_t *tree2=NULL;
  briandais_t *tree_hamlet=NULL;

  int fd = ouvrir_fichier(DATA_DIR"exemple_de_base");
  int fdh = ouvrir_fichier(SHAKESPEARE_DIR"hamlet.txt");
  char mot[50];
  
  while(mot_suivant(fd, mot) != 0) {
    tree = insert_briandais(tree, mot);
  }
  tree2 = insert_briandais(tree2, "saperlipopette");
  
  print_briandais(tree);

  printf("\nMerge :\n");
  tree = merge_briandais(tree, tree2);
  print_briandais(tree);

  printf("\n\nTesting search :\n");
  printf("Search redevables : %d\n", search_briandais(tree, "redevables"));
  printf("Search redevable : %d\n", search_briandais(tree, "redevable"));
  printf("Search saperlipopette : %d\n", search_briandais(tree, "saperlipopette"));
  printf("Search puisque : %d\n", search_briandais(tree, "puisque"));
  printf("Search un : %d\n", search_briandais(tree, "un"));

  printf("\nTesting count :\n");
  printf("Count (should be 34) : %d\n", count_briandais(tree));

  printf("\nTesting NULL pointers count :\n");
  printf("Count : %d\n", count_null_briandais(tree));

  printf("\nTesting height of tree (should be 15) :\n");
  printf("Height : %d\n", height_briandais(tree));

  printf("\nTesting prefix in Briandais :\n");
  printf("dactylo (should be 2) : %d\n", prefix_briandais(tree, "dactylo"));
  printf("c (should be 5) : %d\n", prefix_briandais(tree, "c"));
  printf("sa (should be 0) : %d\n", prefix_briandais(tree, "sa"));

  printf("\nCreating Hamlet tree...\n");
  while(mot_suivant(fdh, mot) != 0) {
    tree_hamlet = insert_briandais(tree_hamlet, mot);
  }
  printf("\nExporting Hamlet tree...\n");
  export_to_latex(tree_hamlet, "hamlet.tex");
  print_briandais(tree_hamlet);
  
  destroy_briandais(&tree);
  destroy_briandais(&tree2);
  destroy_briandais(&tree_hamlet);

  return EXIT_SUCCESS;
}
