#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

typedef struct{
    int annee;
    int mois;
    int jour;

}Date;

void Saisir_date(Date*);

#endif