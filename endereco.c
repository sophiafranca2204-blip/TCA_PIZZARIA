#include <stdio.h>
#include <stdlib.h>
#include "endereco.h"
#include "util.h"


int lerEndereco(TEndereco *endereco) {

    endereco->logradouro = NULL;
    endereco->numero = NULL;
    endereco->complemento = NULL;
    endereco->bairro = NULL;
    endereco->cidade = NULL;
    endereco->estado = NULL;
    endereco->cep = NULL;
    
    printf("Digite o logradouro: ");
    endereco->logradouro = lerTexto();

    if(endereco->logradouro == NULL){
        printf("Erro ao alocar memoria para o logradouro.\n");
        liberarEndereco(endereco);
        return 0;
    }

    printf("Digite o número: ");
    endereco->numero = lerTexto();

    if(endereco->numero == NULL){
        printf("Erro ao alocar memoria para o numero.\n");
        liberarEndereco(endereco);
        return 0;
    }

    printf("Digite o complemento: ");
    endereco->complemento = lerTexto();

    if(endereco->complemento == NULL){
        printf("Erro ao alocar memoria para o complemento.\n");
        liberarEndereco(endereco);
        return 0;
    }

    printf("Digite o bairro: ");
    endereco->bairro = lerTexto();

    if(endereco->bairro == NULL){
        printf("Erro ao alocar memoria para o bairro.\n");
        liberarEndereco(endereco);
        return 0;
    }

    printf("Digite a cidade: ");
    endereco->cidade = lerTexto();

    if(endereco->cidade == NULL){
        printf("Erro ao alocar memoria para a cidade.\n");
        liberarEndereco(endereco);
        return 0;
    }

    printf("Digite o estado: ");
    endereco->estado = lerTexto();

    if(endereco->estado == NULL){
        printf("Erro ao alocar memoria para o estado.\n");
        liberarEndereco(endereco);
        return 0;
    }

    int cepValido = 0;

    do {
        printf("Digite o CEP (apenas números): ");
        char *cep = lerTexto();

        if(cep == NULL){
            printf("Erro ao alocar memoria para o CEP.\n");
            liberarEndereco(endereco);
            return 0;
        }

        if(validarCEP(cep)){
            endereco->cep = cep;
            cepValido = 1;
        }
        else{
            printf("CEP invalido! Digite novamente.\n");
            free(cep);
        }
    } while (!cepValido); // Continua pedindo o CEP até que seja válido

    return 1;
}

int validarCEP(const char *cep){

    // Verifica se o CEP tem exatamente 8 caracteres
    if(strlen(cep) != 8){
        return 0;
    }

    // Verifica se todos os caracteres são dígitos
    for(int i = 0; i < 8; i++){
        if(cep[i] < '0' || cep[i] > '9'){
            return 0;
        }
    }

    return 1;
}

void exibirCEP(const char *cep){
    printf("%.5s-%.3s\n", cep, cep + 5);
}

void liberarEndereco(TEndereco *endereco) {
    free(endereco->logradouro);
    endereco->logradouro = NULL;
    free(endereco->numero);
    endereco->numero = NULL;
    free(endereco->complemento);
    endereco->complemento = NULL;
    free(endereco->bairro);
    endereco->bairro = NULL;
    free(endereco->cidade);
    endereco->cidade = NULL;
    free(endereco->estado);
    endereco->estado = NULL;
    free(endereco->cep);
    endereco->cep = NULL;
}