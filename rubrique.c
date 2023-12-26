#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "rubrique.h"
#include <dirent.h>
#include "global.h"
#include "linked_lists.h"
#include "date.h"

#define MAX_STRING_LENGTH 100
#define MAX_LINE_LENGTH 256

void saisir_rubrique(RUBRIQUE* r){

    r->Numero_inscription = u.Numero_inscription;
    r->Date_de_poste = date_actuelle();
    r->Supprime = 0;
    initialiser_liste_de_liste_de_message(&r->Listes_messages);
    
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

    initialiser_liste(&r->Sites_internet);

    char site_internet[MAX_LINE_LENGTH];
    do{
        printf("Donnez le site(vide pour quitter): ");
        fgets(site_internet, MAX_STRING_LENGTH, stdin);
        if(strcmp(site_internet, "\n") != 0){
            site_internet[strlen(site_internet)-1] = '\0';
            ajouter_element(&r->Sites_internet, site_internet);
        }    
    }while(strcmp(site_internet, "\n") != 0);

    ajouter_rubrique(&f.Rubriques, *r);
    sauvegarder_rubrique(*r);

}

void affichage_rubrique(RUBRIQUE r){

    unsigned int nombre_messages_rubriques = 0;
    unsigned int taille_messages = 0;
    Noeud_liste_de_message *iter_messages = r.Listes_messages.tete;
    while(iter_messages!=NULL){
        Noeud_message *iter_message = iter_messages->Valeur.tete;
        while(iter_message != NULL){
            Noeud *iter_text = iter_message->Valeur.Messages.tete;
            while(iter_text != NULL){
                taille_messages+=strlen(iter_text->Valeur);
                iter_text = iter_text->Suivant;
            }
            nombre_messages_rubriques++;
            iter_message = iter_message->Suivant;
        }
        iter_messages = iter_messages->Suivant;
    }

    if(r.Supprime){
        printf("\n*Rubrique est supprimée par les administrateurs.*\n\n");
        if (!u.Administrateur) return;
    };

    printf("Theme: %s\n", r.Theme);
    if(!f.Utilisateurs[r.Numero_inscription].Interdit || u.Administrateur) printf("Auteur: %s\n", f.Utilisateurs[r.Numero_inscription].Pseudo);
    else printf("Auteur: Cet utilisateur est interdit\n");
    if(u.Administrateur) printf("Nombre de messages dans cette rubrique: %i\n", nombre_messages_rubriques);
    if(u.Administrateur) printf("Taille moyenne des messages dans cette rubrique: %.2f\n", (float)taille_messages/nombre_messages_rubriques);
    printf("Date de poste: %i/%i/%i\n", r.Date_de_poste.jour ,r.Date_de_poste.mois, r.Date_de_poste.annee);
    
    Noeud *iter = r.Sites_internet.tete;
    for(int i = 0; iter != NULL; i++){
        printf("Site %i: %s\n", i+1, iter->Valeur);
        iter = iter->Suivant;
    }

}

void initialiser_liste_de_liste_de_message(Liste_de_liste_de_message* LLM){
    LLM->tete = NULL;
}

void ajouter_liste_de_message(Liste_de_liste_de_message* LLM, Liste_message LM){

    Noeud_liste_de_message *Nouvelle_liste_de_message = (Noeud_liste_de_message*)malloc(sizeof(Noeud_liste_de_message));
    Nouvelle_liste_de_message->Valeur = LM;
    Nouvelle_liste_de_message->Suivant = NULL;

    if(LLM->tete == NULL){
        LLM->tete = Nouvelle_liste_de_message;
        return;
    }

    Noeud_liste_de_message *iter = LLM->tete;
    while(iter->Suivant != NULL) iter = iter->Suivant;
    iter->Suivant = Nouvelle_liste_de_message;
}

