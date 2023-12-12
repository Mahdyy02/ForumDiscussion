#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <string.h>

#define MAX_STRING_LENGTH 100

void Menu_rubrique(RUBRIQUE r){

    printf("\n********************************************************\n");
    printf("*                                                      *\n");
    printf("*                  Theme: %s                  *\n", r.Theme);
    printf("*                                                      *\n");
    printf("********************************************************\n");

    while(1){

        printf("1. Ecrire un message dans la rubrique\n");
        printf("2. Voir la liste des messages dans la rubrique\n");
        printf("3. Retour vers le menu des rubriques\n");
        printf("4. Quitter\n");

        unsigned short int choix;
        printf("Donnez votre choix: "); scanf("%hu", &choix);

        while(getchar() != '\n');

        switch(choix){

            case 1:{

                RUBRIQUE current_r;

                charger_rubriques(&Rubriques);
                for(unsigned int i = 0; i < f.Nombres_Rubriques; i++){
                    charger_rubrique(Rubriques+i);
                }

                for(unsigned int i = 0; i < f.Nombres_Rubriques; i++){
                    if(Rubriques[i].Theme  == r.Theme){
                        current_r = Rubriques[i];
                        break;
                    }    
                }

                MESSAGES m;
                saisir_message(&m);
                sauvegarder_message(m, current_r);
                break;

                free_rubriques(Rubriques, f.Nombres_Rubriques);
            }

            case 2:{

                    RUBRIQUE current_r;

                    charger_rubriques(&Rubriques);
                    for(unsigned int i = 0; i < f.Nombres_Rubriques; i++){
                        charger_rubrique(Rubriques+i);
                    }

                    for(unsigned int i = 0; i < f.Nombres_Rubriques; i++){
                        if(Rubriques[i].Theme  == r.Theme){
                            current_r = Rubriques[i];
                            break;
                        }    
                    }
                    
                    for(unsigned int i = 0; i < r.Numero_messages; i++)
                        printf("%i. %s\n", i+1, r.Messages[i][0].Titre);

                    printf("%i. Quitter\n", r.Numero_messages+1);

                     unsigned short int sous_choix;
                    printf("Donnez votre choix: "); scanf("%hu", &sous_choix);

                    while(getchar() != '\n');

                    if(sous_choix == r.Numero_messages+1){
                        exit(0);
                        free_utilisateurs();
                    }    
                    if(sous_choix > 0 && sous_choix <=r.Numero_messages){
                        for(unsigned int i = 0; r.Messages[sous_choix-1][i].Titre != NULL; i++){
                            affichage_message(r.Messages[sous_choix-1][i]);
                            printf("\n\n********************************************************\n");
                        }
                    }  

                    free_rubriques(Rubriques, f.Nombres_Rubriques);  

                break;
            }

            case 4:{
                free_utilisateurs();
                exit(0);
                break;
            }

            default:
                printf("Votre choix est invalide\n");
                break;

        }

        if(choix == 3) break;

    }
    


}

void Menu_rubriques(){

    printf("\n********************************************************\n");
    printf("*                                                      *\n");
    printf("*                  Menu Des Rubriques                  *\n");
    printf("*                                                      *\n");
    printf("********************************************************\n");

    while(1){
    
        printf("1. Voir les rubriques\n");
        printf("2. Ajouter un rubrique\n");
        printf("3. Se deconnecter\n");
        printf("4. Quitter\n");

        unsigned short int choix;
        printf("Donnez votre choix: "); scanf("%hu", &choix);

        while(getchar() != '\n');

        switch(choix){

            case 1:{
                    while(1){
    
                    printf("\n********************************************************\n");
                    printf("*                                                      *\n");
                    printf("*                  Page Des Rubriques                  *\n");
                    printf("*                                                      *\n");
                    printf("********************************************************\n");

                    charger_rubriques(&Rubriques);
                    for(unsigned int i = 0; i < f.Nombres_Rubriques; i++){
                        charger_rubrique(Rubriques+i);
                    }

                    for(unsigned int i = 0; i < f.Nombres_Rubriques; i++){
                        printf("%i. %s\n", i+1, Rubriques[i].Theme);
                    }

                    printf("%i. Retour vers le menu précédant\n", f.Nombres_Rubriques+1);
                    printf("%i. Quitter\n", f.Nombres_Rubriques+2);

                    unsigned int choix;
                    printf("Donnez votre choix: "); scanf("%u", &choix);

                    while(getchar() != '\n');

                    if(choix == f.Nombres_Rubriques+1) break;
                    if(choix == f.Nombres_Rubriques+2) exit(0);

                    if(choix > 0 && choix <= f.Nombres_Rubriques){
                        printf("\n\n********************************************************\n"); 
                        affichage_rubrique(Rubriques[choix-1]);
                        printf("\n");
                        Menu_rubrique(Rubriques[choix-1]);
                        free_rubriques(Rubriques, f.Nombres_Rubriques);
                    }else printf("Votre choix est invalide\n");
                }
                break;
            }
            case 2:{
                RUBRIQUE r;
                saisir_rubrique(&r);
                break;
            }
            case 4:{
                free_utilisateurs();
                exit(0);
                break;
            }
            default:
                printf("Votre choix est invalide\n");
                break;
        }

        if(choix == 3) break;
    
    }
}

