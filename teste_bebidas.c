#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "bebidas.h"

int main(void){
    TListaBebidas bebidas;
    inicializarBebidas(&bebidas);

    int op, codigo;
    do{
        printf("\n1-Cadastrar 2-Listar 3-Listar por tipo 4-Buscar codigo 5-Buscar nome\n");
        printf("6-Alterar 7-Excluir 0-Sair: ");
        if(lerInteiro(&op) != 1){ op = 0; }   // EOF ou entrada invalida: encerra

        switch(op){
            case 1: cadastrarBebida(&bebidas); break;
            case 2: listarBebidas(&bebidas); break;
            case 3:
                printf("Tipo (0 = nao alcoolica, 1 = alcoolica): ");
                if(lerInteiro(&codigo) == 1){
                    listarBebidasPorTipo(&bebidas, (TTipoBebida)codigo);
                }
                break;
            case 4:
                printf("Codigo: ");
                if(lerInteiro(&codigo) == 1){
                    TBebida *b = buscarBebidaCodigo(&bebidas, codigo);
                    if(b == NULL){ printf("Nao encontrada.\n"); }
                    else{ exibirBebida(b); }
                }
                break;
            case 5: {
                printf("Nome: ");
                char *nome = lerTexto();
                if(nome != NULL){
                    buscarBebidaNome(&bebidas, nome);
                    free(nome);
                }
                break;
            }
            case 6:
                printf("Codigo: ");
                if(lerInteiro(&codigo) == 1){ alterarBebida(&bebidas, codigo); }
                break;
            case 7:
                printf("Codigo: ");
                if(lerInteiro(&codigo) == 1){ excluirBebida(&bebidas, codigo); }
                break;
        }
    } while(op != 0);

    liberarBebidas(&bebidas);
    return 0;
}