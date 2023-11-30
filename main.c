#include <stdio.h>
#include <stdlib.h>
#include "rubrique.h"
#include "utilisateur.h"
#include "forum.h"
#include "global.h"
#include <string.h>

void Menu(){

    while(1){

        int c;

        printf("1. Afficher le compte de l'utilisateur\n");
        printf("2. Saisir rebriques\n");
        printf("3. Afficher les rebriques\n");
        printf("4. Quitter\n");
        printf("Choix: "); scanf("%i", &c);

        while(getchar() != '\n');

        switch (c)
        {
        case 1:
            if(u.Nom == NULL){
                printf("Vous êtes invité");
            }else{
                affichage(u);
            }
            break;
        
        case 2:
            saisir_rubrique(&r);
            break;

        case 3:
            if(r.Theme == NULL){
                printf("Aucune rebrique trouvée");
            }else{
                affichage_rubrique(r);
            }
            break;

        case 4:
            exit(0);
            break;        

        default:
            break;
        }
    }

}


int main(){

    r.Messages = (MESSAGES**) malloc(sizeof(MESSAGES*) * 1000);
    for(int i = 0; i < 100; i++){
        r.Messages[i] = (MESSAGES*) malloc(sizeof(MESSAGES) * 1000);
    }

    r.Theme = strdup("Peinture");

    charger_rubrique(&r);

    for(int i = 0;  i < r.Numero_messages; i++){
        for (int j = 0; r.Messages[i][j].Titre != NULL ; j++){
            affichage_message(r.Messages[i][j]);
            printf("=============================================\n");
        }
        
    }

    for(int i = 0;  i < 1000; i++){
            free(r.Messages[i]);
    }
    free(r.Messages);
        

    // int c;
    // char pseudo_invite[100];
    // strcpy(f.Adresse_internet, "forum-de-discussion.com");

    // saisir_forum();

    // while(1){

    //     printf("1. Register un nouveau compte\n");
    //     printf("2. Entrer en tant que invité\n");
    //     printf("3. Quitter\n");
    //     printf("Choix: "); scanf("%i", &c);

    //     while(getchar() != '\n');

    //     switch(c){
    //     case 1:
    //         inscription(&u);
    //         if(&u != NULL){
    //             (f.Nombre_utilisateurs)++;
    //             sauvegarder_utilisateur(u);
    //             Menu();
    //         }
    //         break;

    //     case 2:
    //         printf("Donner votre pseudo en tant que invité: ");
    //         scanf("%s", pseudo_invite);
    //         (f.Nombre_invites)++;
    //         Menu();
    //         break;    
        
    //     case 3:
    //         exit(0);
    //         break;

    //     default:
    //         break;
    //     }

    // }

    return 0;
}