#include "trieHybride_primitives.h"

// Fonction permettant de creer un trie hybride.
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

//Libere la memoire allouee au trie hybride
void free_trie_hybride(TrieHybride * t){
  if(t){
    free_trie_hybride(t->inferieur);
    free_trie_hybride(t->egal);
    free_trie_hybride(t->superieur);
    free(t);
  }
}

//Renvoi le caractere a la racine du trie
char racine(TrieHybride * t){
  return t->c;
}

//Accesseurs
TrieHybride * inferieur(TrieHybride * t){
  return t->inferieur;
}

TrieHybride * egal(TrieHybride * t){
  return t->egal;
}

TrieHybride * superieur(TrieHybride * t){
  return t->superieur;
}

//Teste si le trie passe en parametre est vide 
int est_trie_vide(TrieHybride * t){
  return t==NULL ? 1 : 0;
}

//Cree le trie hybride correspondant au mot passe en parametre
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

//Rempli le fichier passe en parametre avec le trie hybride, converti
//au format dot
int remplir_dot(FILE * f, TrieHybride * t, int n){
    
  int ninf,neq,nsup;
  fprintf(f,"%d [label=\"%c\"",n,t->c);
  if(t->fin){
    fprintf(f," color=green fill=blue");
  }
  fprintf(f,"];\n");

  if(t->inferieur==NULL && t->egal==NULL && t->superieur==NULL){
    return n+1;
  }

  if(t->inferieur){
    ninf=remplir_dot(f,t->inferieur,n+1);
    fprintf(f,"%d->%d [label=\"&lt;\"];\n",n,n+1);
  }else{
    ninf=n+1;
  }

  if(t->egal){
    neq=remplir_dot(f,t->egal,ninf);
    fprintf(f,"%d->%d [label=\"=\"];\n",n,ninf);
  }else{
    neq=ninf+1;
  }

  if(t->superieur){
    nsup=remplir_dot(f,t->superieur,neq);
    fprintf(f,"%d->%d [label=\"&gt;\"];\n",n,neq);
  }else{
    nsup=neq;
  }

  return nsup+1;
}

//Cree et rempli le fichier dot avec le trie passee en parametre
void generer_fichier_dot(char * nom_fichier, TrieHybride * t){
  FILE * f;
  if((f=fopen(nom_fichier,"w"))==NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(f,"digraph fichier {\n");
  remplir_dot(f,t,1);
  fprintf(f,"}\n");
  fclose(f);
}

//Converti le fichier dot produit par la fonction ci-dessus en fichier svg.
void creer_fichier_svg(char * nom_fichier, TrieHybride * t){
  char buff[256];
  generer_fichier_dot(nom_fichier,t);
  sprintf(buff,"dot -O -Tsvg %s",nom_fichier);
  system(buff); 
}

//Rempli le fichier passe en parametre avec le trie hybride.
void remplir_latex(FILE * f, TrieHybride * t){
  if(t){
    if(t->fin){
      fprintf(f,"[.\\node[blue]{%c}; \n",t->c);
    }else{
      fprintf(f,"[.%c \n",t->c);
    }
    if(t->inferieur){
      fprintf(f,"\\edge node [auto=right] {$<$};\n");  
      remplir_latex(f,t->inferieur);
    }
    if(t->egal){
      fprintf(f,"\\edge node {=};\n");  
      remplir_latex(f,t->egal);
    }
    if(t->superieur){  
      remplir_latex(f,t->superieur);
    }
    fprintf(f,"]");
  }
}

//Genere le fichier latex correspondant au trie passe en parametre
void generer_fichier_latex(char * nom_fichier, TrieHybride * t){
  FILE * f;
  if((f=fopen(nom_fichier,"w"))==NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(f,"\\documentclass{article}\n");
  fprintf(f,"\\usepackage{tikz-qtree}\n");
  fprintf(f,"\\usepackage{verbatim}\n");
  fprintf(f,"\\usepackage[active,tightpage]{preview}\n");
  fprintf(f,"\\PreviewEnvironment{tikzpicture}\n");
  fprintf(f,"\\begin{document}\n");
  fprintf(f,"\\begin{tikzpicture}[every tree node/.style={draw,circle}]\n");
  fprintf(f,"\\Tree\n");
  remplir_latex(f,t);
  fprintf(f,"\\end{tikzpicture}\n");
  fprintf(f,"\\end{document}\n");
  fclose(f);
}

/*
  Fonction permettant d'inserer un mot dans le trie
*/
TrieHybride * ajouter_trie_hybride(char * mot, TrieHybride *t){
  int n=strlen(mot);
  //Si le trie est vide, on renvoi l'arbre correspondant au mot
  if(est_trie_vide(t)){
    return creer_mot(mot);
  }else{
    //Sinon, s'il ne reste qu'une lettre dans le mot et que celle-ci
    //correspond a la lettre present a la racine du trie, cela veut dire
    //que le noeud représente la fin du mot que l'on veut inserer.
    if(n==1 && mot[0]==racine(t)){
      t->fin=1;
      return t;
    } 
    
    //Si la premiere lettre du mot est inferieure a celle presente a la racine
    //On insere le mot dans la branche correspondante.
    if(mot[0]<racine(t)){
      t->inferieur=ajouter_trie_hybride(mot,inferieur(t));
      return t;
    }else if(mot[0]>racine(t)){//De meme si la lettre est superieure.
      t->superieur=ajouter_trie_hybride(mot,superieur(t));
      return t;
    }else{
      //ici, la premiere lettre du mot est la meme que celle de la racine.
      //On peut donc inserer le mot, prive de sa premiere lettre dans la
      //branche correspondante
      t->egal=ajouter_trie_hybride(mot+1,egal(t));
      return t;
    }
  }
}
