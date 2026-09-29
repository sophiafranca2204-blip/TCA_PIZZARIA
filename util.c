#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

char *lerTexto(void){

    char *texto = NULL;
    int caracteres;
    int tamanho = 0;

    while((caracteres = getchar()) != '\n' && caracteres != EOF){
        char *temp = realloc(texto, (tamanho + 1) *sizeof(char));

        if(temp == NULL){
            free(texto);
            return NULL;
        }

        texto = temp;
        texto[tamanho] = caracteres;
        tamanho ++;
    }

    if(caracteres == EOF && tamanho == 0){
        return NULL;   // a entrada acabou e nada foi lido
    }

    char *final = realloc(texto, (tamanho + 1) *sizeof(char));

    if(final == NULL){
        free(texto);
        return NULL;
    }

    texto = final;
    texto[tamanho] = '\0';

    return texto;
}
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // descarta o caractere
}

int lerInteiro(int *valor){
    int resultado = scanf("%d", valor);

    if(resultado == EOF){
        return -1;
    }

    limparBuffer();

    if(resultado == 1){
        return 1;
    }

    return 0;
}