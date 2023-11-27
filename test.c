#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"
#include "date.h"

#define MAX_STRING_LENGTH 100
#define MAX_LINE_LENGTH 256


int main(){
    int c;
    char* str;

    str = strdup("Hello world!");

    printf("%s", str);
}