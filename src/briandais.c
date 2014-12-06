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
  if(tree == NULL) {
    if(*word == '\0') {
      return new_empty_briandais();
    }
    return new_briandais(*word,
			 insert_briandais(NULL, word+1),
			 NULL);
  }
  if(*word == '\0') {
    if(tree->key != '\0') {
      B = new_empty_briandais();
      B->brother = tree;
      return B;
    }
    return tree;
  }
  else if(*word < tree->key) {
    return new_briandais(*word, insert_briandais(NULL, word+1), tree);
  }
  else if(*word == tree->key) {
    tree->cpt++;
    tree->son = insert_briandais(tree->son, word+1);
    return tree;
  }
  else {
    tree->brother = insert_briandais(tree->brother, word);
    return tree;
  }
  /* if(is_empty_briandais(tree)) { */
  /*   tree->brother = new_briandais(*word, insert_briandais(NULL, word+1), NULL); */
  /*   return tree; */
  /* } */
  return tree;
}

int delete_briandais(briandais_t **tree, char* word) {
  int r;
  briandais_t *bros_bro, *sons_bro, *son, *bro;

  if(*tree == NULL)
    return -1;
  
  if((*tree)->key == '\0' && *word == '\0') {
      return 1;   // tell father to take my brother as a son and destroy me
  }

  if(*word == (*tree)->key) {
    if((r = delete_briandais(&((*tree)->son), word+1)) != -1) {
      (*tree)->cpt--;
      if(r == 1) {
	son = (*tree)->son;
	sons_bro = son->brother;
	(*tree)->son = sons_bro;
	free(son);
	if((*tree)->cpt == 0) {
	  return 1;  // tell father/bro to destroy me (and take my bro as son)
	}
      }
      return 0;
    }
  }
  else if(*word > (*tree)->key) {
    if((r = delete_briandais(&((*tree)->brother), word)) != -1) {
      if(r == 1) {
	bro = (*tree)->brother;
	bros_bro = bro->brother;
	(*tree)->brother = bros_bro;
	free(bro);
      }
      return 0;
    }
  }
  
  return -1;
}

