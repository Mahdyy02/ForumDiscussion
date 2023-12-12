#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_lists.h"


void initialiser_liste(Liste* L){
    L->tete = NULL;
}

void ajouter_element(Liste* L, char* valeur){

    // Je vais ajouter le nouveau noeud a la fin de la liste

    Noeud* nouveau_noeud = (Noeud*)malloc(sizeof(Noeud));
    nouveau_noeud->Valeur = strdup(valeur);
    nouveau_noeud->Suivant = NULL;

    if(L->tete == NULL){
        L->tete = nouveau_noeud;
        return;
    } 

    Noeud *iter = L->tete;
    while(iter->Suivant != NULL) iter = iter->Suivant;
    iter->Suivant = nouveau_noeud;
}

void afficher_liste(Liste* L){

    printf("[");
    Noeud* iter = L->tete;
    while(iter != NULL){
        if(iter->Suivant == NULL) printf("%s", iter->Valeur);
        else printf("%s, ", iter->Valeur);
        iter = iter->Suivant;
    }
    printf("]\n");

}

void afficher_element_liste_de_liste(Liste* L){

    printf("[");
    Noeud* iter = L->tete;
    while(iter != NULL){
        if(iter->Suivant == NULL) printf("%s", iter->Valeur);
        else printf("%s, ", iter->Valeur);
        iter = iter->Suivant;
    }
    printf("]");

}

char* retirer_element(Liste* L){

    if(L->tete == NULL){
        printf("Erreur: On ne peux pas retirer un element d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }

    if(L->tete->Suivant == NULL){
        char* valeur = strdup(L->tete->Valeur);
        free(L->tete->Valeur);
        free(L->tete);
        L->tete = NULL;
        return valeur;
    }

    Noeud *iter = L->tete;
    while(iter->Suivant->Suivant != NULL) iter = iter->Suivant;
    char* valeur = strdup(iter->Suivant->Valeur);
    free(iter->Suivant->Valeur);
    free(iter->Suivant);
    iter->Suivant = NULL;
    return valeur;

}

void detruire_liste(Liste* L){
    while(L->tete != NULL) retirer_element(L);
}

unsigned int longeur_liste(Liste* L){

    if(L->tete == NULL) return 0;

    unsigned int longeur = 0;

    Noeud *iter = L->tete;
    while(iter != NULL){
        iter = iter->Suivant;
        longeur++;
    }

    return longeur;

}