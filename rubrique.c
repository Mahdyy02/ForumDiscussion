#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rubrique.h"
#include <dirent.h>
#include "global.h"

#define MAX_STRING_LENGTH 100
#define MAX_LINE_LENGTH 256

void saisir_rubrique(RUBRIQUE* r){
    
        while(1){
        printf("Theme de la rubrique: ");
        r->Theme = malloc(MAX_STRING_LENGTH*sizeof(char));
        fgets(r->Theme, MAX_STRING_LENGTH, stdin);
        (r->Theme)[strlen(r->Theme) - 1] = '\0';

        int valid_string = 1;
        for(unsigned int i = 0; i < strlen(r->Theme) - 1;i++){
            if(!isupper(r->Theme[i]) && (!islower(r->Theme[i]) || isdigit(r->Theme[i]))){
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
    (r->Numero_de_sites)--;

}

void affichage_rubrique(RUBRIQUE r){

    printf("Le theme du rubrique est: %s\n",r.Theme);
    printf("La date de poste du rubrique est: %i/%i/%i\n",r.Date_de_poste.jour ,r.Date_de_poste.mois, r.Date_de_poste.annee);
    
    for(unsigned int i=0; i < r.Numero_de_sites ; i++){
        printf("liste %i: %s\n",i+1,(r.Liste_internet)[i]);
    }
   
}

void charger_rubriques() {


    char *cheminDossier = "../Rubriques";

    DIR *dossier = opendir(cheminDossier);
    struct dirent *entree;

    if (dossier == NULL) {
        perror("Impossible d'ouvrir le répertoire");
        exit(EXIT_FAILURE);
    }

    f.Nombres_Rubriques = 0;

    while ((entree = readdir(dossier)) != NULL) {
        if (entree->d_type == DT_DIR) { 

            if (strcmp(entree->d_name, ".") != 0 && strcmp(entree->d_name, "..") != 0) {
                char cheminSousDossier[MAX_STRING_LENGTH];

                (f.Nombres_Rubriques)++;
                Rubriques = (RUBRIQUE*)realloc(Rubriques, f.Nombres_Rubriques);
                Rubriques[f.Nombres_Rubriques-1].Theme = strdup(entree->d_name);

                sprintf(cheminSousDossier, "%s/%s", cheminDossier, entree->d_name);

                DIR *sousDossier = opendir(cheminSousDossier);
                int nombreFichiersTxt = 0;

                if (sousDossier != NULL) {
                    struct dirent *entreeSousDossier;
                    while ((entreeSousDossier = readdir(sousDossier)) != NULL) {
                        if (entreeSousDossier->d_type == DT_REG && strstr(entreeSousDossier->d_name, ".txt") != NULL) {
                            nombreFichiersTxt++;
                        }
                    }
                    closedir(sousDossier);

                    Rubriques[f.Nombres_Rubriques-1].Messages = (MESSAGES**) malloc((nombreFichiersTxt-1)*sizeof(MESSAGES*));
                    for(int i = 0; i < nombreFichiersTxt-1; i++){
                        Rubriques[f.Nombres_Rubriques-1].Messages[i] = (MESSAGES*) malloc(1000*sizeof(MESSAGES));
                    }

                } else {
                    perror("Impossible d'ouvrir le sous-répertoire");
                }
            }
        }
    }

    closedir(dossier);
}

void charger_rubrique(RUBRIQUE* r) {

    r->Numero_messages = 0;

    char *rep_dossier;
    rep_dossier = strdup(r->Theme);

    rep_dossier = (char* )realloc(rep_dossier, (strlen(rep_dossier)+strlen("../Rubriques/"))*sizeof(char));

    snprintf(rep_dossier, MAX_LINE_LENGTH, "../Rubriques/%s", r->Theme);


    DIR *dir = opendir(rep_dossier);

    if (dir == NULL) {
        printf("Erreur d'ouverture de la répertoire %s.\n", rep_dossier);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char rep_fichier[MAX_LINE_LENGTH];
            snprintf(rep_fichier, sizeof(rep_fichier), "%s/%s", rep_dossier, entry->d_name);

            if (entry->d_type == DT_REG) {
                if(strchr(rep_fichier, '_') == NULL){

                    FILE *Fichier_rubrique = fopen(rep_fichier, "r");

                    if (Fichier_rubrique == NULL) {
                        printf("Erreur de l'ouverture du fichier %s.\n", rep_fichier);
                        exit(1);
                    }

                    char nom_de_chaine_a_lire[MAX_LINE_LENGTH];
                    char chaine_a_lire[MAX_STRING_LENGTH];
                    char line[MAX_LINE_LENGTH];
                    int index_of_start;
                    int size;
                    int indice_de_liste = 0;

                    while (fgets(line, sizeof(line), Fichier_rubrique) != NULL) {


                        if(line[1] == '=' || line[0] == '\0'){
                            continue;    
                        }

                        size = 0;
                        index_of_start = first_index(line, strlen(line), ':');    

                        for(int i = 0; i < index_of_start; i++){
                            nom_de_chaine_a_lire[i] = line[i];
                        }

                        for(unsigned int i = index_of_start + 2; i < strlen(line); i++){
                            chaine_a_lire[size++] = line[i];
                        }

                        nom_de_chaine_a_lire[index_of_start] = '\0';
                        chaine_a_lire[size-1] = '\0';


                        if(strcmp(nom_de_chaine_a_lire, "Numero d'inscription") == 0){
                            r->Numero_inscription = atoi(chaine_a_lire);
                        }else if(strcmp(nom_de_chaine_a_lire, "Theme") == 0){
                            r->Theme = strdup(chaine_a_lire);
                        }else if(strcmp(nom_de_chaine_a_lire ,"Date de poste") == 0){
                            r->Date_de_poste = charger_date(chaine_a_lire);
                        }else if(strcmp(nom_de_chaine_a_lire, "Numero de sites") == 0){
                            r->Numero_de_sites = atoi(chaine_a_lire);
                            r->Liste_internet = (char**) malloc((r->Numero_de_sites)*sizeof(char*));
                        }else{
                            r->Liste_internet[indice_de_liste++] = strdup(chaine_a_lire);
                        }

                    }
                    fclose(Fichier_rubrique);

                }else{ 
                    r->Messages[r->Numero_messages++] = charger_message(rep_fichier);
                }    
            }
        }
    }

    closedir(dir);
}

void sauvegarder_rubrique(RUBRIQUE r){
    
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

    char Nom_fichier_rubrique[100];
    snprintf(Nom_fichier_rubrique, sizeof(Nom_fichier_rubrique), "%s.txt", r.Theme);

    FILE *Fichier_rubrique = fopen(Nom_fichier_rubrique, "a");

    if(Fichier_rubrique == NULL){
        perror("Erreur de l'ouverture du fichier rubrique.\n");
        exit(0);
    }

    fprintf(Fichier_rubrique,"Theme: %s\n", r.Theme);
    fprintf(Fichier_rubrique,"Date de poste: %i/%i/%i\n", r.Date_de_poste.jour, r.Date_de_poste.mois, r.Date_de_poste.annee);
    fprintf(Fichier_rubrique,"Numero d'inscription: %i\n", r.Numero_inscription);
    fprintf(Fichier_rubrique,"Numero de sites: %i\n", r.Numero_de_sites);
    for(unsigned int i=0; i< r.Numero_de_sites; i++){
        fprintf(Fichier_rubrique,"Listes internet %i: %s", i+1, r.Liste_internet[i]);
    }


    if (chdir("..") != 0) {
        perror("Erreur du retour vers le dossier principale.\n");
        return;
    }

    fclose(Fichier_rubrique);
}