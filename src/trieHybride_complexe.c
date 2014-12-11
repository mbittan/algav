#include "trieHybride_complexe.h"

//Fonction de conversion d'un trie hybride vers un arbre de la briandais
briandais_t * conversion(TrieHybride * t){
  //Si l'arbre est vide, on renvoie l'arbre vide
  if(t==NULL){
    return NULL;
  }
  //Sinon, on convertit le fils inferieur
  briandais_t * b = conversion(t->inferieur);
  briandais_t * b2, * aux;

  //Si le noeud represente la fin d'un mot, on cree un arbre ayant pour
  //fils l'arbre de la briandais representant la fin d'un mot.
  //Le frere du fils de cet arbre est alors la conversion du fils egal du trie
  //hybride
  if(t->fin){
    b2 = new_briandais(t->c,new_empty_briandais(),NULL);
    b2->son->brother=conversion(t->egal);
  }else{
    //Sinon, si le noeud ne represente pas la fin d'un mot, on cree un arbre de
    //la briandais n'ayant ni frere ni fils. Le fils de cet arbre est alors la
    //conversion du fils egal du trie hybride.
    b2 = new_briandais(t->c,NULL,NULL);
    b2->son=conversion(t->egal);
  }
  
  //Dans tout les cas, le frere de l'arbre de la briandais est la conversion
  //du fils superieur du trie hybride
  b2->brother=conversion(t->superieur);

  //On cherche le dernier frere de l'arbre de la briandais representant le 
  //fils inferieur.
  aux = b;
  while(aux && aux->brother!=NULL){
    aux=aux->brother;
  }

  //Si le pointeur est NULL, cela veut dire que la conversion
  //rend l'arbre vide, donc on renvoi b2
  if(aux==NULL){
    return b2;
  }else{
    //Sinon, on indique que le frere du dernier frere, est la conversion des
    //branches egal et superieure du trie hybride
    aux->brother=b2;
  }
  return b;
}

//Effectue une rotation droite sur le trie passe en parametre
TrieHybride * rotD(TrieHybride * t){
  TrieHybride * aux;
  aux=t->inferieur;
  t->inferieur=aux->superieur;
  aux->superieur=t;
  return aux;
}

//Effectue une rotation gauche sur le trie passe en parametre
TrieHybride * rotG(TrieHybride * t){
  TrieHybride * aux;
  aux=t->superieur;
  t->superieur=aux->inferieur;
  aux->inferieur=t;
  return aux;
}

//Fonction d'equilibrage d'un arbre
TrieHybride * equilibrer(TrieHybride * t){
  //Si l'arbre est vide, pas besoin d'equilibrage
  if(t==NULL){
    return t;
  }
  //On equilibre les trois sous arbres
  t->inferieur=equilibrer(t->inferieur);
  t->egal=equilibrer(t->egal);
  t->superieur=equilibrer(t->superieur);

  //On calcule la hauteur des fils inferieur et superieur.
  int hinf=hauteur(t->inferieur);
  int hsup=hauteur(t->superieur);
  int diff=hinf-hsup;

  //Si la difference des hauteurs est plus grande que 3 en valeur absolue, on
  //effectue les rotations appropriees, dans l'esprit des AVL
  if(diff>=2){
    int dinf=hauteur(t->inferieur->inferieur)-hauteur(t->inferieur->superieur);
    if(dinf<=-1){
      t->inferieur=rotG(t->inferieur);
    }
    t=rotD(t);
  }else if(diff<=-2){  
    int dsup=hauteur(t->superieur->inferieur)-hauteur(t->superieur->superieur);
    if(dsup>=1){
      t->superieur=rotD(t->superieur);
    }
    t=rotG(t);
  }
  return t;
}

TrieHybride * fusion_rec(TrieHybride * t1, TrieHybride * t2, char * buff, int n){
  if(t2==NULL){
    return t1;
  }

  t1=fusion_rec(t1,t2->inferieur,buff,n);
  buff[n]=t2->c;
  buff[n+1]='\0';
  if(t2->fin){
    t1=ajouter_trie_hybride(buff,t1);
  }
  t1=fusion_rec(t1,t2->egal,buff,n+1);
  buff[n]='\0';
  t1=fusion_rec(t1,t2->superieur,buff,n);
  return t1;
}

//Fusionne deux trie.
TrieHybride * fusion_trie_hybride(TrieHybride * t1, TrieHybride * t2){
  char buff[128];
  return fusion_rec(t1,t2,buff,0);
}
