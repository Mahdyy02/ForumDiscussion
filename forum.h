#ifndef FORUM_H_INCLUDED
#define FORUM_H_INCLUDED 
#include "utilisateur.h"

typedef struct {
    char Adresse_internet[19];
    char* Adresse_e_mail;
    unsigned int Nombre_utilisateurs;
    unsigned int Nombre_invites;
    unsigned int Nombres_Rubriques;
    UTILISATEUR* Utilisateurs;
}FORUM;

void saisir_forum();

#endif

