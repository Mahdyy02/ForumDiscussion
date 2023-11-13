#ifndef UTILISATEUR_H_INCLUDED
#define UTILISATEUR_H_INCLUDED


typedef struct 
{
    char* Nom;
    char* Prenom;
    char* Adresse;
    char* Date_de_naissance;
    unsigned int Numero_telephone;
    char* Adresse_email;
    char* Password;
    char* Pseudo;
    unsigned short int Administrateur;

}UTILISATEUR;



#endif