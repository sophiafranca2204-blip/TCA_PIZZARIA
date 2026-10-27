#include <stdlib.h>
#include "util.h"
#include "data.h"
#include "cliente.h"
#include "pizza.h"
#include "bebidas.h"
#include "pedido.h"

int main(void){
    TClientes clientes;
    TListaPizzas pizzas;
    TListaBebidas bebidas;
    TPedidos pedidos;

    inicializarClientes(&clientes);
    inicializarPizzas(&pizzas);
    inicializarBebidas(&bebidas);
    inicializarPedidos(&pedidos);

    int op, valor;
    char *cpf;
    do{
        printf("\n1-Cadastrar cliente 2-Cadastrar pizza 3-Cadastrar bebida\n");
        printf("4-Realizar pedido 5-Listar pedidos 6-Buscar pedido por numero\n");
        printf("7-Pedidos de um cliente 8-Excluir cliente 9-Excluir pizza 10-Excluir bebida 0-Sair: ");
        if(lerInteiro(&op) != 1){ op = 0; }

        switch(op){
            case 1: cadastrarCliente(&clientes); break;
            case 2: cadastrarPizza(&pizzas); break;
            case 3: cadastrarBebida(&bebidas); break;
            case 4: realizarPedido(&pedidos, &clientes, &pizzas, &bebidas); break;
            case 5: listarPedidos(&pedidos); break;
            case 6:
                printf("Numero: ");
                if(lerInteiro(&valor) == 1){
                    TPedido *p = buscarPedidoNumero(&pedidos, valor);
                    if(p == NULL){ printf("Nao encontrado.\n"); }
                    else{ exibirPedido(p); }
                }
                break;
            case 7:
                printf("CPF (so numeros): ");
                cpf = lerTexto();
                if(cpf != NULL){
                    listarPedidosCliente(&pedidos, cpf);
                    free(cpf);
                }
                break;
            case 8:
                printf("CPF (so numeros): ");
                cpf = lerTexto();
                if(cpf != NULL){
                    excluirClienteSeguro(&clientes, &pedidos, cpf);
                    free(cpf);
                }
                break;
            case 9:
                printf("Codigo da pizza: ");
                if(lerInteiro(&valor) == 1){ excluirPizzaSegura(&pizzas, &pedidos, valor); }
                break;
            case 10:
                printf("Codigo da bebida: ");
                if(lerInteiro(&valor) == 1){ excluirBebidaSegura(&bebidas, &pedidos, valor); }
                break;
        }
    } while(op != 0);

    liberarPedidos(&pedidos);
    liberarBebidas(&bebidas);
    liberarPizzas(&pizzas);
    liberarClientes(&clientes);
    return 0;
}