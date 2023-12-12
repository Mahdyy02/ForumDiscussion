#ifndef FORUM_H_INCLUDED
#define FORUM_H_INCLUDED
#include "rubrique.h"
#include "utilisateur.h"

typedef struct {
    char* Adresse_internet;
    char* Adresse_e_mail;
    unsigned int Nombre_utilisateurs;
    unsigned int Nombre_invites;
    Liste_rubrique Rubriques;
    UTILISATEUR* Utilisateurs;
}FORUM;

void saisir_forum();

#endif

