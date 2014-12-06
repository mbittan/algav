#include "benchmark.h"

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
  Liste *l = fichiers_reguliers(SHAKESPEARE_DIR);
  Element *e = l->debut;
  briandais_t *tree = NULL;
  int i;
  
  for(i=0; i<l->taille; i++) {
    tree = lire_fichier_briandais((char*)e->data, tree);
    e = e->suiv;
  }

  export_to_svg(tree, "shakespeare.svg");
}

int main() {
  bench_insert_briandais();
  return 0;
}
