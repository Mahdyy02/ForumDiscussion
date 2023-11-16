#ifndef RUBRIQUE_H_INCLUDED
#define RUBRIQUE_H_INCLUDED
#include "date.h"

typedef struct{
    char* Théme ;
    Date Date_de_poste;
    unsigned int Numero_inscription;
    char* Message;
    char* Liste_internet;

}RUBRIQUE;

#endif
