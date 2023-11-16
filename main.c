#include <stdlib.h>
#include "message.h"
#include "rubrique.h"
#include "utilisateur.h"


int main(){

    MESSAGES m;

    saisir_message(MESSAGES* m);
    affichage_message(MESSAGES m);

    return 0;
}