#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rubrique.h"


#define MAX_STRING_LENGTH 100

void saisir_rubrique(RUBRIQUE* r){

        r->Nombre_messages = 0;
    
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

    r->Numero_de_sites = 0;
    r->Liste_internet = (char**) malloc(MAX_STRING_LENGTH * sizeof(char*));
    do{
        printf("Le nom du site(vide pour quitter): ");
        unsigned int i = r->Numero_de_sites;
        (r->Liste_internet)[i] = (char*) malloc(MAX_STRING_LENGTH * sizeof(char));
        fgets((r->Liste_internet)[i], MAX_STRING_LENGTH, stdin);
        // (m->Textes)[i][strlen((m->Textes)[i])-1] = '\0';
        (r->Numero_de_sites)++;

    } while(strcmp((r->Liste_internet)[(r->Numero_de_sites) - 1], "\n") != 0);
    

}
void affichage_rubrique(RUBRIQUE r){
    printf("Le theme du rubrique est: %s\n",r.Theme);
    printf("La date de poste du premier rubrique est: %i/%i/%i\n",r.Date_de_poste.jour ,r.Date_de_poste.mois, r.Date_de_poste.annee);
    
    for(int i=0;i<r.Numero_de_sites-1;i++){
        printf("liste %i: %s\n",i+1,(r.Liste_internet)[i]);

    }
   
}

void sauvegarder_rubrique(MESSAGES m ,RUBRIQUE r){
        const char *DossierRubrique = r.Theme;

    if (chdir("../Rubriques") != 0) {
        fprintf(stderr, "Erreur lors du changement vers le répertoire rubriques.\n");
        return;
    }

    if (access(DossierRubrique, F_OK) == -1) {
        if (mkdir(DossierRubrique) != 0) {
            fprintf(stderr, "Erreur lors de la création du répertoire %s\n", DossierRubrique);
            return;
        }
    }

    if (chdir(DossierRubrique) != 0) {
        fprintf(stderr, "Erreur lors du changement vers le répertoire %s.\n", r.Theme);
        return;
    }

    (m.Titre)[strlen(m.Titre) - 1] = '\0';

}

    char Nom_fichier_rubrique[100];
    snprintf(Nom_fichier_rubrique, sizeof(Nom_fichier_rubrique), "%s.txt", r.Theme);

    FILE *Fichier_rubrique = fopen(Nom_fichier_rubrique, "a");

    if(Fichier_rubrique == NULL){
        perror("Erreur de l'ouverture du fichier rubrique.\n");
        exit(0);
    }
    fprintf(Fichier_rubrique,"Théme: %s", r.Theme);
    fprintf(Fichier_rubrique,"Date de poste: %i/%i/%i\n",r.date_de_poste.jour,r.date_de_poste.mois,r.date_de_poste.annee);
    fprintf(Fichier_rubrique,"Numero d'inscription: %i\n",r.Numero_inscription);
    fprintf(Fichier_rubrique,"Nombre de messages: %i\n",r.Nombre_message);
    fpintf(Fichier_rubrique,"Numero de sites: %i\n",r.Numero_de_sites);
    fprintf(Fichier_rubrique,"listes internets: %s",(r.Liste_internet)[0]);

    fclose(Fichier_rubrique);

