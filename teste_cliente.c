
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "data.h"
#include "cliente.h"

int main(void){
    TClientes clientes;
    inicializarClientes(&clientes);

    int op;
    char *cpf;
    do{
        printf("\n1-Cadastrar 2-Listar 3-Buscar CPF 4-Buscar nome\n");
        printf("5-Alterar 6-Excluir 7-Atualizar ultima compra 0-Sair: ");
        if(lerInteiro(&op) != 1){ op = 0; }

        switch(op){
            case 1: cadastrarCliente(&clientes); break;
            case 2: listarClientes(&clientes); break;
            case 3:
                printf("CPF (so numeros): ");
                cpf = lerTexto();
                if(cpf != NULL){
                    TCliente *c = buscarClienteCPF(&clientes, cpf);
                    if(c == NULL){ printf("Nao encontrado.\n"); }
                    else{ exibirCliente(c); }
                    free(cpf);
                }
                break;
            case 4:
                printf("Nome: ");
                cpf = lerTexto();   // aqui a variavel guarda o nome
                if(cpf != NULL){
                    buscarClienteNome(&clientes, cpf);
                    free(cpf);
                }
                break;
            case 5:
                printf("CPF (so numeros): ");
                cpf = lerTexto();
                if(cpf != NULL){
                    alterarCliente(&clientes, cpf);
                    free(cpf);
                }
                break;
            case 6:
                printf("CPF (so numeros): ");
                cpf = lerTexto();
                if(cpf != NULL){
                    excluirCliente(&clientes, cpf);
                    free(cpf);
                }
                break;
            case 7:
                printf("CPF (so numeros): ");
                cpf = lerTexto();
                if(cpf != NULL){
                    TData data;
                    if(lerData(&data) == 1){
                        atualizarCompraCliente(&clientes, cpf, data);
                    }
                    free(cpf);
                } 
                break;
        }
    } while(op != 0);

    liberarClientes(&clientes);
    return 0;
}