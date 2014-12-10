#include "trieHybride_simple.h"

/*
  Fonction qui recherche un mot dans le trie. Renvoi 1 si le mot est present,
  0 sinon
*/
int recherche_trie_hybride(TrieHybride * t, char * mot){
  //Si le trie est vide, cela veut forcement dire que le mot n'est pas present
  if(est_trie_vide(t)){
    return 0;
  }else{
    int n = strlen(mot);
    //Sinon, si la lettre a la racine et la derniere lettre du mot sont egales
    //Cela veut dire que l'on est arrive au noeud ou doit se trouver la fin du 
    //mot. On retourne donc le champ 'fin' du noeud, qui vaut 1 si le noeud
    //Represente la fin d'un mot, 0 sinon.
    if(n==1 &&  mot[0]==racine(t)){
      return t->fin;
    }else{
      //Si la premiere lettre du mot est plus petite que celle presente a la
      //racine, cela veut dire que l'on doit chercher dans la branche 'inferieur'
      if(mot[0]<racine(t)){
	return recherche_trie_hybride(inferieur(t),mot);
      }else if(mot[0]>racine(t)){//De meme si la lettre est superieure
	return recherche_trie_hybride(superieur(t),mot);
      }else{
	//Sinon, cela veut dire que la premiere lettre du mot et celle de la 
	//racine sont egales. Il faut donc chercher le mot prive de sa premiere lettre
	//dans la branche 'egal' du noeud.
	return recherche_trie_hybride(egal(t),mot+1);
      }
    }
  }
}

/*
Compte le nombre de mots dans le trie
*/
int comptage_mots(TrieHybride * t){
  if(t==NULL){
    return 0;
  }
  int inf,eq,sup;
  inf=comptage_mots(t->inferieur);
  eq=comptage_mots(t->egal);
  sup=comptage_mots(t->superieur);
  if(t->fin){
    return 1+inf+eq+sup;
  }else{
    return inf+eq+sup;
  }
}

/*
  Fonction recursive permettant d'afficher la liste des mots present dans le
  trie, dans l'ordre alphabetique
*/
void afficher_liste_mots_rec(TrieHybride * t, char * buff, int n){
  if(t==NULL){
    return;
  }
  afficher_liste_mots_rec(t->inferieur,buff,n);
  buff[n]=t->c;
  buff[n+1]='\0';
  if(t->fin){
    printf("%s\n",buff);
  }
  afficher_liste_mots_rec(t->egal,buff,n+1);
  buff[n]='\0';
  afficher_liste_mots_rec(t->superieur,buff,n);
}

void afficher_liste_mots(TrieHybride * t){
  char buff[100];
  afficher_liste_mots_rec(t,buff,0);
}

/*
  Rempli la liste passe en parametre avec les mots present dans le trie
*/
void liste_mots_rec(TrieHybride * t, char * buff, int n, Liste * l){
  if(t==NULL){
    return;
  }
  liste_mots_rec(t->inferieur,buff,n,l);
  buff[n]=t->c;
  buff[n+1]='\0';
  if(t->fin){
    inserer_fin(l,strdup(buff));
  }
  liste_mots_rec(t->egal,buff,n+1,l);
  buff[n]='\0';
  liste_mots_rec(t->superieur,buff,n,l);
}

Liste * liste_mots(TrieHybride *t){
  Liste * l = creer_liste();
  char buff[100];
  liste_mots_rec(t,buff,0,l);
  return l;
}

/*
  Compte le nombre de pointeurs vers NULL
*/
int comptage_nil(TrieHybride * t){
  if(t==NULL){
    return 1;
  }

  int n1,n2,n3;
  n1=comptage_nil(t->inferieur);
  n2=comptage_nil(t->egal);
  n3=comptage_nil(t->superieur);
  return n1+n2+n3;
} 

//Renvoi le max de deux entiers
int max(int a, int b){
  if(a<b){
    return b;
  }else{
    return a;
  }
}

/*
  Calcule la hauteur du trie
*/
int hauteur(TrieHybride *t){
  if(t==NULL){
    return 0;
  }

  int n1,n2,n3;
  n1=hauteur(t->inferieur);
  n2=hauteur(t->egal);
  n3=hauteur(t->superieur);
  return 1+max(max(n1,n2),n3); 
}

/*
  Calcule la profondeur moyenne
*/
double profondeur_moyenne(TrieHybride * t){
  if(t==NULL){
    return 0;
  }
  int n1,n2,n3;
  n1=hauteur(t->inferieur);
  n2=hauteur(t->egal);
  n3=hauteur(t->superieur);
  return (n1+n2+n3)/3.0;
}

