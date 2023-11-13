#ifndef UTILISATEUR_H_INCLUDED
#define UTILISATEUR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
    char* Nom;
    char* Prenom;
    char* Adresse;
    char* Date_de_naissance;
    unsigned int Numero_telephone;
    unsigned int Numero_inscription;
    char* Adresse_email;
    char* Password;
    char* Pseudo;
    unsigned short int Administrateur;

}UTILISATEUR;

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




#endif