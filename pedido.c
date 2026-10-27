#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "cliente.h"
#include "bebidas.h"
#include "pedido.h"
#include "util.h"

//funções apenas para este arquivo

static int lerItensPizza(TPedido *pedido, TListaPizzas *pizzas);
static int lerItensBebida(TPedido *pedido, TListaBebidas *bebidas);

void inicializarPedidos(TPedidos *pedidos){
    pedidos->itens = NULL;
    pedidos->quantidade = 0;
}

TPedido *buscarPedidoNumero(TPedidos *pedidos, int numero){
    for(int i = 0; i < pedidos->quantidade; i++){
        if(pedidos->itens[i].numero == numero){
            return &pedidos->itens[i];
        }
    }

    return NULL;
}

void listarPedidos(const TPedidos *pedidos){
    
    if(pedidos->quantidade == 0){
        printf("Nenhum pedido cadastrado.\n");
        return;
    }

    for(int i = 0; i < pedidos->quantidade; i++){
        TPedido *pedido = &pedidos->itens[i];

        exibirPedido(pedido);
    }
}

void exibirPedido(const TPedido *pedido){
    
    printf("Numero: %d\n", pedido->numero);
    printf("CPF do cliente: ");
    exibirCPF(pedido->cpfCliente);
    printf("Data do Pedido: ");
    exibirData(pedido->data);
    printf("Pizzas:\n");

    if(pedido->pizzas.quantidade == 0){
        printf("  (nenhuma)\n");
    }

    for(int i = 0; i < pedido->pizzas.quantidade; i++){
        TItemPizza *item = &pedido->pizzas.itens[i];

        printf(" %dx %s (%s)/(%s) - R$ %.2f cada - subtotal R$ %.2f\n", item->quantidade, item->nome, nomeTamanho(item->tamanho), nomeCategoria(item->categoria), item->precoUnitario, item->subtotal);
    }

    printf("Bebidas:\n");

    if(pedido->bebidas.quantidade == 0){
        printf(" (nenhuma)\n");
    }

    for(int i = 0; i < pedido->bebidas.quantidade; i++){
        TItemBebida *item = &pedido->bebidas.itens[i];

        printf("  %dx %s %d ml (%s) - R$ %.2f cada - subtotal R$ %.2f\n", item->quantidade, item->nome, item->volumeMl, nomeTipo(item->tipo), item->precoUnitario, item->subtotal);
    }

    printf("Total do pedido: R$ %.2f\n", pedido->valorTotal);

    printf("------------------------\n");
}

void liberarPedido(TPedido *pedido){

    free(pedido->cpfCliente);                       

    for(int i = 0; i < pedido->pizzas.quantidade; i++){
        free(pedido->pizzas.itens[i].nome);   
    }
    free(pedido->pizzas.itens);                

    for(int i = 0; i < pedido->bebidas.quantidade; i++){
        free(pedido->bebidas.itens[i].nome);  
    }
    free(pedido->bebidas.itens);    

    pedido->cpfCliente = NULL;
    pedido->pizzas.itens = NULL;
    pedido->pizzas.quantidade = 0;
    pedido->bebidas.itens = NULL;
    pedido->bebidas.quantidade = 0;
}

void liberarPedidos(TPedidos *pedidos){

    for(int i = 0; i < pedidos->quantidade; i++){
        liberarPedido(&pedidos->itens[i]);
    }

    free(pedidos->itens);
    pedidos->itens = NULL;
    pedidos->quantidade = 0;
}

int adicionarItemPizza(TPedido *pedido, const TPizza *pizza, int quantidade){

    TItemPizza *temp = realloc(pedido->pizzas.itens, (pedido->pizzas.quantidade + 1) *sizeof(TItemPizza));

    if(temp == NULL){
        printf("Erro ao alocar memoria para o item.\n");
        return 0;
    }

    pedido->pizzas.itens = temp;

    char *copiaNome = malloc(strlen(pizza->nome) + 1);

    if(copiaNome == NULL){
        printf("Erro ao alocar memoria para o item.\n");
        return 0;
    }

    strcpy(copiaNome, pizza->nome);

    TItemPizza *item = &pedido->pizzas.itens[pedido->pizzas.quantidade];

    item->nome = copiaNome;
    item->tamanho = pizza->tamanho;
    item->categoria = pizza->categoria;
    item->codigoPizza = pizza->codigo;
    item->quantidade = quantidade;
    item->precoUnitario = pizza->preco;
    item->subtotal = item->quantidade * item->precoUnitario;

    pedido->pizzas.quantidade++;

    return 1;
}

