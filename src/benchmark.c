#include "benchmark.h"

Liste *l;
briandais_t *tree;

long bench(void (*f)()) {
  struct timeval tv;
  long start, end;

  // get current time before launching function f
  if(gettimeofday(&tv, NULL) != 0)
    return -1;
  start = tv.tv_sec*1000000 + tv.tv_usec;

  // execute f
  f();

  // get current time after completion of function f
  if(gettimeofday(&tv, NULL) != 0)
    return -1;
  end = tv.tv_sec*1000000 + tv.tv_usec;

  // return function f's execution duration
  return end - start;
}

void bench_insert_briandais() {
  Element *e = l->debut;
  int i;
  
  tree = NULL;

  for(i=0; i<l->taille; i++) {
    tree = lire_fichier_briandais((char*)e->data, tree);
    e = e->suiv;
  }
}

void bench_destroy_briandais() {
  destroy_briandais(&tree);
}

int main() {
  l = fichiers_reguliers(SHAKESPEARE_DIR);

  printf("Benchmarking insertion in de la Briandais tries :\n\
Inserting all Shakespeare plays...\n");
  printf("Insertion done in %f seconds.\n",
	 MS_TO_S(bench(bench_insert_briandais)));

  printf("Benchmarking destruction of a de la Briandais trie :\n");
  printf("Destruction done in %f seconds.\n",
	 MS_TO_S(bench(bench_destroy_briandais)));
  
  return 0;
}
