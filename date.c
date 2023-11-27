#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "date.h"

void Saisir_date(Date *d){

    while(1){

        printf("Donnez le mois: ");
        scanf("%d", &(d->mois));

        while(getchar() != '\n');

        if(d->mois >= 1 && d->mois <= 12)
            break;
        
        printf("Le mois doit être entre 1 et 12\n");
    }
    
    while(1){
        printf("Donnez le jour: ");
        scanf("%d", &(d->jour));

        while(getchar() != '\n');

        if((d->mois) < 8)
            if((d->mois)%2 == 1){
                if((d->jour) >= 1 && (d->jour) <= 31){
                    break;
                }
                printf("Le nombre du jour pour le mois %i doit être compris entre 1 et 31\n", d->mois);    
            }else{
                if((d->jour) >= 1 && (d->jour) <= 30){
                    break;
                }
                printf("Le nombre du jour pour le mois %i doit être compris entre 1 et 30\n", d->mois);    
            }
        else{
            if((d->mois)%2 == 0){
                if((d->jour) >= 1 && (d->jour) <= 31){
                    break;
                }
                printf("Le nombre du jour pour le mois %i doit être compris entre 1 et 31\n", d->mois);    
            }else{
                if((d->jour) >= 1 & (d->jour) <= 30){
                    break;
                }
                printf("Le nombre du jour pour le mois %i doit être compris entre 1 et 30\n", d->mois);    
            }
        }    
        
    }

    printf("Donnez l'année: ");
    scanf("%d", &(d->annee));


}

Date charger_date(char* chaine_date){

    Date d;

    char *jeton = strtok(chaine_date, "/");
    int indice = 0;

    while (jeton != NULL) {
        
        switch (indice){
        case 0:
            d.jour = atoi(jeton);
            break;
        case 1:
            d.mois = atoi(jeton);
            break;
        case 2:
            d.annee = atoi(jeton);
            break;
        }

        indice++;
        jeton = strtok(NULL, ";");
    }

    return d;
}