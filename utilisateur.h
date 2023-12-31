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
    unsigned short int Administrateur; // 1 si administrateur 
    unsigned short int Interdit; // 1 si interdit

}UTILISATEUR;

void inscription(UTILISATEUR*);
void affichage(UTILISATEUR);
void sauvegarder_utilisateur(UTILISATEUR);
void charger_utilisateur();
int first_index(char*, int, char);
void free_utilisateurs();
void basculer_interdiction_utilisateur(UTILISATEUR*);
void voir_messages_utilisateur(UTILISATEUR*);

#endif