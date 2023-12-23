#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "linked_lists.h"
#include "global.h"

#define MAX_STRING_LENGTH 100
#define MAX_LINE_LENGTH 256

void saisir_message(MESSAGE* m, MESSAGE* reponse, unsigned short int question){

    m->Numero_inscription = u.Numero_inscription;
    m->Date_de_poste = date_actuelle();
    m->question = question;
    initialiser_liste(&m->Messages);
    if(question) reponse = NULL;

    unsigned short int valide;

    if(question){

        do{
            valide = 1;
            free(m->Titre);
            printf("Donnez le titre du message(ne doit pas contenir des caracteres speciaux sauf '.' et '_'): ");
            m->Titre = (char*)malloc(MAX_STRING_LENGTH*sizeof(char));

            if (m->Titre == NULL) {
                fprintf(stderr, "Échec d'allocation mémoire du titre.\n");
                exit(EXIT_FAILURE);
            }

            fgets(m->Titre, MAX_STRING_LENGTH, stdin);
            m->Titre[strlen(m->Titre)-1] = '\0';

            for(unsigned int i = 0; i < strlen(m->Titre); i++){
                if (!isalnum(m->Titre[i]) && m->Titre[i] != '_' && m->Titre[i] != '.'){
                    valide = 0;
                    break;
                }
            }

        }while(!valide);
        
    }else if(reponse != NULL) m->Titre = strdup(reponse->Titre);

    initialiser_liste(&m->Messages);

    char message[MAX_LINE_LENGTH];
    do{
        printf("Le contenu de message(vide pour quitter): ");
        fgets(message, MAX_STRING_LENGTH, stdin);
        if(strcmp(message, "\n") != 0){
            message[strlen(message)-1] = '\0';
            ajouter_element(&m->Messages, message);
        }    
    }while(strcmp(message, "\n") != 0);
    
}

void affichage_message(MESSAGE m){

    if(f.Utilisateurs[m.Numero_inscription].Interdit) return;

    printf("Titre: %s\n", m.Titre);
    printf("Auteur: %s\n", f.Utilisateurs[m.Numero_inscription].Pseudo);

    if(m.question) printf("Type: Question\n");
    else printf("Type: Réponse\n");
        
    Noeud *iter = m.Messages.tete;
    for(int i = 0; iter != NULL; i++){
        if(i == 0){
            printf("Premier message: \n");
            printf("%s\n", iter->Valeur);
        }else{
            printf("Reponse anonyme %i: \n", i);
            printf("%s\n", iter->Valeur);
        }
        iter = iter->Suivant;

    }

    printf("La date de poste est: %i/%i/%i\n", m.Date_de_poste.jour, m.Date_de_poste.mois, m.Date_de_poste.annee);
    printf("===============================================\n");
}

void repondre_messsage_anonyme(MESSAGE m, RUBRIQUE r){

    MESSAGE reponse;
    reponse.question = 1;
    reponse.Titre = strdup(m.Titre);
    reponse.Date_de_poste = m.Date_de_poste;

    initialiser_liste(&reponse.Messages);
    ajouter_element(&reponse.Messages, m.Messages.tete->Valeur);

    char message[MAX_LINE_LENGTH];
    printf("Ecrivez votre reponse au message '%s'.\n", m.Messages.tete->Valeur);
    do{
        printf("Texte (vide pour quitter): ");
        fgets(message, MAX_STRING_LENGTH, stdin);
        if(strcmp(message, "\n") != 0){
            message[strlen(message)-1] = '\0';
            ajouter_element(&reponse.Messages, message);
        }    
    }while(strcmp(message, "\n") != 0);

    sauvegarder_message(reponse, NULL, r);

}

