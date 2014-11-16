#include "trieHybride_simple.h"

int main(int argc, char ** argv){
  TrieHybride * t = NULL;
  int res;
  char buff[100];
  FILE * f=fopen("./data/shakespeare/lear.txt","r");
  memset(buff,'\0',100*sizeof(char));
  while(fscanf(f,"%s ",buff)!=EOF){
    t=ajouter_trie_hybride(buff,t);
    memset(buff,'\0',100*sizeof(char));
  }
  fclose(f);  

  f=fopen("./data/shakespeare/lear.txt","r");
  memset(buff,'\0',100*sizeof(char));
  while(fscanf(f,"%s ",buff)!=EOF){
    res=recherche_trie_hybride(t,buff);
    if(!res){
      printf("mot %s non trouve !\n",buff);
    }
    memset(buff,'\0',100*sizeof(char));
  }
  fclose(f);
  generer_fichier_xml("test.xml",t);
  free_trie_hybride(t);

  return EXIT_FAILURE;
}
