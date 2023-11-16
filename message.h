#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED
#include "date.h"

typedef struct{
    char* Titre;
    char** Textes;
    Date Date_de_poste;
    unsigned int Numero_incription;
    unsigned int Numero_de_messages; // TO BE BACK HERE
    
}MESSAGES;

void saisir_message(MESSAGES*);
void affichage_message(MESSAGES);

#endif