void charger_rubrique(RUBRIQUE* r) {

    char *rep_dossier;
    rep_dossier = strdup(r->Theme);

    rep_dossier = (char*)realloc(rep_dossier, (strlen(rep_dossier)+strlen("../Rubriques/"))*sizeof(char));

    snprintf(rep_dossier, MAX_LINE_LENGTH, "../Rubriques/%s", r->Theme);


    DIR *dir = opendir(rep_dossier);

    if (dir == NULL) {
        printf("Erreur d'ouverture de la répertoire %s.\n", rep_dossier);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            char rep_fichier[MAX_LINE_LENGTH];
            snprintf(rep_fichier, sizeof(rep_fichier), "%s/%s", rep_dossier, entry->d_name);

            if (entry->d_type == DT_REG){
                if(strchr(rep_fichier, '_') == NULL){

                    FILE *Fichier_rubrique = fopen(rep_fichier, "r");

                    if (Fichier_rubrique == NULL) {
                        printf("Erreur de l'ouverture du fichier %s.\n", rep_fichier);
                        exit(EXIT_FAILURE);
                    }

                    char nom_de_chaine_a_lire[MAX_LINE_LENGTH];
                    char chaine_a_lire[MAX_STRING_LENGTH];
                    char line[MAX_LINE_LENGTH];
                    int index_of_start;
                    int size;

                    initialiser_liste_de_liste_de_message(&r->Listes_messages);
                    initialiser_liste(&r->Sites_internet);

                    while (fgets(line, sizeof(line), Fichier_rubrique) != NULL) {

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
                            r->Numero_inscription = (unsigned int)atoi(chaine_a_lire);
                        }else if(strcmp(nom_de_chaine_a_lire ,"Date de poste") == 0){
                            r->Date_de_poste = charger_date(chaine_a_lire);
                        }else if(strcmp(nom_de_chaine_a_lire ,"Supprimé") == 0){
                            r->Supprime = (unsigned short int)atoi(chaine_a_lire);
                        }else if(strcmp(nom_de_chaine_a_lire ,"Theme") == 0){
                            r->Theme = strdup(chaine_a_lire);
                        }else{
                            ajouter_element(&r->Sites_internet, chaine_a_lire);
                        }
                    }
                    fclose(Fichier_rubrique);

                }else{ 
                    ajouter_liste_de_message(&r->Listes_messages, charger_message(rep_fichier));                    
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
    fprintf(Fichier_rubrique, "Supprimé: %i\n", r.Supprime);
    fprintf(Fichier_rubrique,"Date de poste: %i/%i/%i\n", r.Date_de_poste.jour, r.Date_de_poste.mois, r.Date_de_poste.annee);
    fprintf(Fichier_rubrique,"Numero d'inscription: %i\n", r.Numero_inscription);

    if(r.Sites_internet.tete == NULL){
        printf("Erreur: le message n'admet pas de texte.\n");
        exit(EXIT_FAILURE);
    }

    if(r.Sites_internet.tete != NULL){
        Noeud* iter = r.Sites_internet.tete;
        for(unsigned int i = 1; iter != NULL; i++){
            fprintf(Fichier_rubrique, "Site %i: %s\n", i, iter->Valeur);
            iter = iter->Suivant;
        }
    }


    if (chdir("..") != 0) {
        perror("Erreur du retour vers le dossier principale.\n");
        return;
    }

    fclose(Fichier_rubrique);

}

void initialiser_liste_rubriques(Liste_rubrique *LR){
    LR->tete = NULL;
}

void ajouter_rubrique(Liste_rubrique *LR, RUBRIQUE r){

    Noeud_rubrique *nouvelle_rubrique = (Noeud_rubrique*)malloc(sizeof(Noeud_rubrique));
    nouvelle_rubrique->valeur = r;
    nouvelle_rubrique->Suivant = NULL;

    if(LR->tete == NULL){
        LR->tete = nouvelle_rubrique;
        return;
    }

    Noeud_rubrique *iter = LR->tete;
    while(iter->Suivant != NULL) iter = iter->Suivant;
    iter->Suivant = nouvelle_rubrique;

}

void retirer_rubrique(Liste_rubrique* LR){

    if(LR->tete == NULL){
        printf("Erreur: On ne peux pas retirer un element d'une liste vide.\n");
        exit(EXIT_FAILURE);
    }

    if(LR->tete->Suivant == NULL){
        detruire_liste_de_liste_de_message(&LR->tete->valeur.Listes_messages);
        free(LR->tete);
        LR->tete = NULL;
        return;
    }

    Noeud_rubrique *iter = LR->tete;
    while(iter->Suivant->Suivant != NULL) iter = iter->Suivant;
    detruire_liste_de_liste_de_message(&iter->Suivant->valeur.Listes_messages);
    free(iter->Suivant);
    iter->Suivant = NULL;
}

void detruire_liste_rubrique(Liste_rubrique* LR){
    while(LR->tete != NULL) retirer_rubrique(LR);
}

void charger_rubriques(Liste_rubrique *LR) {

    char *cheminDossier = "../Rubriques";
    DIR *dossier = opendir(cheminDossier);

    if (dossier == NULL) {
        perror("Impossible d'ouvrir le répertoire");
        exit(EXIT_FAILURE);
    }

    if(LR->tete != NULL) detruire_liste_rubrique(LR);
    initialiser_liste_rubriques(LR);

    while (1){
        struct dirent *entree = readdir(dossier);
        if (!entree) break;

        if (entree->d_type == DT_DIR && strcmp(entree->d_name, ".") != 0 && strcmp(entree->d_name, "..") != 0){
            RUBRIQUE r;
            r.Theme = strdup(entree->d_name);
            charger_rubrique(&r);    
            ajouter_rubrique(LR, r);
        }
    }
    closedir(dossier);

}

unsigned int nombre_rubriques(){
    
    unsigned int nr = 0;
    Noeud_rubrique *iter = f.Rubriques.tete;
    while(iter != NULL){
        nr++;
        iter = iter->Suivant;
    }

    return nr;

}

void basculer_supression_rubrique(RUBRIQUE *r){
    
    char *rep_fichier = strdup(r->Theme);
    rep_fichier = (char*)realloc(rep_fichier, (strlen("../Rubriques//.txt")+ 2*strlen(r->Theme) + 1)*sizeof(char));
    snprintf(rep_fichier, MAX_LINE_LENGTH, "../Rubriques/%s/%s.txt", r->Theme, r->Theme);

    FILE *fichierEntree, *fichierTemporaire;
    char ligne[MAX_LINE_LENGTH]; 

    fichierEntree = fopen(rep_fichier, "r");

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

    while (fgets(ligne, sizeof(ligne), fichierEntree) != NULL){
        if(strstr(ligne, "Supprimé") != NULL){
            if(r->Supprime) ligne[strlen(ligne)-2] = '0';
            else ligne[strlen(ligne)-2] = '1';
        }
        fprintf(fichierTemporaire, "%s", ligne);
    }

    r->Supprime = !r->Supprime;

    fclose(fichierEntree);
    fclose(fichierTemporaire);

    remove(rep_fichier);
    rename("fichiertemporaire.txt", rep_fichier);
    
}

void afficher_utilisateurs_rubrique(RUBRIQUE* r){
    Noeud_liste_de_message *iter_messages = r->Listes_messages.tete;
    printf("\n");
    unsigned int nombres_utilisateurs = 1;
    unsigned int numero_inscription_utilisateur_precedant;
    if(iter_messages!=NULL){
        numero_inscription_utilisateur_precedant = iter_messages->Valeur.tete->Valeur.Numero_inscription;
        printf("%i. %s(%i)\n", nombres_utilisateurs++, f.Utilisateurs[numero_inscription_utilisateur_precedant].Pseudo, numero_inscription_utilisateur_precedant);
    }else return;
    while(iter_messages!=NULL){
        Noeud_message *iter_message = iter_messages->Valeur.tete;
        while(iter_message != NULL){
            if (iter_message->Valeur.Numero_inscription > numero_inscription_utilisateur_precedant){
                printf("%i. %s(%i)\n", nombres_utilisateurs++, f.Utilisateurs[iter_message->Valeur.Numero_inscription].Pseudo, iter_message->Valeur.Numero_inscription);
                numero_inscription_utilisateur_precedant = iter_message->Valeur.Numero_inscription;
            }    
            iter_message = iter_message->Suivant;
        }
        iter_messages = iter_messages->Suivant;
    }
    printf("\n");
}

void chercher_mot_messages(char* mot_cherche){

    Noeud_rubrique *iter_rubriques = f.Rubriques.tete;
    while(iter_rubriques != NULL){
        Noeud_liste_de_message *iter_messages = iter_rubriques->valeur.Listes_messages.tete;
        while(iter_messages!=NULL){
            Noeud_message *iter_message = iter_messages->Valeur.tete;
            while(iter_message != NULL){
                Noeud *iter_text = iter_message->Valeur.Messages.tete;
                while(iter_text != NULL){
                    if(strstr(iter_text->Valeur, mot_cherche) != NULL){
                        printf("Rubrique: %s\n", iter_rubriques->valeur.Theme);
                        affichage_message(iter_message->Valeur);
                    }
                    iter_text = iter_text->Suivant;
                }
                iter_message = iter_message->Suivant;
            }
            iter_messages = iter_messages->Suivant;
        }
        iter_rubriques = iter_rubriques->Suivant;
    }

}

char* jours_plus_active(){

    unsigned int frequences_jours_semaine[] = {0, 0, 0, 0, 0, 0, 0}; 

    Noeud_rubrique *iter_rubriques = f.Rubriques.tete;
    while(iter_rubriques != NULL){
        frequences_jours_semaine[jour_semaine(iter_rubriques->valeur.Date_de_poste)]++;
        Noeud_liste_de_message *iter_messages = iter_rubriques->valeur.Listes_messages.tete;
        while(iter_messages!=NULL){
            Noeud_message *iter_message = iter_messages->Valeur.tete;
            while(iter_message != NULL){
                frequences_jours_semaine[jour_semaine(iter_message->Valeur.Date_de_poste)]++;
                iter_message = iter_message->Suivant;
            }
            iter_messages = iter_messages->Suivant;
        }
        iter_rubriques = iter_rubriques->Suivant;

    }

    printf("D  |  L  |  Ma  |  Me  |  J  |  V  |  S  |\n");
    for(int i = 0; i < 7; i++) printf("%i  |  ", frequences_jours_semaine[i]);
        printf("\n");

    unsigned int maximum_frequence = frequences_jours_semaine[0];
    unsigned int jours_plus_frequent = 0;
    for (int i = 0; i < 7; i++){
        if (frequences_jours_semaine[i] > maximum_frequence) {
            maximum_frequence = frequences_jours_semaine[i];
            jours_plus_frequent = (unsigned int)i;
        }
    }

    switch (jours_plus_frequent){
        case 0:
            return "dimanche";
            break;
        case 1:
            return "lundi";
            break;
        case 2:
            return "mardi";
            break;
        case 3:
            return "mercredi";
            break;
        case 4:
            return "jeudi";
            break;
        case 5:
            return "vendredi";
            break;
        case 6:
            return "samedi";
            break;                    
        default:
            return "Erreur";
            break;
        }    
}