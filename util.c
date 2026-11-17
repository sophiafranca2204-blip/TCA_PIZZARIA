#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

char *lerTexto(void){ // Função para ler uma linha de texto do usuário, alocando dinamicamente a memória necessária

    char *texto = NULL; // Ponteiro para armazenar o texto lido, NULL pois ainda não foi alocado
    int caracteres; 
    int tamanho = 0;

    while((caracteres = getchar()) != '\n' && caracteres != EOF){ // Lê caractere por caractere até encontrar uma nova linha ou EOF
        char *temp = realloc(texto, (tamanho + 1) *sizeof(char)); // Realoca a memória para armazenar o novo caractere

        if(temp == NULL){ // Se a realocação falhar, libera a memória alocada e retorna NULL
            free(texto);
            return NULL;
        }

        texto = temp;
        texto[tamanho] = caracteres; // Armazena o caractere lido na posição correta do vetor
        tamanho ++; // Incrementa o tamanho do texto lido
    }

    if(caracteres == EOF && tamanho == 0){ // Se EOF for encontrado antes de ler qualquer caractere, retorna NULL
        return NULL;   // a entrada acabou e nada foi lido
    }

    while(tamanho > 0 && (texto[tamanho - 1] == ' ' || texto[tamanho - 1] == '\t')){ // Remove espaços em branco e tabulações do final do texto'
        tamanho--; // Decrementa o tamanho do texto
    }
 
    char *final = realloc(texto, (tamanho + 1) *sizeof(char)); // Realoca a memória para o tamanho final do texto, incluindo o caractere nulo '\0'

    if(final == NULL){
        free(texto);
        return NULL;
    }

    texto = final;
    texto[tamanho] = '\0';

    return texto;
}

void limparBuffer(void) { // Função para limpar o buffer de entrada
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lê e descarta todos os caracteres restantes no buffer até encontrar uma nova linha ou EOF
}

int lerInteiro(int *valor){

    int resultado = scanf("%d", valor); // Lê um inteiro do usuário e armazena no ponteiro fornecido

    if(resultado == EOF){
        return -1;
    }

    if(resultado == 1){

        int proximo = getchar();

        if(proximo == '\n' || proximo == EOF){
            return 1;
        }

        // sobrou lixo depois do número (ex: 12abc)
        limparBuffer();
        return 0;
    }

    // o scanf falhou: o texto não começava com um número
    limparBuffer();
    return 0;
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

char *lerLinhaArquivo(FILE *arq){

    char *texto = NULL;
    int caracteres;
    int tamanho = 0;

    while((caracteres = fgetc(arq)) != '\n' && caracteres != EOF){
        char *temp = realloc(texto, (tamanho + 1) * sizeof(char));

        if(temp == NULL){
            free(texto);
            return NULL;
        }

        texto = temp;
        texto[tamanho] = caracteres;
        tamanho++;
    }

    if(caracteres == EOF && tamanho == 0){
        return NULL;
    }

    char *final = realloc(texto, (tamanho + 1) * sizeof(char));

    if(final == NULL){
        free(texto);
        return NULL;
    }

    texto = final;
    texto[tamanho] = '\0';

    return texto;
}

int lerInteiroArquivo(FILE *arq, int *valor){

    char *linha = lerLinhaArquivo(arq);

    if(linha == NULL){
        return 0;
    }

    int lidos = sscanf(linha, "%d", valor);
    free(linha);

    return lidos == 1;
}

int lerDecimalArquivo(FILE *arq, float *valor){

    char *linha = lerLinhaArquivo(arq);

    if(linha == NULL){
        return 0;
    }

    int lidos = sscanf(linha, "%f", valor);
    free(linha);

    return lidos == 1;
}

void limparTela(void) {

    #ifdef _WIN32
        system("cls"); // Comando para limpar a tela no Windows
    #else
        system("clear"); // Comando para limpar a tela em sistemas Unix/Linux
    #endif
}

void pausar(void) {

    printf("Pressione Enter para continuar...");
    char *texto = lerTexto(); // Lê uma linha de texto do usuário para pausar a execução
    free(texto); // Libera a memória alocada para o texto lido
}

#define SEPARADOR "-----"

void escreverSeparador(FILE *arq){
    fprintf(arq, "%s\n", SEPARADOR);
}

int lerSeparadorArquivo(FILE *arq){

    char *linha = lerLinhaArquivo(arq);

    if(linha == NULL){
        return 0;
    }

    int ok = (strcmp(linha, SEPARADOR) == 0);
    free(linha);

    return ok;
}