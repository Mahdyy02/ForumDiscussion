#ifndef RUBRIQUE_H_INCLUDED
#define RUBRIQUE_H_INCLUDED
#include "message.h"

typedef struct Noeud_liste_de_message{
    Liste_message Valeur;
    struct Noeud_liste_de_message* Suivant;
}Noeud_liste_de_message;

typedef struct{
    Noeud_liste_de_message* tete;
}Liste_de_liste_de_message;

typedef struct{
    char* Theme;
    Date Date_de_poste;
    unsigned int Numero_inscription;
    unsigned short int Supprime;
    Liste Sites_internet;
    Liste_de_liste_de_message Listes_messages;
}RUBRIQUE;

typedef struct Noeud_rubrique{
    RUBRIQUE valeur;
    struct Noeud_rubrique* Suivant;
}Noeud_rubrique;

typedef struct Liste_rubrique{
    Noeud_rubrique *tete;
}Liste_rubrique;

void affichage_rubrique(RUBRIQUE);
void saisir_rubrique(RUBRIQUE*);
void sauvegarder_message(MESSAGE, MESSAGE*, RUBRIQUE);
void charger_rubrique(RUBRIQUE*);
void sauvegarder_rubrique(RUBRIQUE);
void retirer_liste_de_message(Liste_de_liste_de_message *);
void detruire_liste_de_liste_de_message(Liste_de_liste_de_message *);
void charger_rubriques(Liste_rubrique*);
void initialiser_liste_rubriques(Liste_rubrique*);
void repondre_messsage_anonyme(MESSAGE, RUBRIQUE);
unsigned int nombre_rubriques();
void detruire_liste_rubrique(Liste_rubrique*);
void ajouter_rubrique(Liste_rubrique*, RUBRIQUE);
void initialiser_liste_de_liste_de_message(Liste_de_liste_de_message*);
void ajouter_liste_de_message(Liste_de_liste_de_message*, Liste_message);
void basculer_supression_message(RUBRIQUE* r, Liste_message LM, MESSAGE* m);
unsigned int indice_message_dans_liste_message(Liste_message, MESSAGE*);
void basculer_supression_rubrique(RUBRIQUE*);
void afficher_utilisateurs_rubrique(RUBRIQUE*);
void chercher_mot_messages(char*);
char* jours_plus_active();
void modifier_message(RUBRIQUE*, Liste_message*, MESSAGE*);

#endif