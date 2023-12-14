#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED
#include "date.h"
#include "linked_lists.h"

typedef struct{
    char* Titre;
    Liste Messages; 
    Date Date_de_poste;
    unsigned int Numero_incription;
}MESSAGE;

typedef struct Noeud_message{
    MESSAGE Valeur;
    struct Noeud_message* Suivant;
}Noeud_message;

typedef struct Liste_message{
    struct Noeud_message* tete;
}Liste_message;

void saisir_message(MESSAGE*);
void affichage_message(MESSAGE);
Liste_message charger_message(char*);
void initialiser_liste_de_messages(Liste_message*);
void ajouter_liste_message(Liste_message*, MESSAGE);
void retirer_message(Liste_message*);
void detruire_liste_de_message(Liste_message*);

#endif