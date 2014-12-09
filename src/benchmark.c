#include "benchmark.h"

Liste *l;
briandais_t *tree;
int loading;

void* loading_animation(void* a) {
  while(1) {
    if(!loading)
      break;
    printf("\b|");
    fflush(stdout);
    usleep(250000);
    if(!loading)
      break;
    printf("\b/");
    fflush(stdout);
    usleep(250000);
    if(!loading)
      break;
    printf("\b-");
    fflush(stdout);
    usleep(250000);
    if(!loading)
      break;
    printf("\b\\");
    fflush(stdout);
    usleep(250000);
  }
  printf("\b");
  fflush(stdout);
  pthread_exit(NULL);
}

long bench(void (*f)()) {
  struct timeval tv;
  long start, end;
  pthread_t loading_thread;

  // get current time before launching function f
  if(gettimeofday(&tv, NULL) != 0)
    return -1;
  start = tv.tv_sec*1000000 + tv.tv_usec;

  // execute f + loading animation
  loading = 1;
  pthread_create(&loading_thread, NULL, loading_animation, NULL);
  f();
  loading = 0;
  pthread_join(loading_thread, NULL);

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

void bench_delete_briandais() {
  Element *e = l->debut;
  int i=0, fd;
  char buff[1024];

  while(strcmp((char*)e->data, "./data/shakespeare/hamlet.txt") != 0 &&
	i<l->taille) {
    e = e->suiv;
    i++;
  }
  if(i == l->taille) {
    perror("bench_delete_briandais");
    exit(1);
  }

  fd = ouvrir_fichier((char*)e->data);
  
  while(mot_suivant(fd, buff) > 0) {
    delete_briandais(&tree, buff);
  }

  close(fd);
}

void bench_search_briandais() {
  Element *e = l->debut;
  int i, fdH=-1, fdA=-1, found=0, not_found=0;
  char buff[1024];

  for(i=0; i<l->taille; i++) {
    if(fdH == -1 &&
       strcmp((char*)e->data, "./data/shakespeare/hamlet.txt") == 0)
      fdH = ouvrir_fichier((char*)e->data);
    else if(fdA == -1 && 
	    strcmp((char*)e->data, "./data/shakespeare/allswell.txt") == 0)
      fdA = ouvrir_fichier((char*)e->data);
    if(fdH != -1 && fdA != -1)
      break;
    e = e->suiv;
  }

  if(fdH == -1 || fdA == -1) {
    perror("bench_search_briandais");
    exit(1);
  }

  while(mot_suivant(fdH, buff) > 0) {
    if(search_briandais(tree, buff))
      found++;
    else
      not_found++;
  }
  while(mot_suivant(fdA, buff) > 0) {
    if(search_briandais(tree, buff))
      found++;
    else
      not_found++;
  }

  close(fdA);
  close(fdH);
  printf("\bFound %d/%d words\n", found, not_found);
}

int main() {
  l = fichiers_reguliers(SHAKESPEARE_DIR);

  printf("Benchmarking insertion in de la Briandais tries :\n\
Inserting all Shakespeare plays...\n");
  printf("Insertion done in %f seconds.\n",
	 MS_TO_S(bench(bench_insert_briandais)));

  printf("Benchmarking deletion of Hamlet words in de la Briandais trie :\n\
Deleting all Hamlet words ...\n");
  printf("Deletion done in %f seconds.\n",
	 MS_TO_S(bench(bench_delete_briandais)));

  printf("Benchmarking search of All's Well and Hamlet words in de la Briandais\
 trie :\nSearching All's Well and Hamlet words ...\n");
  printf("Search done in %f seconds.\n",
	 MS_TO_S(bench(bench_search_briandais)));

  printf("Benchmarking destruction of a de la Briandais trie :\n");
  printf("Destruction done in %f seconds.\n",
	 MS_TO_S(bench(bench_destroy_briandais)));
  
  return 0;
}
