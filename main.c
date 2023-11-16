#include <stdlib.h>
#include "message.h"
#include "rubrique.h"
#include "utilisateur.h"


int main(){

    RUBRIQUE r;

    saisir_rubrique(&r);
    affichage_rubrique(r);

    return 0;
}