int adicionarItemBebida(TPedido *pedido, const TBebida *bebida, int quantidade){

    TItemBebida *temp = realloc(pedido->bebidas.itens, (pedido->bebidas.quantidade + 1) *sizeof(TItemBebida));

    if(temp == NULL){
        printf("Erro ao alocar memoria para o item.\n");
        return 0;
    }

    pedido->bebidas.itens = temp;

    char *copiaNome = malloc(strlen(bebida->nome) + 1);

    if(copiaNome == NULL){
        printf("Erro ao alocar memoria para o item.\n");
        return 0;
    }

    strcpy(copiaNome, bebida->nome);

    TItemBebida *item = &pedido->bebidas.itens[pedido->bebidas.quantidade];

    item->nome = copiaNome;
    item->volumeMl = bebida->volumeMl;
    item->tipo = bebida->tipo;
    item->codigoBebida = bebida->codigoBebida;
    item->quantidade = quantidade;
    item->precoUnitario = bebida->preco;
    item->subtotal = item->quantidade * item->precoUnitario;

    pedido->bebidas.quantidade++;

    return 1;

}

void calcularTotalPedido(TPedido *pedido){

    float total = 0;

    for(int i = 0; i < pedido->pizzas.quantidade; i++){
        total += pedido->pizzas.itens[i].subtotal;
    }

    for(int i = 0; i < pedido->bebidas.quantidade; i++){
        total += pedido->bebidas.itens[i].subtotal;
    }

    pedido->valorTotal = total;
}

static int lerItensPizza(TPedido *pedido, TListaPizzas *pizzas){

    int codigo;
    int r;

    do{

        printf("Digite o codigo da pizza (ou 0 para terminar): ");
        r = lerInteiro(&codigo);

        if(r == -1){
            return 0;
        }

        if(r == 0){
            printf("Entrada invalida!\n");
            codigo = -1;
            continue;
        }

        if(codigo == 0){
            break;
        }

        TPizza *pizza = buscarPizzaCodigo(pizzas, codigo);

        if(pizza == NULL){
            printf("Pizza nao encontrada.\n");
            continue;
        }
        
        // pede a quantidade até ser válida
        int quantidade = 0;

        do{

            printf("Quantidade: ");
            r = lerInteiro(&quantidade);

            if(r == -1){
                return 0;
            }

            if(r == 0 || quantidade <= 0){
                printf("Quantidade invalida!\n");
                quantidade = 0;
            }
        } while(quantidade <= 0);

        if(adicionarItemPizza(pedido, pizza, quantidade) == 0){
            return 0;
        }
    }while(codigo != 0);

    return 1;
}

static int lerItensBebida(TPedido *pedido, TListaBebidas *bebidas){

    int codigo;
    int r;

    do{

        printf("Digite o codigo da bebida (ou 0 para terminar): ");
        r = lerInteiro(&codigo);

        if(r == -1){
            return 0;
        }

        if(r == 0){
            printf("Entrada invalida!\n");
            codigo = -1;
            continue;
        }

        if(codigo == 0){
            break;
        }

        TBebida *bebida = buscarBebidaCodigo(bebidas, codigo);

        if(bebida == NULL){
            printf("Bebida nao encontrada.\n");
            continue;
        }

        int quantidade = 0;

        do{
            printf("Quantidade: ");
            r = lerInteiro(&quantidade);

            if(r == -1){
                return 0;
            }

            if(r == 0 || quantidade <= 0){
                printf("Quantidade invalida!\n");
                quantidade = 0;
            }
        } while(quantidade <= 0);

        if(adicionarItemBebida(pedido, bebida, quantidade) == 0){
            return 0;
        }
    } while(codigo != 0);

    return 1;
}

