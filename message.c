#include <stdio.h>
#include <stdlib.h>
#include "message.h"

#define MAX_STRING_LENGTH 100

void saisir_message(MESSAGES* m){
    printf("Le titre de message est: ");
    m->Titre = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
    fgets(m->Titre, MAX_STRING_LENGTH, stdin);

    m->Numero_de_messages = 0;
    m->Textes = (char**) malloc(MAX_STRING_LENGTH * sizeof(char*));
    do{
        printf("Le contenu de message(vide pour quitter): ");
        unsigned int i = m->Numero_de_messages;
        (m->Textes)[i] = (char*) malloc(MAX_STRING_LENGTH * sizeof(char));
        fgets((m->Textes)[i], MAX_STRING_LENGTH, stdin);
        (m->Numero_de_messages)++;
    } while ((m->Textes)[(m->Numero_de_messages)-1] != "\n");
    
}

void affichage_message(MESSAGES m){

    for(int i = 0; i < m.Numero_de_messages; i++){

        if(i == 0){
            printf("Le titre de message est: %s\n", m.Titre);
            printf("premier message: \n");
            printf("%s\n", m.Textes[i]);
        }else{
            printf("Reply %i: \n", i);
            printf("%s\n", m.Textes[i]);
        }
    }

    printf("la date de poste est: %i/%i/%i\n",m.Date_de_poste.jour,m.Date_de_poste.mois,m.Date_de_poste.annee);
}