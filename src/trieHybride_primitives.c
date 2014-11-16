#include "trieHybride_primitives.h"


TrieHybride * trie_hybride(char c, char fin, TrieHybride * inf, 
			   TrieHybride * eq, TrieHybride * sup){
  TrieHybride * t = (TrieHybride *) malloc(sizeof(TrieHybride));
  if(t==NULL){
    fprintf(stderr,"Erreur lors de l'allocation memoire d'un noeud (TH)\n");
    exit(EXIT_FAILURE);
  }
  t->c=c;
  t->fin=fin;
  t->inferieur=inf;
  t->egal=eq;
  t->superieur=sup;
  return t;
}

void free_trie_hybride(TrieHybride * t){
  free_trie_hybride(t->inferieur);
  free_trie_hybride(t->egal);
  free_trie_hybride(t->superieur);
  free(t);
}

char racine(TrieHybride * t){
  return t->c;
}

TrieHybride * inferieur(TrieHybride * t){
  return t->inferieur;
}

TrieHybride * egal(TrieHybride * t){
  return t->egal;
}

TrieHybride * superieur(TrieHybride * t){
  return t->superieur;
}

int est_trie_vide(TrieHybride * t){
  return t==NULL ? 1 : 0;
}

TrieHybride * creer_mot(char * mot){
  TrieHybride * t=NULL;
  int i;
  int n=strlen(mot);
  if(n==0){
    return NULL;
  }

  t=trie_hybride(mot[n-1],1,NULL,NULL,NULL);
  for(i=n-2;i>=0;i--){
    t=trie_hybride(mot[i],0,NULL,t,NULL);
  }

  return t;
}

void indenter(FILE *f, int niveau){
  int i=0;
  for(i=0;i<niveau;i++){
    fprintf(f,"  ");
  }
}
void remplir_xml(FILE *f,TrieHybride * t, int niveau){
  if(t==NULL){
    return;
  }

  indenter(f,niveau);
  fprintf(f,"<triehybride c='%c' fin='%d'>\n",t->c,t->fin);


  indenter(f,niveau+1);
  if(t->inferieur){
    fprintf(f,"<inferieur>\n");
    remplir_xml(f,t->inferieur,niveau+2);
    indenter(f,niveau+1);
    fprintf(f,"</inferieur>\n");  
  }else{
    fprintf(f,"<inferieur/>\n");
  }

  indenter(f,niveau+1);
  if(t->egal){
    fprintf(f,"<egal>\n");
    remplir_xml(f,t->egal,niveau+2);
    indenter(f,niveau+1);
    fprintf(f,"</egal>\n");
  }else{
    fprintf(f,"<egal/>\n");
  }

  indenter(f,niveau+1);
  if(t->superieur){  
    fprintf(f,"<superieur>\n");
    remplir_xml(f,t->superieur,niveau+2);
    indenter(f,niveau+1);
    fprintf(f,"</superieur>\n");
  }else{
    fprintf(f,"<superieur/>\n");
  }

  indenter(f,niveau);
  fprintf(f,"</triehybride>\n");
}

void generer_fichier_xml(char * nom_fichier, TrieHybride * t){
  FILE * f;
  if((f=fopen(nom_fichier,"w"))==NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  remplir_xml(f,t,0);
  fclose(f);
}

void print_trie_hybride(TrieHybride * t){
  if(t){
    printf("Rac : %c, fin %d\n",t->c,t->fin);
    print_trie_hybride(inferieur(t));
    print_trie_hybride(egal(t));
    print_trie_hybride(superieur(t));
  }else{
    printf("VIDE !\n");
  }
}

TrieHybride * ajouter_trie_hybride(char * mot, TrieHybride *t){
  int n=strlen(mot);
  if(est_trie_vide(t)){
    return creer_mot(mot);
  }else{
    if(n==0){
      t->fin=0;
      return t;
    }
    if(mot[0]<racine(t)){
      t->inferieur=ajouter_trie_hybride(mot,inferieur(t));
      return t;
    }else if(mot[0]>racine(t)){
      t->superieur=ajouter_trie_hybride(mot,superieur(t));
      return t;
    }else{
      t->egal=ajouter_trie_hybride(mot+1,egal(t));
      return t;
    }
  }
}