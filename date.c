#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>

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
                if((d->jour) >= 1 && (d->jour) <= 30){
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

    int result = sscanf(chaine_date, "%d/%d/%d", &d.jour, &d.mois, &d.annee);

    if (result != 3){
        printf("Échec de l'analyse de la chaîne de date.\n");
    }

    return d;
}

Date date_actuelle(){
    
    Date d;

    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    d.mois = localTime->tm_mon + 1;
    d.jour = localTime->tm_mday;
    d.annee = localTime->tm_year + 1900;

    return d;

}

int jour_semaine(Date d){

    int jour = d.jour;
    int mois = d.mois;
    int annee = d.annee;

    if (mois < 3) {
        mois += 12;
        annee--;
    }

    int k = annee%100;
    int j = annee/100;

    int jour_semaine = (jour + 13*(mois+1)/5 + k + k/4 + j/4 - 2*j)%7; // Algorithme de la Congruence de Zeller

    return (jour_semaine + 6)%7;

}