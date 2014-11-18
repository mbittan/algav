#ifndef _GESTION_FICHIER_H_
#define _GESTION_FICHIER_H_

#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHAKESPEARE_DIR "./data/shakespeare/"
#define DATA_DIR "./data/"

/*
  Ouvre le fichier correspondant a nom. Retourne le descripteur de fichier
  associé.
*/
int ouvrir_fichier(char * nom);

/*
  Lit dans le fichier associé au descripteur fd le mot suivant. Deplace
  l'offset de fd de maniere appropriée. On suppose que le tableau mot
  contient la place necessaire pour contenir le mot suivant.
  Retourne le nombre de caracteres lus, ou -1 si une erreur s'est produite.
*/
int mot_suivant(int fd, char * mot);

#endif
