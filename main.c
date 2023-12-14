#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <string.h>

#define MAX_STRING_LENGTH 100

void Menu_message(){
    printf("Menu message\n");
}

void Menu_rubrique(RUBRIQUE *r){

    while(1){

        printf("\n********************************************************\n");
        printf("*                                                      *\n");
        printf("*                  Theme: %s                  *\n", r->Theme);
        printf("*                                                      *\n");
        printf("********************************************************\n");

        printf("1. Ecrire un message dans la rubrique\n");
        printf("2. Voir la liste des messages dans la rubrique\n");
        printf("3. Retour vers le menu des rubriques\n");
        printf("4. Quitter\n");

        unsigned short int choix;
        printf("Donnez votre choix: "); scanf("%hu", &choix);

        while(getchar() != '\n');

        switch(choix){

            case 1:{
                MESSAGE m;
                saisir_message(&m);
                sauvegarder_message(m, *r);
                break;
            }

            case 2:{          
                    Noeud_liste_de_message *iter_messages = r->Listes_messages.tete;
                    unsigned int nombre_de_messages = 1;
                    while(iter_messages != NULL){
                        printf("%i. %s\n", nombre_de_messages, iter_messages->Valeur.tete->Valeur.Titre);
                        nombre_de_messages++;
                        iter_messages = iter_messages->Suivant;
                    }

                    printf("%i. Quitter\n", nombre_de_messages);

                    unsigned short int sous_choix;
                    printf("Donnez votre choix: "); scanf("%hu", &sous_choix);

                    while(getchar() != '\n');

                    if(sous_choix == nombre_de_messages){
                        free_utilisateurs();
                        detruire_liste_rubrique(&f.Rubriques);
                        exit(EXIT_SUCCESS);
                    }    
                    if(sous_choix > 0 && sous_choix < nombre_de_messages){
                        Noeud_liste_de_message *iter_messages = r->Listes_messages.tete;
                        for(unsigned int i = 1; i < sous_choix; i++){
                            iter_messages = iter_messages->Suivant;
                        }
                        printf("\n");
                        Noeud_message *iter_message = iter_messages->Valeur.tete;
                        while(iter_message !=NULL){
                            affichage_message(iter_message->Valeur);
                            iter_message = iter_message->Suivant;
                        }
                        Menu_message();
                    }else printf("Votre choix est invalide.\n");

                break;
            }case 3:{


                break;
            }

            case 4:{
                free_utilisateurs();
                detruire_liste_rubrique(&f.Rubriques);
                exit(EXIT_SUCCESS);
                break;
            }

            default:
                printf("Votre choix est invalide.\n");
                break;

        }
        if(choix == 3) break;
    }
}

void Menu_rubriques(){

    while(1){

        printf("\n********************************************************\n");
        printf("*                                                      *\n");
        printf("*                  Menu Des Rubriques                  *\n");
        printf("*                                                      *\n");
        printf("********************************************************\n");
    
        printf("1. Voir les rubriques\n");
        printf("2. Ajouter une rubrique\n");
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


                    Noeud_rubrique *iter_rubrique = f.Rubriques.tete;
                    unsigned int nombre_rubriques = 1;
                    while(iter_rubrique != NULL){
                        printf("%i. %s\n",nombre_rubriques ,iter_rubrique->valeur.Theme);
                        nombre_rubriques++;
                        iter_rubrique = iter_rubrique->Suivant;
                    }

                    printf("%i. Retour vers le menu précédant\n", nombre_rubriques);
                    printf("%i. Quitter\n", nombre_rubriques+1);

                    unsigned int choix;
                    printf("Donnez votre choix: "); scanf("%u", &choix);

                    while(getchar() != '\n');

                    if(choix == nombre_rubriques) break;
                    if(choix == nombre_rubriques+1){
                        detruire_liste_rubrique(&f.Rubriques);
                        free_utilisateurs();
                        exit(EXIT_SUCCESS);
                    }

                    if(choix > 0 && choix < nombre_rubriques){
                        printf("\n\n********************************************************\n");
                        Noeud_rubrique *iter_rubrique = f.Rubriques.tete;
                        for(unsigned int i = 1; i < choix; i++){
                            iter_rubrique = iter_rubrique->Suivant;
                        }
                        affichage_rubrique(iter_rubrique->valeur);
                        printf("\n");
                        Menu_rubrique(&iter_rubrique->valeur);
                    }else printf("Votre choix est invalide\n");
                }
                break;
            }
            case 2:{
                RUBRIQUE r;
                saisir_rubrique(&r);
                Menu_rubrique(&r);
                break;
            }
            case 4:{
                free_utilisateurs();
                detruire_liste_rubrique(&f.Rubriques);
                exit(EXIT_SUCCESS);
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


        Noeud_rubrique *iter_rubrique = f.Rubriques.tete;
        unsigned int nombre_rubriques = 1;
        while(iter_rubrique != NULL){
            printf("%i. %s\n",nombre_rubriques ,iter_rubrique->valeur.Theme);
            nombre_rubriques++;
            iter_rubrique = iter_rubrique->Suivant;
        }

        printf("%i. Retour vers le menu précédant\n", nombre_rubriques);
        printf("%i. Quitter\n", nombre_rubriques+1);

        unsigned int choix;
        printf("Donnez votre choix: "); scanf("%u", &choix);

        while(getchar() != '\n');

        if(choix == nombre_rubriques) break;
        if(choix == nombre_rubriques+1){
            detruire_liste_rubrique(&f.Rubriques);
            free_utilisateurs();
            exit(EXIT_SUCCESS);
        }

        if(choix > 0 && choix < nombre_rubriques){
            printf("\n\n********************************************************\n");
            Noeud_rubrique *iter_rubrique = f.Rubriques.tete;
            for(unsigned int i = 1; i < choix; i++){
                iter_rubrique = iter_rubrique->Suivant;
            }
            affichage_rubrique(iter_rubrique->valeur);
            printf("\n");
        }else printf("Votre choix est invalide\n");
    }

} 

int main(){

    charger_rubriques(&f.Rubriques);

    f.Nombre_invites = 0;

    f.Adresse_internet = strdup("www.forum.com");
    saisir_forum();

    charger_utilisateur();

    while(1){

        unsigned short int choix;
        
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

                u.Adresse_email = NULL;
                unsigned short int mot_de_passe_incorrect = 0;

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
                            mot_de_passe_incorrect = 1;
                            printf("Mot de passe incorrect.\n");
                            break;
                        }   
                    }
                }

                if(u.Adresse_email != NULL) Menu_rubriques();
                else if(!mot_de_passe_incorrect) printf("Vous n'êtes pas inscrits.\n");
        
                break; 
            }
            case 4:{
                detruire_liste_rubrique(&f.Rubriques);
                free_utilisateurs();
                exit(EXIT_SUCCESS);
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