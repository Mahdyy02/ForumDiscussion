#include <stdlib.h>
#include <stdio.h>
#include "utilisateur.h"
#include "date.h"
#include "forum.h"
#include "global.h"
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 100
#define MAX_LINE_LENGTH 256

int frequency(char* s, int size, char c){

    int freq = 0;
    
    for(int i = 0; i < size; i++){
        if(s[i] == c)
            freq++;
    }

    return freq;

}

int first_index(char* s, int size, char c){
    
    for(unsigned int i = 0; i < (unsigned int)size; i++){
        if(s[i] == c)
            return i;

        if(i == (strlen(s) - 1) && s[i] != c)
            return -1;       
    }
}

void inscription(UTILISATEUR* u){ // NEED TO BE BACK HERE LATER


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
        for(unsigned int i = 0; i < strlen(u->Nom) - 1;i++){
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
        for(unsigned int i = 0; i < strlen(u->Prenom) - 1;i++){
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

    while(1){

        printf("Adresse_email: ");
        u->Adresse_email = malloc(MAX_STRING_LENGTH);
        fgets(u->Adresse_email, MAX_STRING_LENGTH, stdin);
        (u->Adresse_email)[strlen(u->Adresse_email) - 1] = '\0';

        if(frequency(u->Adresse_email, strlen(u->Adresse_email), '@') == 1 && frequency(u->Adresse_email, strlen(u->Adresse_email), '.') >= 1){   

            int freq_point = 0;
            for(unsigned int j = first_index(u->Adresse_email, strlen(u->Adresse_email), '@') + 1; j < strlen(u->Adresse_email); j++){
                if((u->Adresse_email)[j] == '.')
                    freq_point++;
            }

            if(freq_point <= 2)
                break;  
        }

        printf("Le format d'un email est user@domaine.abc.xyz\n");    

    }

    while(1){

        printf("Password: ");
        u->Password = malloc(MAX_STRING_LENGTH);
        fgets(u->Password, MAX_STRING_LENGTH, stdin);
        (u->Password)[strlen(u->Password) - 1] = '\0';

        int upper = 0; int symbol = 0;
        for(unsigned int i = 0; i < strlen(u->Password); i++){
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
    u->Pseudo = malloc(MAX_STRING_LENGTH);
    fgets(u->Pseudo, MAX_STRING_LENGTH, stdin);
    (u->Pseudo)[strlen(u->Pseudo) - 1] = '\0'; 

    printf("Félicitations vous êtes inscrits avec succés.\n");

}


void affichage(UTILISATEUR u){

    printf("\n\n\n\n\n");
    printf("********************************************************\n");
    printf("*                                                      *\n");
    printf("*                 Profil de %s                  *\n", u.Pseudo);
    printf("*                                                      *\n");
    printf("********************************************************\n");

    printf("le nom est: %s\n", u.Nom);
    printf("le prénom est: %s\n",u.Prenom);
    printf("l'adresse est: %s\n",u.Adresse);
    printf("la date de naissance est: %i/%i/%i\n",u.Date_de_naissance.jour,u.Date_de_naissance.mois,u.Date_de_naissance.annee);
    printf("le numéro de téléphone est: %u\n",u.Numero_telephone);
    printf("l'adresse e_amil est: %s\n",u.Adresse_email);
}


void sauvegarder_utilisateur(UTILISATEUR u){

    FILE *Fichier_utilisateurs = fopen("utilisateurs.txt", "a");

    if (Fichier_utilisateurs == NULL) {
        perror("Erreur d'ouverture du fichier utilisateur.\n");
        exit(0);
    }

    u.Administrateur = 0;
    u.Numero_inscription = f.Nombre_utilisateurs;

    fprintf(Fichier_utilisateurs ,"%s;%s;%s;%i/%i/%i;%i;%i;%s;%s;%s;%i\n", u.Nom, u.Prenom, u.Adresse, u.Date_de_naissance.jour, u.Date_de_naissance.mois, u.Date_de_naissance.annee, u.Numero_telephone, u.Numero_inscription, u.Adresse_email, u.Password, u.Pseudo, u.Administrateur);

    fclose(Fichier_utilisateurs);
}

void charger_utilisateur(){

    FILE *Fichier_utilisateurs = fopen("utilisateurs.txt", "r");

    char line[MAX_LINE_LENGTH];

    if (Fichier_utilisateurs == NULL) {
        perror("Erreur de l'ouverture du fichier message.\n");
        exit(1);
    }


    while (fgets(line, sizeof(line), Fichier_utilisateurs) != NULL) {

        UTILISATEUR u;
            
        int indice_attribut = 0; // pour connaitre les differents attributs
        char *jeton = strtok(line, ";");

        while (jeton != NULL) {

            switch (indice_attribut){

                case 0:
                    u.Nom = jeton;
                    break;
                case 1:
                    u.Prenom = jeton;
                    break;
                case 2:
                    u.Adresse = jeton;
                    break;
                case 4:
                    u.Date_de_naissance = charger_date(jeton);
                    break;
                case 3:
                    u.Numero_telephone = (unsigned int)jeton;
                    break;    
                case 5:
                    u.Numero_inscription = (unsigned int)jeton;
                    break;
                case 6:
                    u.Adresse_email = jeton;
                    break;
                case 7:
                    u.Password = jeton;
                    break;
                case 8:
                    u.Pseudo = jeton;
                    break;
                case 9:
                    u.Administrateur = (int)jeton;
                    break;   

            }

            indice_attribut++;
            jeton = strtok(NULL, ";");
        }

        (f.Utilisateurs)[u.Numero_inscription] = u; 

    }
    
    fclose(Fichier_utilisateurs);
}