void Menu_invite(){

    while(1){
    
        printf("\n********************************************************\n");
        printf("*                                                      *\n");
        printf("*                  Page Des Rubriques                  *\n");
        printf("*                                                      *\n");
        printf("********************************************************\n");

        charger_rubriques(&Rubriques);
        for(unsigned int i = 0; i < f.Nombres_Rubriques; i++){
            charger_rubrique(Rubriques+i);
        }

        for(unsigned int i = 0; i < f.Nombres_Rubriques; i++){
            printf("%i. %s\n", i+1, Rubriques[i].Theme);
        }

        printf("%i. Retour vers le menu précédant\n", f.Nombres_Rubriques+1);
        printf("%i. Quitter\n", f.Nombres_Rubriques+2);

        unsigned int choix;
        printf("Donnez votre choix: "); scanf("%u", &choix);

        while(getchar() != '\n');

        if(choix == f.Nombres_Rubriques+1) break;
        if(choix == f.Nombres_Rubriques+2){
            exit(0);
            free_utilisateurs();
        }

        if(choix > 0 && choix <= f.Nombres_Rubriques){ 
            printf("\n\n********************************************************\n");
            affichage_rubrique(Rubriques[choix-1]);
            printf("\n");
            free_rubriques(Rubriques, f.Nombres_Rubriques);
        }else printf("Votre choix est invalide\n");
    }

} 

int main(){

    f.Nombre_invites = 0;

    f.Adresse_internet = strdup("www.forum.com");
    saisir_forum();

    charger_utilisateur();

    while(1){

        unsigned short int choix = -1;
        UTILISATEUR u;
        
        printf("********************************************************\n");
        printf("*                                                      *\n");
        printf("*                    Page d'accueil                    *\n");
        printf("*                                                      *\n");
        printf("********************************************************\n");

        printf("1. S'inscrire en tant que invité\n");
        printf("2. S'inscrire en tant que utilisateur\n");
        printf("3. Se connecter\n");
        printf("4. Quitter\n");
        printf("Donnez le choix: "); scanf("%hu", &choix);

        while(getchar() != '\n');

        switch(choix){
                
            case 1:{
                char pseudo_name[MAX_STRING_LENGTH];
                printf("Donnez votre pseudo: ");
                fgets(pseudo_name, MAX_STRING_LENGTH, stdin);
                pseudo_name[strcspn(pseudo_name, "\n")] = '\0';
                (f.Nombre_invites)++;
                Menu_invite();
                break;
            }
            case 2:{
                inscription(&u);
                Menu_rubriques();
                break; 
            }
            case 3:{
                char adresse_email[MAX_STRING_LENGTH];
                printf("Donnez votre adresse mail: ");
                fgets(adresse_email, MAX_STRING_LENGTH, stdin);
                adresse_email[strcspn(adresse_email, "\n")] = '\0';
                char password[MAX_STRING_LENGTH];
                printf("Donnez votre mot de passe: ");
                fgets(password, MAX_STRING_LENGTH, stdin);
                password[strcspn(password, "\n")] = '\0';

                for(unsigned int i = 0; i < f.Nombre_utilisateurs; i++){
                    if(strcmp(f.Utilisateurs[i].Adresse_email, adresse_email) == 0){
                        if(strcmp(f.Utilisateurs[i].Password, password) == 0){
                            u = f.Utilisateurs[i];
                            break;
                        }else{
                            printf("Mot de passe incorrect.\n");
                            break;
                        }   
                    }
                }
                    
                if(strcmp(f.Utilisateurs[f.Nombre_utilisateurs - 1].Adresse_email, adresse_email) != 0){
                    printf("Vous n'êtes pas inscrits.\n");
                    break;
                }

                if(u.Adresse_email != NULL){
                    Menu_rubriques();
                }

                break; 
            }
            case 4:{
                free_utilisateurs();
                exit(0);
                break;          
            }
            default:{
                printf("Votre choix est invalide.\n");
                break;
            }

        }

    }
    
    return 0;
}