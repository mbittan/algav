#include "trieHybride_simple.h"
#include "gestion_fichier.h"

int main(int argc, char ** argv){
  TrieHybride * t = NULL;
  int res;
  char buff[100];
 
  int fd=ouvrir_fichier(SHAKESPEARE_DIR"hamlet.txt");
  if(fd<0){
    perror("open");
    exit(1);
  }
  memset(buff,'\0',100*sizeof(char));
  while(mot_suivant(fd,buff)){
    printf("%s\n",buff);
    t=ajouter_trie_hybride(buff,t);
  }
  res=comptage_mots(t);
  printf("%d\n",res);
  generer_fichier_latex("test.tex",t);
  return EXIT_SUCCESS;
}
