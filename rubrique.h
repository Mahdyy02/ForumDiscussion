#ifndef RUBRIQUE_H_INCLUDED
#define RUBRIQUE_H_INCLUDED
#include "date.h"

typedef struct{
    char* Theme;
    Date Date_de_poste;
    unsigned int Numero_inscription;
    char* Message;
    char** Liste_internet;
    unsigned int Numero_de_sites;


}RUBRIQUE;

void affichage_rubrique(RUBRIQUE);
void saisir_rubrique(RUBRIQUE*);

#endif