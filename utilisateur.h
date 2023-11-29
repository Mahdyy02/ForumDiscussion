#ifndef UTILISATEUR_H_INCLUDED
#define UTILISATEUR_H_INCLUDED
#include "date.h"

typedef struct{
    char* Nom;
    char* Prenom;
    char* Adresse;
    Date Date_de_naissance;
    unsigned int Numero_telephone;
    unsigned int Numero_inscription;
    char* Adresse_email;
    char* Password;
    char* Pseudo;
    unsigned short int Administrateur;

}UTILISATEUR;

void inscription(UTILISATEUR*);
void affichage(UTILISATEUR);
void sauvegarder_utulisateur(utilisateur);


#endif