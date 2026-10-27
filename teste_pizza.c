#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "pizza.h"

int main(void){
    TListaPizzas pizzas;
    inicializarPizzas(&pizzas);

    int op, valor;
    do{
        printf("\n1-Cadastrar 2-Listar 3-Listar por tamanho 4-Listar por categoria\n");
        printf("5-Buscar codigo 6-Buscar nome 7-Alterar 8-Excluir 0-Sair: ");
        if(lerInteiro(&op) != 1){ op = 0; }

        switch(op){
            case 1: cadastrarPizza(&pizzas); break;
            case 2: listarPizzas(&pizzas); break;
            case 3:
                printf("Tamanho (0 = pequena, 1 = media, 2 = grande): ");
                if(lerInteiro(&valor) == 1){
                    listarPizzasPorTamanho(&pizzas, (TTamanhoPizza)valor);
                }
                break;
            case 4:
                printf("Categoria (0 = tradicional, 1 = especial, 2 = nobre): ");
                if(lerInteiro(&valor) == 1){
                    listarPizzasPorCategoria(&pizzas, (TCategoriaPizza)valor);
                }
                break;
            case 5:
                printf("Codigo: ");
                if(lerInteiro(&valor) == 1){
                    TPizza *p = buscarPizzaCodigo(&pizzas, valor);
                    if(p == NULL){ printf("Nao encontrada.\n"); }
                    else{ exibirPizza(p); }
                }
                break;
            case 6: {
                printf("Nome: ");
                char *nome = lerTexto();
                if(nome != NULL){
                    buscarPizzaNome(&pizzas, nome);
                    free(nome);
                }
                break;
            }
            case 7:
                printf("Codigo: ");
                if(lerInteiro(&valor) == 1){ alterarPizza(&pizzas, valor); }
                break;
            case 8:
                printf("Codigo: ");
                if(lerInteiro(&valor) == 1){ excluirPizza(&pizzas, valor); }
                break;
        }
    } while(op != 0);

    liberarPizzas(&pizzas);
    return 0;
}