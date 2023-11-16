

void affichage (MESSAGE m){
    printf(" le titre de message est: %s\n",m.Titre);
    printf("le texte écrit est: %s\n",m.Texte);
    printf("la date de poste est: %i/%i/%i\n",m.Date_de_poste.jour,m.Date_de_poste.mois,m.Date_de_poste.annee);
}
