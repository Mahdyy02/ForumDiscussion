#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forum.h"
#include "global.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_STRING_LENGTH 100


void saisir_forum(){

    while (1){ 
        char adresse_entree[MAX_STRING_LENGTH];
        printf("Donner l'adresse internet du forum: ");
        scanf("%s", adresse_entree); 
        if(strcmp(adresse_entree, f.Adresse_internet) == 0) break;
    }
}