/*
  Renvoie le nombre de mots dont le prefixe est le mot passe en parametre
*/
int prefixe(TrieHybride * t, char * mot){
  //Si l'arbre est vide, on renvoie 0.
  if(t==NULL){
    return 0;
  }

  int n = strlen(mot);

  //Si on est arrive a la fin du mot, et que la lettre a la racine du trie
  //correspond a la derniere lettre du mot, on compte le nombre de mots
  //du sous-arbre 'egal'
  if(n==1 && mot[0]==racine(t)){
    return t->fin+comptage_mots(egal(t));
  }

  //Sinon, si la premiere lettre du mot est inferieur a celle presente a la 
  //racine du trie, on cherche dans le sous arbre 'inferieur'
  if(mot[0]<racine(t)){
    return prefixe(inferieur(t),mot);
  }
  if(mot[0]>racine(t)){//De meme si la lettre est superieure
    return prefixe(superieur(t),mot);
  }

  //Sinon, cela veut dire que la premiere lettre du mot est egale a celle de la
  //racine, et donc on cherche le resultat dans le sous arbre 'egal', en
  //privant le mot de sa premiere lettre
  return prefixe(egal(t),mot+1);
}

//Fonction permettant d'extraire le minimum d'un trie (c'est a dire le sous
//arbre qui n'a pas de fils 'inferieur'
TrieHybride * extraire_minimum(TrieHybride * t, TrieHybride * res){
  //Si on a trouve le minimum, on recupere les info pertinentes et
  //On libere la memoire alloue au noeud.
  //On retourne le fils 'superieur' a l'appelant
  if(t->inferieur==NULL){
    TrieHybride * aux = t->superieur;
    res->c=t->c;
    res->fin=t->fin;
    res->inferieur=NULL;
    res->superieur=NULL;
    res->egal=t->egal;
    free(t);
    return aux;
  }else{
    //Sinon, on effectue un appel recursif. 
    t->inferieur=extraire_minimum(t->inferieur,res);
    return t;
  }
}

//Fonction permettant de supprimer la racine d'un trie (on suppose qu'il n'y a
//pas de fils 'egal').
TrieHybride * supprimer_racine(TrieHybride * t){
  //Si les deux autres fils pointent vers NULL, on peut directement supprimer le noeud.
  if(t->inferieur==NULL && t->superieur==NULL){
    free(t);
    return NULL;
  }else if(t->inferieur==NULL){
    //Sinon, si le fils inferieur pointe vers NULL, on peut mettre le
    //fils superieur a la place de la racine
    TrieHybride * aux = t->superieur;
    t->c=aux->c;
    t->fin=aux->fin;
    t->inferieur=aux->inferieur;
    t->egal=aux->egal;
    t->superieur=aux->superieur;
    free(aux);
    return t;
  }else if(t->superieur==NULL){
    //De meme si le fils superieur pointe vers NULL
    TrieHybride * aux = t->inferieur;
    t->c=aux->c;
    t->fin=aux->fin;
    t->inferieur=aux->inferieur;
    t->egal=aux->egal;
    t->superieur=aux->superieur;
    free(aux);
    return t;
  }else{
    //Si on arrive ici, cela veut dire qu'aucun des deux fils ne pointe vers
    //NULL. Dans ce cas, on doit extraire le minimum du fils superieur et le
    //mettre a la racine, pour que l'arbre resultant soit toujours un trie
    //hybride.
    TrieHybride res;
    t->superieur=extraire_minimum(t->superieur,&res);
    t->c=res.c;
    t->fin=res.fin;
    t->egal=res.egal;
    return t;
  }
}

/*
  Fonction de suppression d'un mot. Renvoi le trie hybride dans lequel le mot
  est supprime.
*/
TrieHybride * supprimer(TrieHybride * t, char * mot){
  //Si le trie est vide, on renvoie le trie vide
  if(t==NULL){
    return NULL;
  }

  int n = strlen(mot);

  //Si on est arrive a la fin du mot, et sur le noeud representant la derniere
  //lettre du mot, on indique que le noeud ne represente plus la fin d'un mot.
  //Si le noeud n'avait pas de fils egal, on le supprime.
  if(n==1 && mot[0]==racine(t)){
    t->fin=0;
    if(t->egal==NULL){
      return supprimer_racine(t);
    }else{
      return t;
    }
  }

  //Si la premiere lettre du mot est inferieur a la lettre du noeud, on
  //cherche dans le fils inferieur
  if(mot[0]<racine(t)){
    t->inferieur=supprimer(inferieur(t),mot);
    return t;
  }else if(mot[0]>racine(t)){
    t->superieur=supprimer(superieur(t),mot);
    return t;
  }else{
    //Ici, la premiere lettre du mot est egale a celle du noeud, on va donc
    //supprimer le mot prive de sa premiere lettre dans le fils 'egal'.
    //Ensuite, si le fils egal est NULL et que le noeud ne represente pas la fin d'un mot,
    //on peut le supprimer.
    t->egal=supprimer(egal(t),mot+1);
    if(t->egal==NULL && t->fin==0){
      return supprimer_racine(t);
    }else{
      return t;
    }
  }
}
