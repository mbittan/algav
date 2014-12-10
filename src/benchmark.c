#include "benchmark.h"

Liste *l, *trees_list;
briandais_t *tree;
TrieHybride *th;
int loading, nb_trees;
pthread_t threads[NB_THREADS];
pthread_mutex_t merge_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t lock;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* loading_animation(void* a) {
  while(loading) {
    printf("\b|");
    fflush(stdout);
    usleep(125000);
    printf("\b/");
    fflush(stdout);
    usleep(125000);
    printf("\b-");
    fflush(stdout);
    usleep(125000);
    printf("\b\\");
    fflush(stdout);
    usleep(125000);
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

void* insert_briandais_mthread(void* filename) {
  briandais_t *t = NULL, *t2 = NULL;
  t = lire_fichier_briandais((char*)filename, t);
  pthread_mutex_lock(&merge_lock);
  if(trees_list->taille > 0) {
    t2 = (briandais_t*) supprimer_debut(trees_list);
    pthread_mutex_unlock(&merge_lock);
    t = merge_briandais(t, t2);
    pthread_mutex_lock(&merge_lock);
  }
  inserer_debut(trees_list, (void*) t);
  nb_trees--;
  if(nb_trees == 0)
    pthread_cond_signal(&cond);
  pthread_mutex_unlock(&merge_lock);
  sem_post(&lock);

  pthread_exit(NULL);
}

void bench_insert_briandais_mthread() {
  Element *e = l->debut;
  int i;
  pthread_t thread;
  pthread_attr_t attr;
  briandais_t *t;
  
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  if(trees_list == NULL)
    trees_list = creer_liste();
  nb_trees = l->taille;
  sem_init(&lock, 0, NB_THREADS);
  
  for(i=0; i<l->taille; i++) {
    sem_wait(&lock); // pass if a thread is available
    pthread_create(&thread, &attr, insert_briandais_mthread, e->data);
    e = e->suiv;
  }
  pthread_attr_destroy(&attr);
  pthread_cond_wait(&cond, &merge_lock);

  tree = (briandais_t*) supprimer_debut(trees_list);
  while(trees_list->taille > 0) {
    t = (briandais_t*) supprimer_debut(trees_list);
    tree = merge_briandais(tree, t);
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

void bench_count_briandais() {
  printf("\bFound %d words.\n", count_briandais(tree));
}

void bench_count_null_briandais() {
  printf("\bFound %d null pointers.\n", count_null_briandais(tree));
}

void bench_list_briandais() {
  Liste *list = list_briandais(tree);
  char *tmp;
  while(list->taille > 0) {
    tmp = (char*) supprimer_debut(list);
    free(tmp);
  }
  free(list);
}

void bench_height_briandais() {
  printf("\bHeight = %d\n", height_briandais(tree));
}

void bench_average_depth_briandais() {
  printf("\bAverage depth = %f\n", average_depth_briandais(tree));
}

void bench_prefix_briandais() {
  
}

void bench_merge_briandais() {

}

void bench_convert_to_hybrid() {
  th = convert_to_hybrid(tree);
}

void bench_export_to_svg() {
  export_to_svg(tree, "shakespeare_briandais.svg");
  printf("\bExported to shakespeare_briandais.svg\n");
}

void bench_worst_insertion_briandais() {
  tree = insert_briandais(tree, "youtizzzzz");
}

void bench_memory_usage_briandais() {
  printf("\bShakespeare's de la Briandais trie uses %d bytes in memory.\n",
	 memory_usage_briandais(tree));
}

void print_line() {
  printf("\n===================================================================\
=============\n\n");
}

/*
 * Main
 */
int main() {
  char* tmp;

  // we get the list of Shakespeare's plays files
  l = fichiers_reguliers(SHAKESPEARE_DIR);


  /*******************************************\
  |*                BENCHMARKS               *|
  \*******************************************/

  printf("Benchmarking insertion in de la Briandais tries :\n\
Inserting all Shakespeare plays...\n");
  printf("Insertion done in %f seconds.\n",
	 MS_TO_S(bench(bench_insert_briandais)));
  print_line();

  printf("Benchmarking deletion of Hamlet words in de la Briandais trie :\n\
Deleting all Hamlet words ...\n");
  printf("Deletion done in %f seconds.\n",
	 MS_TO_S(bench(bench_delete_briandais)));
  print_line();

  printf("Benchmarking search of All's Well and Hamlet words in de la Briandais\
 trie :\nSearching All's Well and Hamlet words ...\n");
  printf("Search done in %f seconds.\n",
	 MS_TO_S(bench(bench_search_briandais)));
  print_line();

  printf("Benchmarking destruction of a de la Briandais trie :\n");
  printf("Destruction done in %f seconds.\n",
	 MS_TO_S(bench(bench_destroy_briandais)));
  print_line();

  printf("Benchmarking multithreaded insertion in de la Briandais tries :\n\
Inserting all Shakespeare plays...\n");
  printf("Multithreaded insertion done in %f seconds.\n",
	 MS_TO_S(bench(bench_insert_briandais_mthread)));
  print_line();
  
  printf("Benchmarking word counting in de la Briandais tries :\n");
  printf("Word counting done in %f seconds.\n",
	 MS_TO_S(bench(bench_count_briandais)));
  print_line();

  printf("Benchmarking null pointers counting in de la Briandais tries :\n");
  printf("Null pointers counting done in %f seconds.\n",
	 MS_TO_S(bench(bench_count_null_briandais)));
  print_line();

  printf("Benchmarking listing words in de la Briandais tries :\n");
  printf("Listing (and destrying of list) done in %f seconds.\n",
	 MS_TO_S(bench(bench_list_briandais)));
  print_line();

  printf("Benchmarking height computing in Shakespeare's de la Briandais trie :\
\n");
  printf("Height computing done in %f seconds.\n",
	 MS_TO_S(bench(bench_height_briandais)));
  print_line();

  printf("Benchmarking average depth computing in Shakespeare's de la Briandais\
 trie :\n");
  printf("Average depth computing done in %f seconds.\n",
	 MS_TO_S(bench(bench_average_depth_briandais)));
  print_line();

  printf("Benchmarking conversion to hybrid trie of Shakespeare's de la \
Briandais trie :\n");
  printf("Conversion done in %f seconds.\n",
	 MS_TO_S(bench(bench_convert_to_hybrid)));
  print_line();

  printf("Benchmarking worst insertion scenario in Shakespeare's de la\
 Briandais trie :\n");
  printf("Insertion of 'youtizzzzz' done in %f seconds.\n",
	 MS_TO_S(bench(bench_worst_insertion_briandais)));
  print_line();

  printf("Benchmarking exporting to SVG of Shakespeare's de la Briandais trie\
 :\n");
  printf("Export done in %f seconds.\n",
	 MS_TO_S(bench(bench_export_to_svg)));
  print_line();

  printf("Benchmarking memory usage of Shakespeare's de la Briandais trie :\n");
  printf("Memory usage benchmark done in %f seconds.\n",
	 MS_TO_S(bench(bench_memory_usage_briandais)));
  print_line();

  // Freeing memory
  destroy_briandais(&tree);

  // destroying l list
  while(l->taille > 0) {
    tmp = (char*)supprimer_debut(l);
    free(tmp);
  }
  free(l);

  if(trees_list != NULL)
    free(trees_list);
  
  return 0;
}
