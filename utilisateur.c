#include <stdlib.h>
#include <stdio.h>
#include "utilisateur.h"


void inscription(UTILISATEUR* u){
    printf("Nom: ");
    u->Nom = (char*) malloc(sizeof(char));
    scanf("%s", &(u->Nom));
    printf("Prenom: ");
    u->Prenom = (char*) malloc(sizeof(char));
    scanf("%s",&(u->Prenom));
    printf("Adresse: ");
    u->Adresse = (char*) malloc(sizeof(char));
    scanf("%s",&(u->Adresse));
    printf("Date de naissance: ");
    u->Date_de_naissance = (char*) malloc(sizeof(char));
    scanf("%s",&(u->Date_de_naissance));
    printf("Numero de telephone: ");
    scanf("%i", &(u->Numero_telephone));
    printf("Adresse_email: ");
    scanf("%i",&(u->Adresse_email));
    printf("Password:");
        
}