#include <stdio.h>
#include <stdlib.h>
#include "endereco.h"
#include "util.h"


void lerEndereco(TEndereco *endereco) {
    
    printf("Digite o logradouro: ");
    endereco->logradouro = lerTexto();

    printf("Digite o número: ");
    endereco->numero = lerTexto();

    printf("Digite o complemento: ");
    endereco->complemento = lerTexto();

    printf("Digite o bairro: ");
    endereco->bairro = lerTexto();

    printf("Digite a cidade: ");
    endereco->cidade = lerTexto();

    printf("Digite o estado: ");
    endereco->estado = lerTexto();

    do {
        printf("Digite o CEP (apenas números): ");
        endereco->cep = lerTexto();

        if (!validarCEP(endereco->cep)) { // Valida o CEP
            printf("CEP inválido! Digite novamente.\n");
            free(endereco->cep); // Libera a memória alocada para o CEP inválido
            endereco->cep = NULL; // Define como NULL para que o loop continue
        }
    } while (endereco->cep == NULL); // Continua pedindo o CEP até que seja válido
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
    free(endereco->numero);
    free(endereco->complemento);
    free(endereco->bairro);
    free(endereco->cidade);
    free(endereco->estado);
    free(endereco->cep);
}