int destroy_briandais(briandais_t **tree) {
  if(*tree != NULL) {
    if((*tree)->son != NULL)
      destroy_briandais(&((*tree)->son));
    if((*tree)->brother != NULL)
      destroy_briandais(&((*tree)->brother));
    free(*tree);
    *tree = NULL;
  }
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
  if(tree == NULL)
    return 0;
  if(tree->key == '\0') {
    if(*word == '\0')
      return 1;
    return search_briandais(tree->brother, word);
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

void list_briandais_rec(briandais_t *tree, char *buffer, int size, Liste *list) {
  char *word;
  if(tree != NULL) {
    *buffer = tree->key;
    if(*buffer == '\0') {
      word = malloc((size+1)*sizeof(char));
      word = memcpy(word, buffer-size, size+1);
      inserer_fin(list, (void*)word);
    }
    else {
      list_briandais_rec(tree->son, buffer+1, size+1, list);
    }
    list_briandais_rec(tree->brother, buffer, size, list);
  }
}

Liste* list_briandais(briandais_t *tree) {
  Liste *list;
  char buffer[100];

  list = creer_liste();
  list_briandais_rec(tree, buffer, 0, list);

  return list;
}

int height_briandais(briandais_t *tree) {
  int bro, son;
  if(tree == NULL)
    return 0;
  son = height_briandais(tree->son) + 1;
  bro = height_briandais(tree->brother);
  return MAX(son, bro);
}

double average_depth(briandais_t *tree) {
  double average = 0;
  int nb_bros = 0;
  briandais_t *t = tree;
  int h;

  while(t!=NULL) {
    h = height_briandais(t->son);
    average += h+1;
    nb_bros++;
    t = t->brother;
  }

  return average/(double)nb_bros;
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

briandais_t* merge_briandais_rec(briandais_t *A, briandais_t *B) {
  if(B == NULL)
    return A;
  if(A == NULL)
    return B;

  if(A->key > B->key) {
    B->brother = merge_briandais_rec(A, B->brother);
    return B;
  }
  else if(A->key == B->key) {
    A->brother = merge_briandais_rec(A->brother, B->brother);
    A->son = merge_briandais_rec(A->son, B->son);
  }
  else {//if(A->key < B->key) {
    A->brother = merge_briandais_rec(A->brother, B);
  }

  return A;
}

int update_cpts(briandais_t *tree) {
  int r = 0;
  briandais_t *t;
  
  if(tree == NULL)
    return 0;
  else if(tree->key == '\0') {
    tree->cpt = 1;
  }
  else {
    t = tree->son;
    while (t != NULL) {
      r += update_cpts(t);
      t = t->brother;
    }
    tree->cpt = r;
  }
  
  return tree->cpt;
}

briandais_t* merge_briandais(briandais_t *A, briandais_t *B) {
  briandais_t *tree = merge_briandais_rec(A, B);
  briandais_t *t = tree;
  while(t != NULL) {
    update_cpts(t);
    t = t->brother;
  }

  return tree;
}

TrieHybride* convert_to_hybrid(briandais_t* tree) {
  TrieHybride *th_son=NULL, *th_bro=NULL;
  int end = 0;
  if(tree == NULL)
    return NULL;
  if(tree->son != NULL) {
    if(tree->son->key == '\0')
      end++;
    else
      th_son = convert_to_hybrid(tree->son);
  }
  if(tree->brother != NULL)
    th_bro = convert_to_hybrid(tree->brother);
  return trie_hybride(tree->key, end, NULL, th_son, th_bro);
}

int export_to_latex_rec(briandais_t *tree, FILE* f, int height) {
  static int offset = 0;
  static int node_id = 1;
  int id, relative_id;
  
  if(tree != NULL) {
    id = node_id;
    fprintf(f, "\\node at (%d,-%d) (%d) ",\
	    offset, height, node_id++);
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
  fprintf(f,"\\documentclass{article}\n\
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


int export_to_svg_rec(briandais_t *tree, FILE* f, int height, int* offset, int* max_height) {
  int my_offset = *offset;
  int bro_offset, gap;
  int x, y;
  
  if(tree != NULL) {
    fprintf(f, "<text x=\"%d\" y=\"%d\" fill=\"black\" font-size=\"20\"><!-- offset=%d -->",
	    my_offset*SVG_FACTOR, SVG_BASE+height*SVG_FACTOR, my_offset);
    if(tree->key != '\0')
      fprintf(f, "%c %d</text>\n", tree->key, tree->cpt);
    else
      fprintf(f, "$</text>\n");
    if(export_to_svg_rec(tree->son, f, height+1, offset, max_height) != -1) {
      x = my_offset*SVG_FACTOR+6;
      y = SVG_BASE+5+height*SVG_FACTOR;
      fprintf(f, "<path d=\"M%d,%d l0,18 l-2,0 l2,5 l2,-5 l-2,0\" style=\"stroke:black\"/>\n", x, y);
    }
    if(tree->brother != NULL)
      (*offset)++;
    if((bro_offset = export_to_svg_rec(tree->brother, f, height, offset, max_height)) != -1) {
      x = my_offset*SVG_FACTOR+15;
      y = SVG_BASE-7+height*SVG_FACTOR;
      gap = bro_offset - my_offset;
      fprintf(f, "<path d=\"M%d,%d l%d,0 l0,-2 l5,2 l-5,2 l0,-2\" style=\"stroke:black\"/>\n", x, y, gap*22+23*(gap-1));
    }
    if(height > *max_height)
      *max_height = height;
    return my_offset;
  }
  return -1;
}

int get_nb_digits(int n) {
  int d=1;
  while(n>9) {
    n = n/10;
    d++;
  }
  return d;
}

void export_to_svg(briandais_t *tree, char* filename) {
  FILE *f;
  int i;
  int width=0, height=0, nb_digits;
  int sizes_pos, rect_size_pos;

  if((f = fopen(filename,"w")) == NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  /* Header of svg file */
  fprintf(f,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\
 \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\
<svg viewBox = \"0 0 ");
  sizes_pos = (int)ftell(f);
  fprintf(f, "0123456789 0123456789\" version = \"1.1\"\n\
xmlns=\"http://www.w3.org/2000/svg\"\
 xmlns:xlink= \"http://www.w3.org/1999/xlink\">\n\n\
<rect ");
  rect_size_pos = (int)ftell(f);
  fprintf(f, "width=\"0123456789\" height=\"0123456789\" fill=\"white\"/>\n");

  /* Body */
  export_to_svg_rec(tree, f, 0, &width, &height);

  /* End of file */
  fprintf(f,"\n</svg>\n");

  /* Modifying size of viewBox in svg */
  if(fseek(f, sizes_pos, SEEK_SET) == -1) {
    perror("fseek");
    exit(1);
  }
  width = 45*width+100;
  nb_digits = get_nb_digits(width);
  for(i=10; i>nb_digits; i--)
    fprintf(f, " ");
  fprintf(f, "%d ", width);
  height = 47*height;
  nb_digits = get_nb_digits(height);
  for(i=10; i>nb_digits; i--)
    fprintf(f, " ");
  fprintf(f, "%d", height);

  /* Modifying size of background rect in svg */
  if(fseek(f, rect_size_pos, SEEK_SET) == -1) {
    perror("fseek");
    exit(1);
  }
  nb_digits = get_nb_digits(width) + get_nb_digits(height);
  fprintf(f, "width=\"%d\" height=\"%d\" fill=\"white\"/>", width, height);
  for(i=20-nb_digits; i>0; i--)
    fprintf(f, " ");

  fclose(f);
}

