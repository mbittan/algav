#include "trieHybride_simple.h"
#include "gestion_fichier.h"

int main(int argc, char ** argv){
  TrieHybride * t = NULL;
  double res;
  char buff[100];
  int i =0;
  int fd=ouvrir_fichier(DATA_DIR"exemple_de_base");
  if(fd<0){
    perror("open");
    exit(1);
  }
  memset(buff,'\0',100*sizeof(char));
  while(mot_suivant(fd,buff)){
    t=ajouter_trie_hybride(buff,t);
   } 
  t=ajouter_trie_hybride("toto",t);
  res=comptage_mots(t);
  printf("%d\n",res);
  // generer_fichier_latex("toto.dot",t);
  return EXIT_SUCCESS;
}