void sauvegarder_message(MESSAGE m, MESSAGE *rm, RUBRIQUE r){

    const char *DossierRubrique = r.Theme;

    if (chdir("../Rubriques") != 0) {
        fprintf(stderr, "Erreur lors du changement vers le répertoire rubriques.\n");
        exit(EXIT_FAILURE);
    }

    if (access(DossierRubrique, F_OK) == -1) {
        if (mkdir(DossierRubrique) != 0) {
            fprintf(stderr, "Erreur lors de la création du répertoire %s\n", DossierRubrique);
            exit(EXIT_FAILURE);
        }
    }

    if (chdir(DossierRubrique) != 0) {
        fprintf(stderr, "Erreur lors du changement vers le répertoire %s.\n", r.Theme);
        exit(EXIT_FAILURE);
    }

    char Nom_fichier_message[100];
    snprintf(Nom_fichier_message, sizeof(Nom_fichier_message), "%s_%s.txt", r.Theme, m.Titre);

    int question_existe = 0;

    Noeud_rubrique *iter = f.Rubriques.tete;
    while(iter != NULL){
        if(strcmp(r.Theme, iter->valeur.Theme) == 0) break;
        iter = iter->Suivant;
    }
    
    Noeud_message *message_a_repondre = NULL; 
    Noeud_liste_de_message *iter_liste = iter->valeur.Listes_messages.tete;
    while(iter_liste != NULL){
        Noeud_message *iter_message = iter_liste->Valeur.tete;
        while(iter_message != NULL){
            if(strcmp(iter_message->Valeur.Messages.tete->Valeur, m.Messages.tete->Valeur) == 0){
                question_existe = 1;
                message_a_repondre = iter_message; 
                break;
            }
            iter_message = iter_message->Suivant;
        }
        if(question_existe) break;    
        iter_liste = iter_liste->Suivant;
    }

    if(question_existe){ 

        if(message_a_repondre != NULL){
            Noeud *reponse = m.Messages.tete->Suivant;
            while(reponse != NULL){
                ajouter_element(&message_a_repondre->Valeur.Messages, reponse->Valeur);
                reponse = reponse->Suivant;
            }
        }

        FILE *fichierEntree, *fichierTemporaire;
        char ligne[MAX_LINE_LENGTH]; 

        fichierEntree = fopen(Nom_fichier_message, "r");

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

        int flag = 0;
        int nombre_de_reply = 0;

        while (fgets(ligne, sizeof(ligne), fichierEntree) != NULL) {
            
            if(strstr(ligne, m.Messages.tete->Valeur) != NULL){
                flag = 1;
                fprintf(fichierTemporaire, "%s", ligne);
            }else if(flag){
                if(ligne[1] == '='){
                    Noeud *iter = m.Messages.tete->Suivant;
                    while(iter != NULL){                    
                        fprintf(fichierTemporaire, "Reponse anonyme %i: %s\n", ++nombre_de_reply, iter->Valeur);   
                        iter = iter->Suivant;
                    }
                    flag = 0;

                }else nombre_de_reply++;
                fprintf(fichierTemporaire, "%s", ligne);
            }else{
                fprintf(fichierTemporaire, "%s", ligne);
            }

        }

        fclose(fichierEntree);
        fclose(fichierTemporaire);

        remove(Nom_fichier_message);
        rename("fichiertemporaire.txt", Nom_fichier_message);

        if (chdir("..") != 0){
            perror("Erreur du retour vers le dossier principale.\n");
            exit(EXIT_FAILURE);
        }

    }else if(m.question){

        Noeud_rubrique *iter = f.Rubriques.tete;
        while(iter != NULL){
            if(strcmp(r.Theme, iter->valeur.Theme) == 0) break;
            iter = iter->Suivant;
        }

        unsigned short int titre_trouve = 0;
        Noeud_liste_de_message *iter_liste = iter->valeur.Listes_messages.tete;
        while(iter_liste != NULL){
            Noeud_message *iter_message = iter_liste->Valeur.tete;
            while(iter_message != NULL){
                if(strcmp(iter_message->Valeur.Titre, m.Titre) == 0){
                    titre_trouve = 1;
                    break;
                }
                iter_message = iter_message->Suivant;
            }
            if(titre_trouve) break;    
            iter_liste = iter_liste->Suivant;
        }

        if(iter_liste != NULL) ajouter_message(&iter_liste->Valeur, m);
        else{
            Liste_message LM;
            initialiser_liste_de_messages(&LM);
            ajouter_message(&LM, m);
            ajouter_liste_de_message(&iter->valeur.Listes_messages, LM);
        }
            
        FILE *Fichier_messages = fopen(Nom_fichier_message, "a");

        if(Fichier_messages == NULL){
            perror("Erreur de l'ouverture du fichier message.\n");
            exit(EXIT_FAILURE);
        }

        fprintf(Fichier_messages, "Numero d'inscription: %i\n", m.Numero_inscription);
        fprintf(Fichier_messages, "Titre: %s\n", m.Titre);
        fprintf(Fichier_messages, "Date de poste: %i/%i/%i\n", m.Date_de_poste.jour, m.Date_de_poste.mois, m.Date_de_poste.annee);
        fprintf(Fichier_messages, "Type: %i\n", m.question);

        if(m.Messages.tete == NULL){
            printf("Erreur: le message n'admet pas de texte.\n");
            exit(EXIT_FAILURE);
        }

        fprintf(Fichier_messages, "Message: %s\n", m.Messages.tete->Valeur);

        if(m.Messages.tete->Suivant != NULL){
            Noeud* iter = m.Messages.tete->Suivant;
            for(unsigned int i = 1; iter != NULL; i++){
                fprintf(Fichier_messages, "Reponse anonyme %i: %s\n", i, iter->Valeur);
                iter = iter->Suivant;
            }
        }

        fprintf(Fichier_messages, "========================================================\n");

        fclose(Fichier_messages);

        if (chdir("..") != 0){
            perror("Erreur du retour vers le dossier principale.\n");
            exit(EXIT_FAILURE);
        }

    }else{
        
        Noeud_rubrique *iter = f.Rubriques.tete;
        while(iter != NULL){
            if(strcmp(r.Theme, iter->valeur.Theme) == 0) break;
            iter = iter->Suivant;
        }
        
        unsigned short int flag = 0;
        Noeud_message *message_a_repondre = NULL;
        Noeud_liste_de_message *iter_liste = iter->valeur.Listes_messages.tete;
        while(iter_liste != NULL){
            Noeud_message *iter_message = iter_liste->Valeur.tete;
            while(iter_message != NULL){
                if(strcmp(iter_message->Valeur.Messages.tete->Valeur, rm->Messages.tete->Valeur) == 0){
                    flag = 1;
                    message_a_repondre = iter_message; 
                    break;
                }
                iter_message = iter_message->Suivant;
            }
            if(flag) break;    
            iter_liste = iter_liste->Suivant;
        }

        if(flag){
            Noeud_message *nouveau_message = (Noeud_message*) malloc(sizeof(Noeud_message));
            nouveau_message->Valeur = m;
            nouveau_message->Suivant = message_a_repondre->Suivant;
            message_a_repondre->Suivant = nouveau_message;
        }else{
            printf("Le message a repondre est introuvable.\n");
            return;
        }  

        FILE *fichierEntree, *fichierTemporaire;
        char ligne[MAX_LINE_LENGTH]; 

        fichierEntree = fopen(Nom_fichier_message, "r");

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

        int message_a_repondre_trouve = 0;
        int nombre_de_reply = 0;

        while (fgets(ligne, sizeof(ligne), fichierEntree) != NULL) {
            
            if(strstr(ligne, rm->Messages.tete->Valeur) != NULL){
                message_a_repondre_trouve = 1;
                fprintf(fichierTemporaire, "%s", ligne);

            }else if(message_a_repondre_trouve){
                
                if(ligne[1] == '='){

                    fprintf(fichierTemporaire, "%s", ligne);

                    fprintf(fichierTemporaire, "Numero d'inscription: %i\n", m.Numero_inscription);
                    fprintf(fichierTemporaire, "Titre: %s\n", m.Titre);
                    fprintf(fichierTemporaire, "Date de poste: %i/%i/%i\n", m.Date_de_poste.jour, m.Date_de_poste.mois, m.Date_de_poste.annee);
                    fprintf(fichierTemporaire, "Type: %i\n", m.question);

                    if(m.Messages.tete == NULL){
                        printf("Erreur: le message n'admet pas de texte.\n");
                        exit(EXIT_FAILURE);
                    }

                    fprintf(fichierTemporaire, "Message: %s\n", m.Messages.tete->Valeur);

                    if(m.Messages.tete->Suivant != NULL){
                        Noeud* iter = m.Messages.tete->Suivant;
                        for(unsigned int i = 1; iter != NULL; i++){
                            fprintf(fichierTemporaire, "Reponse anonyme %i: %s\n", i, iter->Valeur);
                            iter = iter->Suivant;
                        }
                    }

                    fprintf(fichierTemporaire, "========================================================\n");
                    message_a_repondre_trouve = 0;

                }else nombre_de_reply++;

            }else{
                fprintf(fichierTemporaire, "%s", ligne);
            }

        }

        fclose(fichierEntree);
        fclose(fichierTemporaire);

        remove(Nom_fichier_message);
        rename("fichiertemporaire.txt", Nom_fichier_message);

        if (chdir("..") != 0){
            perror("Erreur du retour vers le dossier principale.\n");
            exit(EXIT_FAILURE);
        }


    }
}

