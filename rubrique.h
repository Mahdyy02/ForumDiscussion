#ifndef RUBRIQUE_H_INCLUDED
#define RUBRIQUE_H_INCLUDED
#include "date.h"
#include "message.h"

typedef struct{
    char* Theme;
    Date Date_de_poste;
    unsigned int Numero_inscription;
    unsigned int Nombre_messages;
    char** Liste_internet;
    unsigned int Numero_de_sites;

}RUBRIQUE;

void affichage_rubrique(RUBRIQUE);
void saisir_rubrique(RUBRIQUE*);
void sauvegarder_message(MESSAGES m, RUBRIQUE r);
void sauvegarder_rubrique(MESSAGES m , RUBRIQUE r);

#endif
