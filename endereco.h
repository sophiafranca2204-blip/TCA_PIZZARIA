#include <stdio.h>
#include <string.h>
#ifndef ENDERECO_H
#define ENDERECO_H

typedef struct{
    char *logradouro;
    char *numero;
    char * complemento;
    char *bairro;
    char *cidade;
    char *estado;
    char *cep;
}TEndereco;

// Protótipos das funções
void lerEndereco(TEndereco *endereco);
void liberarEndereco(TEndereco *endereco);
int validarCEP(const char *cep);
void exibirCEP (const char *cep);

#endif
