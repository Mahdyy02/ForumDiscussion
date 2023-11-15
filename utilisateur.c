#include <stdlib.h>
#include <stdio.h>
#include "utilisateur.h"
#include "date.h"
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 100

void inscription(UTILISATEUR* u){


    printf("********************************************************\n");
    printf("*                                                      *\n");
    printf("*               Interface d'inscription                *\n");
    printf("*                                                      *\n");
    printf("********************************************************\n");

    while(1){
        printf("Nom: ");
        u->Nom = malloc(MAX_STRING_LENGTH);
        fgets(u->Nom, MAX_STRING_LENGTH, stdin);
        (u->Nom)[strlen(u->Nom) - 1] = '\0';

        int valid_string = 1;
        for(int i = 0; i < strlen(u->Nom) - 1;i++){
            if(!isupper(u->Nom[i]) && !islower(u->Nom[i]) || isdigit(u->Nom[i])){
                valid_string = 0;
                break;
            }
        }
        if(valid_string)
            break;

        printf("ERREUR: Le nom ne doit contenir que des caracteres\n");    
    }

    while(1){
        printf("Prénom: ");
        u->Prenom = malloc(MAX_STRING_LENGTH);
        fgets(u->Prenom, MAX_STRING_LENGTH, stdin);
        (u->Prenom)[strlen(u->Prenom) - 1] = '\0';

        int valid_string = 1;
        for(int i = 0; i < strlen(u->Prenom) - 1;i++){
            if(!isupper(u->Prenom[i]) && !islower(u->Prenom[i]) || isdigit(u->Prenom[i])){
                valid_string = 0;
                break;
            }
        }
        if(valid_string)
            break;

        printf("ERREUR: Le prenom ne doit contenir que des caracteres\n");    
    }

    printf("Adresse: ");
    u->Adresse = malloc(MAX_STRING_LENGTH);
    fgets(u->Adresse, MAX_STRING_LENGTH, stdin);
    (u->Adresse)[strlen(u->Adresse) - 1] = '\0';

    printf("Saisie de la date de naissance: \n");
    Saisir_date(&(u->Date_de_naissance));

    while(getchar() != '\n');

    printf("Numero de telephone: ");
    scanf("%u", &(u->Numero_telephone));

    while(getchar() != '\n');

    printf("Adresse_email: ");
    u->Adresse_email = malloc(MAX_STRING_LENGTH);
    fgets(u->Adresse_email, MAX_STRING_LENGTH, stdin);
    (u->Adresse_email)[strlen(u->Adresse_email) - 1] = '\0';

    printf("Password: ");
    u->Password = malloc(MAX_STRING_LENGTH);
    fgets(u->Password, MAX_STRING_LENGTH, stdin);
    (u->Password)[strlen(u->Password) - 1] = '\0';

    printf("Choisissez votre pseudo: ");
    u->Pseudo = malloc(MAX_STRING_LENGTH);
    fgets(u->Pseudo, MAX_STRING_LENGTH, stdin);
    (u->Pseudo)[strlen(u->Pseudo) - 1] = '\0'; 

    printf("Félicitations vous êtes inscrits avec succés.\n");

    free(u->Nom);
    free(u->Prenom);
    free(u->Adresse);
    free(u->Adresse_email);
    free(u->Password);
    free(u->Pseudo);
    free(u);
}