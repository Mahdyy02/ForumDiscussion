#include <stdlib.h>
#include <stdio.h>
#include "utilisateur.h"
#include "date.h"
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 100

int frequency(char* s, int size, char c){

    int freq = 0;
    
    for(int i = 0; i < size; i++){
        if(s[i] == c)
            freq++;
    }

    return freq;

}

int first_index(char* s, int size, char c){
    
    for(int i = 0; i < size; i++){
        if(s[i] == c)
            return i;

        return -1;    
    }
}

void inscription(UTILISATEUR* u){


    printf("********************************************************\n");
    printf("*                                                      *\n");
    printf("*               Interface d'inscription                *\n");
    printf("*                                                      *\n");
    printf("********************************************************\n");

    while(1){
        printf("Nom: ");
        u->Nom = malloc(MAX_STRING_LENGTH*sizeof(char));
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
        u->Prenom = malloc(MAX_STRING_LENGTH*sizeof(char));
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
    u->Adresse = malloc(MAX_STRING_LENGTH*sizeof(char));
    fgets(u->Adresse, MAX_STRING_LENGTH, stdin);
    (u->Adresse)[strlen(u->Adresse) - 1] = '\0';

    printf("Saisie de la date de naissance: \n");
    Saisir_date(&(u->Date_de_naissance));

    while(getchar() != '\n');

    printf("Numero de telephone: ");
    scanf("%u", &(u->Numero_telephone));

    while(getchar() != '\n');

    while(1){

        printf("Adresse_email: ");
        u->Adresse_email = malloc(MAX_STRING_LENGTH*sizeof(char));
        fgets(u->Adresse_email, MAX_STRING_LENGTH, stdin);
        (u->Adresse_email)[strlen(u->Adresse_email) - 1] = '\0';

        if(frequency(u->Adresse_email, strlen(u->Adresse_email), '@') == 1 && frequency(u->Adresse_email, strlen(u->Adresse_email), '.') >= 1){    
            
            int freq_point = 0;
            for(int j = first_index(u->Adresse, strlen(u->Adresse), *strchr(u->Adresse_email, '@')) + 1; j < strlen(u->Adresse_email); j++){
                if((u->Adresse_email)[j] == '.')
                    freq_point++;
            }

            if(freq_point == 1)
                break;  
        }

        printf("Le format d'un email est user@domaine.xyz\n");    

    }

    while(1){

        printf("Password: ");
        u->Password = malloc(MAX_STRING_LENGTH*sizeof(char));
        fgets(u->Password, MAX_STRING_LENGTH, stdin);
        (u->Password)[strlen(u->Password) - 1] = '\0';

        int upper = 0; int symbol = 0;
        for(int i = 0; i < strlen(u->Password); i++){
            if(ispunct((u->Password)[i]) || isdigit((u->Password)[i])){
                symbol++;
            }else if(isupper((u->Password)[i])){
                upper++;
            }
        }

        if(strlen(u->Password) > 8 && upper >= 1 && symbol >= 2)
            break;

        printf("Le mot de passe doit être de longueur supèrieur à 8, contenir un chiffre majuscule et deux symbole.\n");    

    }

    printf("Choisissez votre pseudo: ");
    u->Pseudo = malloc(MAX_STRING_LENGTH*sizeof(char));
    fgets(u->Pseudo, MAX_STRING_LENGTH, stdin);
    (u->Pseudo)[strlen(u->Pseudo) - 1] = '\0'; 

    printf("Félicitations vous êtes inscrits avec succés.\n");

    // A enlever plus tard

    free(u->Nom);
    free(u->Prenom);
    free(u->Adresse);
    free(u->Adresse_email);
    free(u->Password);
    free(u->Pseudo);
    free(u);
}


void affichage(UTILISATEUR u){
    printf("le nom est: %s\n", u.Nom);
    printf("le prénom est: %s\n",u.Prenom);
    printf("la date de naissance est : %s\n",u.jour);
    printf("le numéro de téléphone ")

    














}