#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

char *lerTexto(void){

    char *texto = NULL;
    int caracteres;
    int tamanho = 0;

    while((caracteres = getchar()) != '\n' && caracteres != EOF){
        texto = realloc(texto, (tamanho + 1) *sizeof(char));

        if(texto == NULL){
            return NULL;
        }

        texto[tamanho] = caracteres;
        tamanho++;
    }

    texto = realloc(texto, (tamanho + 1) * sizeof(char));

    if(texto == NULL){
        return NULL;
    }

    texto[tamanho] = '\0';

    return texto;
}
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // descarta o caractere
}