#include "trieHybride_simple.h"
#include "gestion_fichier.h"
#include "liste.h"
#include "briandais.h"

void print(void * d){
  printf("Mot : %s\n", (char *) d);
}
int main(int argc, char ** argv){
  TrieHybride * t = NULL;
  double res;
  char buff[100];
  int fd=ouvrir_fichier(DATA_DIR"exemple_de_base");
  if(fd<0){
    perror("open");
    exit(1);
  }
  memset(buff,'\0',100*sizeof(char));
  while(mot_suivant(fd,buff)){
    t=ajouter_trie_hybride(buff,t);
   } 
  briandais_t * b=conversion(t);
  Liste * l = list_briandais(b);
  map(l,print);
  destroy_liste(l);
  free_trie_hybride(t);
  return EXIT_SUCCESS;
}