void initialiser_liste_de_messages(Liste_message* LM){
    LM->tete = NULL;
}

void ajouter_message(Liste_message* LM, MESSAGE m){

    Noeud_message *nouveau_message = (Noeud_message*)malloc(sizeof(Noeud_message));
    nouveau_message->Valeur = m;
    nouveau_message->Suivant = NULL;

    if(LM->tete == NULL){
        LM->tete = nouveau_message;
        return;
    }

    Noeud_message *iter = LM->tete;
    while(iter->Suivant != NULL) iter = iter->Suivant;
    iter->Suivant = nouveau_message;

}

void retirer_message(Liste_message* LM){

    if(LM->tete == NULL) return;

    if(LM->tete->Suivant == NULL){
        free(LM->tete);
        LM->tete = NULL;
        return;
    }

    Noeud_message *iter = LM->tete;
    while(iter->Suivant->Suivant != NULL) iter = iter->Suivant;
    free(iter->Suivant);
    iter->Suivant = NULL;

}

void detruire_liste_de_message(Liste_message* LM){
    while(LM->tete != NULL) retirer_message(LM);
}

void retirer_liste_de_message(Liste_de_liste_de_message *LLM){

    if(LLM->tete == NULL) return;

    if(LLM->tete->Suivant == NULL){
        detruire_liste_de_message(&LLM->tete->Valeur);
        free(LLM->tete);
        LLM->tete = NULL;
        return;
    }

    Noeud_liste_de_message *iter_liste = LLM->tete;
    while(iter_liste->Suivant->Suivant != NULL) iter_liste = iter_liste->Suivant;
    detruire_liste_de_message(&iter_liste->Suivant->Valeur);
    free(iter_liste->Suivant);
    iter_liste->Suivant = NULL;
}

