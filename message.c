#include <stdio.h>
#include "message.h"

void affichage (MESSAGE m){

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