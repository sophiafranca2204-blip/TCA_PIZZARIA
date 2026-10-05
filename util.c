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

int lerInteiro(int *valor){ // Função para ler um inteiro do usuário
    int resultado = scanf("%d", valor); // Lê um inteiro do usuário e armazena em 'valor'

    if(resultado == EOF){ // Verifica se ocorreu um erro de leitura
        return -1;
    }

    limparBuffer(); // Limpa o buffer de entrada para evitar problemas com leituras subsequentes

    if(resultado == 1){ // Se a leitura foi bem-sucedida, retorna 1
        return 1;
    }

    return 0; // Se a leitura falhou, retorna 0
}

int lerDecimal(float *valor){

    char *texto = lerTexto();

    if(texto == NULL){
        return -1; // Erro ao ler o texto
    }

    int valido = 1;
    int digitos = 0;
    int pontos = 0;

    for(int i = 0; texto[i] != '\0'; i++){
        
        if(texto[i] == ','){ // Substitui vírgula por ponto para padronizar a entrada
            texto[i] = '.';
        }

        if(texto[i] >= '0' && texto[i] <= '9'){ // Verifica se o caractere é um dígito
            digitos++;
        }
        else if(texto[i] == '.'){ // Verifica se o caractere é um ponto decimal
            pontos++;
        }
        else{
            valido = 0;
        }
    }

    if(!valido || pontos > 1 || digitos == 0){ // Verifica se a entrada é válida (apenas dígitos e no máximo um ponto decimal)
        free(texto);
        return 0; // Entrada inválida
    }

    //convertendo texto para numero digito por digito

    double result = 0;
    double casa = 0.1;
    int dpsDoPonto = 0;

    for(int i = 0; texto[i] != '\0'; i++){

        if(texto[i] == '.'){ // Verifica se o caractere é um ponto decimal
            dpsDoPonto = 1;
        }
        else if(dpsDoPonto){ // Se já encontrou o ponto decimal, adiciona os dígitos após o ponto
            result += (texto[i] - '0') * casa; // Converte o dígito para um número e adiciona à parte decimal
            casa /= 10; // Diminui a casa decimal para o próximo dígito
        }
        else{
            result = result * 10 + (texto[i] - '0'); // Converte o dígito para um número e adiciona à parte inteira
        }
    }

    *valor = (float)result; // Armazena o valor convertido no ponteiro fornecido
    free(texto);

    return 1; // Entrada válida
}