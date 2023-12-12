#ifndef LINKED_LISTS_H_INCLUDED
#define LINKED_LISTS_H_INCLUDED

typedef struct Noeud{
    char* Valeur;
    struct Noeud* Suivant;
}Noeud;


typedef struct{
    Noeud* tete;
}Liste;

void initialiser_liste(Liste*);
void ajouter_element(Liste*, char*);
void afficher_liste(Liste*);
char* retirer_element(Liste*);
unsigned int longeur_liste(Liste*);
void detruire_liste(Liste*);

#endif