int realizarPedido(TPedidos *pedidos, TClientes *clientes, TListaPizzas *pizzas, TListaBebidas *bebidas){
    
    printf("Digite o CPF do cliente: ");
    char *cpf = lerTexto();

    if(cpf == NULL){
        return 0;
    }

    if(buscarClienteCPF(clientes, cpf) == NULL){
        printf("Cliente nao encontrado.\n");
        free(cpf);
        return 0;
    }

    TPedido pedido;

    int maiorNumero = 0;

    for(int i = 0; i < pedidos->quantidade; i++){
        if(pedidos->itens[i].numero > maiorNumero){
            maiorNumero = pedidos->itens[i].numero;
        }
    }

    pedido.numero = maiorNumero + 1;
    pedido.cpfCliente = cpf;
    pedido.pizzas.itens = NULL;
    pedido.pizzas.quantidade = 0;
    pedido.bebidas.itens = NULL;
    pedido.bebidas.quantidade = 0;
    pedido.valorTotal = 0;

    printf("Data do pedido:\n");

    if(lerData(&pedido.data) != 1){
        liberarPedido(&pedido);
        return 0;
    }

    if(lerItensPizza(&pedido, pizzas) == 0){
        liberarPedido(&pedido);
        return 0;
    }

    if(lerItensBebida(&pedido, bebidas) == 0){
        liberarPedido(&pedido);
        return 0;
    }

    if(pedido.pizzas.quantidade == 0 && pedido.bebidas.quantidade == 0){
        printf("Pedido sem itens. Cancelado.\n");
        liberarPedido(&pedido);
        return 0;
    }

    calcularTotalPedido(&pedido);
    exibirPedido(&pedido);

    int opcao = -1;
    int r;

    do{

        printf("1 - Confirmar pedido\n");
        printf("0 - Cancelar pedido\n");
        printf("Escolha: ");

        r = lerInteiro(&opcao);

        if(r == -1){
            liberarPedido(&pedido);
            return 0;
        }

        if(r == 0){
            printf("Entrada invalida!\n");
            opcao = -1;
            continue;
        }

        if(opcao != 0 && opcao != 1){
            printf("Opcao invalida!\n");
        }
    } while(opcao != 0 && opcao != 1);

    if(opcao == 0){
        printf("Pedido cancelado.\n");
        liberarPedido(&pedido);
        return 0;
    }

    
    TPedido *temp = realloc(pedidos->itens, (pedidos->quantidade + 1) *sizeof(TPedido));

    if(temp == NULL){
        printf("Erro ao alocar memoria para o pedido.\n");
        liberarPedido(&pedido);
        return 0;
    }

    pedidos->itens = temp;
    pedidos->itens[pedidos->quantidade] = pedido;
    pedidos->quantidade++;

    atualizarCompraCliente(clientes, pedido.cpfCliente, pedido.data);

    printf("Pedido %d realizado com sucesso!\n", pedido.numero);

    return 1;
}

void listarPedidosCliente(const TPedidos *pedidos, const char *cpf){

    int encontrou = 0;

    for(int i = 0; i < pedidos->quantidade; i++){
        if(strcmp(pedidos->itens[i].cpfCliente, cpf) == 0){
            exibirPedido(&pedidos->itens[i]);
            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("Nenhum pedido encontrado para este cliente.\n");
    }
}

int clienteTemPedido(const TPedidos *pedidos, const char *cpf){

    for(int i = 0; i < pedidos->quantidade; i++){
        if(strcmp(pedidos->itens[i].cpfCliente, cpf) == 0){
            return 1;
        }
    }

    return 0;
}

int excluirClienteSeguro(TClientes *clientes, const TPedidos *pedidos, const char *cpf){

    if(clienteTemPedido(pedidos, cpf)){
        printf("Este cliente tem pedidos e nao pode ser excluido.\n");
        return 0;
    }

    return excluirCliente(clientes, cpf);
}

int pizzaEmPedido(const TPedidos *pedidos, int codigo){

    for(int i = 0; i < pedidos->quantidade; i++){

        const TPedido *pedido = &pedidos->itens[i];

        for(int j = 0; j < pedido->pizzas.quantidade; j++){
            if(pedido->pizzas.itens[j].codigoPizza == codigo){
                return 1;
            }
        }
    }

    return 0;
}

int excluirPizzaSegura(TListaPizzas *pizzas, const TPedidos *pedidos, int codigo){

    if(pizzaEmPedido(pedidos, codigo)){
        printf("Esta pizza esta em pedidos e nao pode ser excluida.\n");
        return 0;
    }

    return excluirPizza(pizzas, codigo);
}

int bebidaEmPedido(const TPedidos *pedidos, int codigo){
    
    for(int i = 0; i < pedidos->quantidade; i++){

        const TPedido *pedido = &pedidos->itens[i];

        for(int j = 0; j < pedido->bebidas.quantidade; j++){
            if(pedido->bebidas.itens[j].codigoBebida == codigo){
                return 1;
            }
        }
    }

    return 0;
}

int excluirBebidaSegura(TListaBebidas *bebidas, const TPedidos *pedidos, int codigo){

    if(bebidaEmPedido(pedidos, codigo)){
        printf("Esta bebida esta em pedidos e nao pode ser excluida.\n");
        return 0;
    }

    return excluirBebida(bebidas, codigo);
    
}
