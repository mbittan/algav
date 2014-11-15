#include "trieHybride_primitives.h"

int main(int argc, char ** argv){
  TrieHybride * t = NULL;
  char buff[100];
  FILE * f=fopen("./data/exemple_de_base","r");
  memset(buff,'\0',100*sizeof(char));
  while(fscanf(f,"%s ",buff)!=EOF){
    printf("%s\n",buff);
    t=ajouter_trie_hybride(buff,t);
    memset(buff,'\0',100*sizeof(char));
  }
  fclose(f);
  generer_fichier_xml("test.xml",t);


  return EXIT_FAILURE;
}