void detruire_liste_de_liste_de_message(Liste_de_liste_de_message *LLM){
    while(LLM->tete != NULL) retirer_liste_de_message(LLM);
}

Liste_message charger_message(char* rep_message){

    FILE *Fichier_messages = fopen(rep_message, "r");

    if (Fichier_messages == NULL) {
        perror("Erreur de l'ouverture du fichier message.\n");
        exit(EXIT_FAILURE);
    }

    char nom_de_chaine_a_lire[MAX_LINE_LENGTH];
    char chaine_a_lire[MAX_STRING_LENGTH];
    char line[MAX_LINE_LENGTH];
    int index_of_start;
    int size;
    
    MESSAGE m;
    initialiser_liste(&m.Messages);

    Liste_message LM;
    initialiser_liste_de_messages(&LM);

    while (fgets(line, sizeof(line), Fichier_messages) != NULL) {

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
            m.Numero_inscription = atoi(chaine_a_lire);
        }else if(strcmp(nom_de_chaine_a_lire, "Titre") == 0){
            m.Titre = strdup(chaine_a_lire);
        }else if(strcmp(nom_de_chaine_a_lire ,"Date de poste") == 0){
            m.Date_de_poste = charger_date(chaine_a_lire);
        }else if(strcmp(nom_de_chaine_a_lire ,"Type") == 0){
            m.question = atoi(chaine_a_lire);
        }else{
            
            if(line[1] != '=' && line[0] != '\0'){
                ajouter_element(&m.Messages, chaine_a_lire);
            }else{
                ajouter_message(&LM, m);
                initialiser_liste(&m.Messages);
            }

        }

    }
    
    fclose(Fichier_messages);

    return LM;
}

void voir_messages_utilisateur(UTILISATEUR* u){
    Noeud_rubrique *iter_rubriques = f.Rubriques.tete;
    while(iter_rubriques != NULL){
        Noeud_liste_de_message *iter_messages = iter_rubriques->valeur.Listes_messages.tete;
        while(iter_messages!=NULL){
            Noeud_message *iter_message = iter_messages->Valeur.tete;
            while(iter_message != NULL){
                if(iter_message->Valeur.Numero_inscription == u->Numero_inscription) affichage_message(iter_message->Valeur);
                iter_message = iter_message->Suivant;
            }
            iter_messages = iter_messages->Suivant;
        }
        iter_rubriques = iter_rubriques->Suivant;
    }
}