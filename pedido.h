#ifndef PEDIDO_H
#define PEDIDO_H
#include "data.h"
#include "pizza.h"
#include "bebidas.h"
#include "cliente.h"

typedef struct{
    char *nome;
    TTamanhoPizza tamanho;
    TCategoriaPizza categoria;
    int codigoPizza;
    int quantidade;
    float precoUnitario;
    float subtotal;
} TItemPizza;

typedef struct{
    TItemPizza *itens;
    int quantidade;
} TItensPizza;

typedef struct{
    char *nome;
    int volumeMl;
    TTipoBebida tipo;
    int codigoBebida;
    int quantidade;
    float precoUnitario;
    float subtotal;
} TItemBebida;

typedef struct{
    TItemBebida *itens;
    int quantidade;
} TItensBebida;

typedef struct{
    int numero;
    char *cpfCliente;
    TData data;
    TItensPizza pizzas;
    TItensBebida bebidas;
    float valorTotal;
} TPedido;

typedef struct{
    TPedido *itens;
    int quantidade;
} TPedidos;

//protótipos das funções

void inicializarPedidos(TPedidos *pedidos);
TPedido *buscarPedidoNumero(TPedidos *pedidos, int numero);
void listarPedidos(const TPedidos *pedidos);
void liberarPedidos(TPedidos *pedidos);
void liberarPedido(TPedido *pedido);
void exibirPedido(const TPedido *pedido);
int adicionarItemPizza(TPedido *pedido, const TPizza *pizza, int quantidade);
int adicionarItemBebida(TPedido *pedido, const TBebida *bebida, int quantidade);
void calcularTotalPedido(TPedido *pedido);
int realizarPedido(TPedidos *pedidos, TClientes *clientes, TListaPizzas *pizzas, TListaBebidas *bebidas);
void listarPedidosCliente(const TPedidos *pedidos, const char *cpf);

//aux para exclusões
int clienteTemPedido(const TPedidos *pedidos, const char *cpf);
int excluirClienteSeguro(TClientes *clientes, const TPedidos *pedidos, const char *cpf);
int pizzaEmPedido(const TPedidos *pedidos, int codigo);
int excluirPizzaSegura(TListaPizzas *pizzas, const TPedidos *pedidos, int codigo);
int bebidaEmPedido(const TPedidos *pedidos, int codigo);
int excluirBebidaSegura(TListaBebidas *bebidas, const TPedidos *pedidos, int codigo);

#endif
