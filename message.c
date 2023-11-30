#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubrique.h"
#include "forum.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_STRING_LENGTH 100
#define MAX_LINE_LENGTH 256

void saisir_message(MESSAGES* m){
    printf("Le titre de message est: ");
    m->Titre = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));
    fgets(m->Titre, MAX_STRING_LENGTH, stdin);

    m->Numero_de_messages = 0;
    m->Textes = (char**) malloc(MAX_STRING_LENGTH * sizeof(char*));
    do{
        printf("Le contenu de message(vide pour quitter): ");
        unsigned int i = m->Numero_de_messages;
        (m->Textes)[i] = (char*) malloc(MAX_STRING_LENGTH * sizeof(char));
        fgets((m->Textes)[i], MAX_STRING_LENGTH, stdin);
        // (m->Textes)[i][strlen((m->Textes)[i])-1] = '\0';
        (m->Numero_de_messages)++;

    } while(strcmp((m->Textes)[(m->Numero_de_messages) - 1], "\n") != 0);

    (m->Numero_de_messages)--;
    
}

void affichage_message(MESSAGES m){

    for(unsigned int i = 0; i < m.Numero_de_messages; i++){

        if(i == 0){
            printf("Le titre de message est: %s\n", m.Titre);
            printf("premier message: \n");
            printf("%s\n", m.Textes[i]);
        }else{
            printf("Reply %i: \n", i);
            printf("%s\n", m.Textes[i]);
        }
    }

    printf("la date de poste est: %i/%i/%i\n", m.Date_de_poste.jour, m.Date_de_poste.mois, m.Date_de_poste.annee);
}

void sauvegarder_message(MESSAGES m, RUBRIQUE r){

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

    char Nom_fichier_message[100];
    snprintf(Nom_fichier_message, sizeof(Nom_fichier_message), "%s_%s.txt", r.Theme, m.Titre);

    FILE *Fichier_messages = fopen(Nom_fichier_message, "a");

    if(Fichier_messages == NULL){
        perror("Erreur de l'ouverture du fichier message.\n");
        exit(0);
    }

    fprintf(Fichier_messages, "Numero d'inscription: %i\n", m.Numero_incription);
    fprintf(Fichier_messages, "Titre: %s\n", m.Titre);
    fprintf(Fichier_messages, "Date de poste: %i/%i/%i\n", m.Date_de_poste.jour, m.Date_de_poste.mois, m.Date_de_poste.annee);
    fprintf(Fichier_messages, "Nombre de messages: %i\n", m.Numero_de_messages);
    fprintf(Fichier_messages, "Messages: %s", (m.Textes)[0]);

    for(unsigned int i = 1; i < m.Numero_de_messages; i++){
        fprintf(Fichier_messages, "Reply %i: %s", i, (m.Textes)[i]);
    }

    fprintf(Fichier_messages, "========================================================\n");

    if (chdir("..") != 0) {
        perror("Erreur du retour vers le dossier principale.\n");
        return;
    }

    fclose(Fichier_messages);
}

MESSAGES* charger_message(char* rep_message){

    FILE *Fichier_messages = fopen(rep_message, "r");

    if (Fichier_messages == NULL) {
        perror("Erreur de l'ouverture du fichier message.\n");
        exit(1);
    }

    char nom_de_chaine_a_lire[MAX_LINE_LENGTH];
    char chaine_a_lire[MAX_STRING_LENGTH];
    char line[MAX_LINE_LENGTH];
    int index_of_start;
    int size;
    int indice_de_message = 0;

    MESSAGES* tableau_de_message = (MESSAGES*) malloc(1000*sizeof(MESSAGES));
    size_t size_tableau_message = 0;

    MESSAGES m;
    m.Numero_de_messages = -1;

    while (fgets(line, sizeof(line), Fichier_messages) != NULL) {


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
            m.Numero_incription = atoi(chaine_a_lire);
        }else if(strcmp(nom_de_chaine_a_lire, "Titre") == 0){
            m.Titre = strdup(chaine_a_lire);
        }else if(strcmp(nom_de_chaine_a_lire ,"Date de poste") == 0){
            m.Date_de_poste = charger_date(chaine_a_lire);
        } else if(strcmp(nom_de_chaine_a_lire, "Nombre de messages") == 0){
            m.Numero_de_messages = atoi(chaine_a_lire);
            m.Textes = (char**) malloc((m.Numero_de_messages) * sizeof(char*));
        } else {
            m.Textes[indice_de_message++] = strdup(chaine_a_lire);
        }

        // printf("DEBUG 1: %i %i\n", indice_de_message, m.Numero_de_messages);

        if(m.Numero_de_messages != -1 && (unsigned int)indice_de_message == m.Numero_de_messages){

            if(size_tableau_message < 1000)   
                tableau_de_message[size_tableau_message++] = m;

            MESSAGES empty_message = {NULL, NULL};
            tableau_de_message[size_tableau_message] = empty_message;
            
            MESSAGES m;
            m.Numero_de_messages = -1;
            indice_de_message = 0;
        }

    }
    
    fclose(Fichier_messages);
    return tableau_de_message;
}