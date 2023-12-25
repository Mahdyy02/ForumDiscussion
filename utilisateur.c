#include <stdlib.h>
#include <stdio.h>
#include "utilisateur.h"
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
    }

    return -1;       
}

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
        for(unsigned int i = 0; i < strlen(u->Nom) - 1;i++){
            if(!isupper(u->Nom[i]) && (!islower(u->Nom[i]) || isdigit(u->Nom[i]))){
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
            if(!isupper(u->Prenom[i]) && (!islower(u->Prenom[i]) || isdigit(u->Prenom[i]))){
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

        printf("Le mot de passe doit être de longueur supèrieur à 8, contenir un chiffre majuscule et deux symboles.\n");    

    }

    printf("Choisissez votre pseudo: ");
    u->Pseudo = malloc(MAX_STRING_LENGTH);
    fgets(u->Pseudo, MAX_STRING_LENGTH, stdin);
    (u->Pseudo)[strlen(u->Pseudo) - 1] = '\0'; 

    u->Interdit = 0;
    u->Numero_inscription = ++(f.Nombre_utilisateurs);
    sauvegarder_utilisateur(*u);

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
    printf("l'adresse e-mail est: %s\n",u.Adresse_email);
}


void sauvegarder_utilisateur(UTILISATEUR u){

    FILE *Fichier_utilisateurs = fopen("utilisateurs.txt", "a");

    if (Fichier_utilisateurs == NULL) {
        perror("Erreur d'ouverture du fichier utilisateur.\n");
        exit(0);
    }

    u.Administrateur = 0;
    u.Numero_inscription = f.Nombre_utilisateurs - 1;

    fprintf(Fichier_utilisateurs ,"%s;%s;%s;%i/%i/%i;%i;%i;%s;%s;%s;%i\n", u.Nom, u.Prenom, u.Adresse, u.Date_de_naissance.jour, u.Date_de_naissance.mois, u.Date_de_naissance.annee, u.Numero_telephone, u.Numero_inscription, u.Adresse_email, u.Password, u.Pseudo, u.Administrateur);

    fclose(Fichier_utilisateurs);

    charger_utilisateur();
    
}

void charger_utilisateur(){

    FILE *Fichier_utilisateurs = fopen("utilisateurs.txt", "r");

    char line[MAX_LINE_LENGTH];

    if (Fichier_utilisateurs == NULL) {
        perror("Erreur de l'ouverture du fichier message.\n");
        exit(1);
    }

    f.Nombre_utilisateurs = 0;

    while (fgets(line, sizeof(line), Fichier_utilisateurs) != NULL) {

        UTILISATEUR u;

        f.Nombre_utilisateurs++;

        f.Utilisateurs = (UTILISATEUR*) realloc(f.Utilisateurs, (f.Nombre_utilisateurs)*sizeof(UTILISATEUR));
            
        int indice_attribut = 0;
        char *jeton = strtok(line, ";");

        while (jeton != NULL) {

            switch (indice_attribut){

                case 0:
                    u.Nom = strdup(jeton);
                    break;
                case 1:
                    u.Prenom = strdup(jeton);
                    break;
                case 2:
                    u.Adresse = strdup(jeton);
                    break;
                case 3:
                    u.Date_de_naissance = charger_date(jeton);
                    break;     
                case 4:
                    u.Numero_telephone = (unsigned int)atoi(jeton);
                    break;   
                case 5:
                    u.Numero_inscription = (unsigned int)atoi(jeton);
                    break;
                case 6:
                    u.Adresse_email = strdup(jeton);
                    break;
                case 7:
                    u.Password = strdup(jeton);
                    break;
                case 8:
                    u.Pseudo = strdup(jeton);
                    break;
                case 9:
                    u.Administrateur = (unsigned short int)atoi(jeton);
                    break;
                case 10:
                    u.Interdit = (unsigned short int)atoi(jeton);
                    break;       
            }

            indice_attribut++;
            jeton = strtok(NULL, ";");
        }

        memcpy(&f.Utilisateurs[u.Numero_inscription], &u, sizeof(UTILISATEUR));

    }
    
    fclose(Fichier_utilisateurs);
}

void free_utilisateurs(){
    for (unsigned int i = 0; i < f.Nombre_utilisateurs; ++i) {
        free(f.Utilisateurs[i].Nom);
        free(f.Utilisateurs[i].Prenom);
        free(f.Utilisateurs[i].Adresse);
        free(f.Utilisateurs[i].Adresse_email);
        free(f.Utilisateurs[i].Password);
        free(f.Utilisateurs[i].Pseudo);
    }
    free(f.Utilisateurs);
}

void basculer_interdiction_utilisateur(UTILISATEUR* u){

    Noeud_rubrique *iter_rubriques = f.Rubriques.tete;
    while(iter_rubriques != NULL){
        Noeud_liste_de_message *iter_messages = iter_rubriques->valeur.Listes_messages.tete;
        while(iter_messages!=NULL){
            Noeud_message *iter_message = iter_messages->Valeur.tete;
            while(iter_message != NULL){
                if(iter_message->Valeur.Numero_inscription == u->Numero_inscription) 
                    basculer_supression_message(&iter_rubriques->valeur, iter_messages->Valeur, &iter_message->Valeur);
                iter_message = iter_message->Suivant;
            }
            iter_messages = iter_messages->Suivant;
        }
        iter_rubriques = iter_rubriques->Suivant;
    }

    FILE *fichierEntree, *fichierTemporaire;
    char ligne[MAX_LINE_LENGTH]; 

    fichierEntree = fopen("utilisateurs.txt", "r");

    if (fichierEntree == NULL){
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fichierTemporaire = fopen("fichiertemporaire.txt", "w");

    if (fichierTemporaire == NULL){
        perror("Erreur lors de l'ouverture du fichier temporaire");
        fclose(fichierEntree);
        exit(EXIT_FAILURE);
    }

    unsigned int nombre_lignes = 0;
    while (fgets(ligne, sizeof(ligne), fichierEntree) != NULL) {
        if(nombre_lignes == u->Numero_inscription){
            if(u->Interdit) ligne[strlen(ligne)-2] = '0';
            else ligne[strlen(ligne)-2] = '1';
        }
        fprintf(fichierTemporaire, "%s", ligne);
        nombre_lignes++;
    }

    u->Interdit = !(u->Interdit);

    fclose(fichierEntree);
    fclose(fichierTemporaire);

    remove("utilisateurs.txt");
    rename("fichiertemporaire.txt", "utilisateurs.txt");
}