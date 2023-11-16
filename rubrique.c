#include <stdlib.h>
#include <stdio.h>
#include "rubrique.h"

#define MAX_STRING_LENGTH 100

void saisir_rubrique(RUBRIQUE* r){
    
        while(1){
        printf("Theme de la rubrique: ");
        r->Theme = malloc(MAX_STRING_LENGTH*sizeof(char));
        fgets(r->Theme, MAX_STRING_LENGTH, stdin);
        (r->Theme)[strlen(r->Theme) - 1] = '\0';

        int valid_string = 1;
        for(int i = 0; i < strlen(r->Theme) - 1;i++){
            if(!isupper(r->Theme[i]) && !islower(r->Theme[i]) || isdigit(r->Theme[i])){
                valid_string = 0;
                break;
            }
        }
        if(valid_string)
            break;

        printf("ERREUR: Le Theme de la rubrique ne doit contenir que des caracteres\n");    
    }

    r->Liste_internet = (char**)malloc(MAX_STRING_LENGTH*sizeof(char*));
    
    int i = 0; // NEED TO BE BACK HERE LATER
    do{
        printf("Donner le site (Laissez vide pour terminer): ");
        (r->Liste_internet)[i] = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
        fgets((r->Liste_internet)[i], MAX_STRING_LENGTH, stdin);
        i++;

    } while ((r->Liste_internet)[i-1] != "\n");
    

}

void affichage(RUBRIQUE r){
    printf("le théme du rubrique est: %s\n",r.Theme);
    printf("la date de poste du premier rubrique est: %i/%i/%i/\n",r.Date_de_poste.jour ,r.Date_de_poste.mois, r.Date_de_poste.annee);
    printf("les liste internets reliés sont: %s\n",r.Liste_internet);
}