#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED
#include "date.h"

#define MAX_STRING_LENGTH 100

typedef struct{
    char* Titre;
    char** Textes;
    Date Date_de_poste;
    unsigned int Numero_incription;
    unsigned int Numero_de_messages; // TO BE BACK HERE
    
}MESSAGE;

void saisir_message(MESSAGE*);
void affichage_message(MESSAGE);

#endif
