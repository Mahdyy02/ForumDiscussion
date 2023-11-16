

void affichage(RUBRIQUE r){
printf("le théme du rubrique est: %s\n",r.Théme);
printf("la date de poste du premier rubrique est: %s/%s/%s/\n",r.Date_poste.jour,r.Date_poste.mois,r.Date_poste.annee);
printf("le  premier message est: %s\n",r.Message);
printf("les liste internets sont: %s\n",r.Liste_internet);
}

