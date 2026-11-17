#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include "cliente.h"
#include "bebidas.h"
#include "pedido.h"
#include "util.h"

//nomes dos arquivos
#define ARQ_CLIENTES "clientes.txt"
#define ARQ_PIZZAS   "pizzas.txt"
#define ARQ_BEBIDAS  "bebidas.txt"
#define ARQ_PEDIDOS  "pedidos.txt"

//aux
static int salvarTudo(const TClientes *clientes, const TListaPizzas *pizzas, const TListaBebidas *bebidas, const TPedidos *pedidos);
static void exibirMenuOpcao(void);


int main(){
    TListaPizzas listaP;
    inicializarPizzas(&listaP);

    TListaBebidas listaB;
    inicializarBebidas(&listaB);

    TClientes listaC;
    inicializarClientes(&listaC);

    TPedidos pedidos;
    inicializarPedidos(&pedidos);

    if(!carregarClientes(&listaC, ARQ_CLIENTES) || !carregarPizzas(&listaP, ARQ_PIZZAS) || !carregarBebidas(&listaB, ARQ_BEBIDAS) || !carregarPedidos(&pedidos, ARQ_PEDIDOS)){
        printf("Erro ao carregar dados dos arquivos.\n");

        liberarClientes(&listaC);
        liberarBebidas(&listaB);
        liberarPizzas(&listaP);
        liberarPedidos(&pedidos);
        
        return 1;
    }

    int opcao = -1;

    while(opcao != 0){

        int pausa = 1;
        limparTela();
        exibirMenuOpcao();
        
        int r = lerInteiro(&opcao);

        if(r == -1){
            opcao = 0;
        }
        else if(r == 0){
            printf("Entrada invalida!\n");
            pausar();
            opcao = -1;
            continue;
        }

        switch (opcao)
        {
        case 1:{
            printf("\n=============================\n");
            printf("           CLIENTE            ");
            printf("\n=============================\n");
            printf("1. Cadastrar cliente\n");
            printf("2. Listar clientes\n"); 
            printf("3. Buscar cliente por CPF\n");
            printf("4. Alterar cliente\n");
            printf("5. Excluir cliente\n");
            printf("6. Buscar cliente por nome\n");
            printf("0. Voltar\n");
            printf("-----------------------------\n");
            printf("Escolha uma opcao: ");

            int opcaoCliente;

            int r = lerInteiro(&opcaoCliente);

            if(r == -1){
                opcao = 0;
                break;
            }

            if(r == 0){
                printf("Entrada invalida!\n");
                break;
            }
            
            switch (opcaoCliente)
            {

            case 1:{
                if(cadastrarCliente(&listaC)){
                    salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                }

                break;
            }

            case 2:{
                listarClientes(&listaC);    
                break;
            }

            case 3:{
                printf("Digite o CPF do cliente: ");
                char *cpf = lerTexto();
                
                if(cpf != NULL){
                    TCliente *c = buscarClienteCPF(&listaC, cpf);

                    if(c == NULL){
                        printf("Cliente nao encontrado.\n");
                    }
                    else{
                        exibirCliente(c);
                    }

                    free(cpf);
                }
                break;
            }

            case 4:{
                printf("Digite o CPF do cliente: ");
                char *cpf = lerTexto();

                if(cpf != NULL){
                    if(alterarCliente(&listaC, cpf)){
                        salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                    }
                    free(cpf);
                }

                break;
            }

            case 5:{
                printf("Digite o CPF do cliente: ");
                
                char *cpf = lerTexto();
                if(cpf != NULL){
                    if(excluirClienteSeguro(&listaC, &pedidos, cpf)){
                        salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                    }

                    free(cpf);
                }

                break;
            }

            case 6:{
                printf("Digite o nome do cliente: ");

                char *nome = lerTexto();
                if(nome != NULL){
                    buscarClienteNome(&listaC, nome);
                    free(nome);
                }
                break;
            }

            case 0:
                pausa = 0; 
                break; 
            
            default:
                printf("Opcao invalida!\n");
                break;
            }

            break;
            
            }
            case 2:{
                printf("\n=============================\n");
                printf("           BEBIDA             ");
                printf("\n=============================\n");
                printf("1. Cadastrar bebida\n");
                printf("2. Listar bebidas\n"); 
                printf("3. Buscar bebida por nome\n");
                printf("4. Alterar bebida\n");
                printf("5. Excluir bebida\n");
                printf("6. Listar bebidas alcoolicas\n");
                printf("7. Listar bebidas nao alcoolicas\n");
                printf("8. Buscar bebida por codigo\n");
                printf("0. Voltar\n");
                printf("-----------------------------\n");
                printf("Escolha uma opcao: ");

                int opcaoBebida;

                int r = lerInteiro(&opcaoBebida);

                if(r == -1){
                    opcao = 0;
                    break;
                }

                if(r == 0){
                    printf("Entrada invalida!\n");
                    break;
                }

                switch (opcaoBebida)
                {
                    case 1:{
                        if(cadastrarBebida(&listaB)){
                            salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                        }

                        break;
                    }

                    case 2:{
                        listarBebidas(&listaB);    
                        break;
                    }

                    case 3:{
                        printf("Digite o nome da bebida: ");
                        
                        char *nome = lerTexto();
                        if(nome != NULL){
                            buscarBebidaNome(&listaB, nome);
                            free(nome);
                        }
                        break;
                    }

                    case 4:{
                        int codigo;
                        printf("Digite o codigo da bebida: ");
                        
                        if(lerInteiro(&codigo) == 1){
                            if(alterarBebida(&listaB, codigo)){
                                salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }

                        break;
                    }

                    case 5:{
                        int codigo;
                        printf("Digite o codigo da Bebida: ");

                        if(lerInteiro(&codigo) == 1){
                            if(excluirBebidaSegura(&listaB, &pedidos, codigo)){
                                salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }
                        break;
                    }

                    case 6:{
                        listarBebidasPorTipo(&listaB, ALCOOLICA);
                        break;
                    }

                    case 7:{
                        listarBebidasPorTipo(&listaB, NAO_ALCOOLICA);
                        break;
                    }

                    case 8: {

                        int codigo;
                        printf("Digite o codigo da bebida: ");

                        if(lerInteiro(&codigo) == 1){

                            TBebida *b = buscarBebidaCodigo(&listaB, codigo);

                            if(b == NULL){
                                printf("Bebida nao encontrada.\n");
                            }
                            else{
                                exibirBebida(b);
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }
                        break;
                    }

                    case 0:
                        pausa = 0; 
                        break;
                    
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            }

             case 3:{
                printf("\n=============================\n");
                printf("           PEDIDO             ");
                printf("\n=============================\n");
                printf("1. Cadastrar pedido\n");
                printf("2. Listar pedidos\n");          
                printf("3. Buscar pedido por numero\n");
                printf("4. Pedidos de um cliente\n");
                printf("0. Voltar\n");
                printf("-----------------------------\n");
                printf("Escolha uma opcao: ");

                int opcaoPedido;

                int r = lerInteiro(&opcaoPedido);

                if(r == -1){
                    opcao = 0;
                    break;
                }

                if(r == 0){
                    printf("Entrada invalida!\n");
                    break;
                }

                switch (opcaoPedido)
                {
                    case 1:{
                        if(realizarPedido(&pedidos, &listaC, &listaP, &listaB)){
                            salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                        }

                        break;
                    }

                    case 2:{
                        listarPedidos(&pedidos);
                        break;
                    }

                    case 3:{
                        
                        int num;
                        printf("Numero do pedido: ");

                        if(lerInteiro(&num) == 1){
                            TPedido *p = buscarPedidoNumero(&pedidos, num);

                            if(p == NULL){
                                printf("Pedido nao encontrado.\n");
                            }
                            else{
                                exibirPedido(p);
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }
                        break;
                    }

                    case 4:{
                        printf("Digite o CPF do cliente: ");
                        char *cpf = lerTexto();
                        if(cpf != NULL){
                            listarPedidosCliente(&pedidos, cpf);
                            free(cpf);
                        }
                        break;
                    }

                    case 0:
                        pausa = 0; 
                        break;  
                    
                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            }

            case 4:{
                printf("\n=============================\n");
                printf("            PIZZA              ");
                printf("\n=============================\n");
                printf("1. Cadastrar pizza\n");
                printf("2. Listar pizzas\n");          
                printf("3. Buscar pizza por nome\n");
                printf("4. Alterar pizza\n");
                printf("5. Excluir pizza\n");
                printf("6. Buscar pizza por codigo\n");
                printf("7. Listar pizza por categoria\n");
                printf("8. Listar pizza por tamanho\n");
                printf("0. Voltar\n");
                printf("-----------------------------\n");
                printf("Escolha uma opcao: ");

                int opcaoPizza;

                int r = lerInteiro(&opcaoPizza);

                if(r == -1){
                    opcao = 0;
                    break;
                }

                if(r == 0){
                    printf("Entrada invalida!\n");
                    break;
                }

                switch (opcaoPizza)
                {
                    case 1:{
                        if(cadastrarPizza(&listaP)){
                            salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                        }

                        break;
                    }

                    case 2:{
                        listarPizzas(&listaP);
                        break;
                    }

                    case 3:{
                        printf("Digite o nome da pizza: ");
                        char *nome = lerTexto();

                        if(nome != NULL){
                            buscarPizzaNome(&listaP, nome);
                            free(nome);
                        }
                        break;
                    }

                    case 4:{
                        int codigo;
                        printf("Digite o codigo da pizza: ");

                        if(lerInteiro(&codigo) == 1){
                            if(alterarPizza(&listaP, codigo)){
                                salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }
                        
                        break;
                    }

                    case 5:{
                        int codigo;
                        printf("Digite o codigo da pizza: ");

                        if(lerInteiro(&codigo) == 1){
                            if(excluirPizzaSegura(&listaP, &pedidos, codigo)){
                                salvarTudo(&listaC, &listaP, &listaB, &pedidos);
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }

                        break;
                    }
                    
                    case 6:{
                        int codigo;
                        printf("Digite o codigo da pizza: ");

                        if(lerInteiro(&codigo) == 1){
                            TPizza *p = buscarPizzaCodigo(&listaP, codigo);

                            if(p == NULL){
                                printf("Pizza nao encontrada.\n");
                            }
                            else{
                                exibirPizza(p);
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }

                        break;
                    }

                    case 7:{
                        int cat;
                        printf("Categoria (1 - Tradicional 2 - Especial 3 - Nobre): ");

                        if(lerInteiro(&cat) == 1){
                            switch(cat){
                                case 1: listarPizzasPorCategoria(&listaP, TRADICIONAL); break;
                                case 2: listarPizzasPorCategoria(&listaP, ESPECIAL); break;
                                case 3: listarPizzasPorCategoria(&listaP, NOBRE); break;
                                default: printf("Opcao invalida!\n");
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }

                        break;
                    }

                    case 8:{
                       int tam; 
                       printf("Tamanho (1 - Pequena 2 - Media 3 - Grande): ");

                       if(lerInteiro(&tam) == 1){
                            switch(tam){
                                case 1: listarPizzasPorTamanho(&listaP, PEQUENA); break;
                                case 2: listarPizzasPorTamanho(&listaP, MEDIA); break;
                                case 3: listarPizzasPorTamanho(&listaP, GRANDE); break;
                                default: printf("Opcao invalida!\n");
                            }
                        }
                        else{
                            printf("Entrada invalida!\n");
                        }

                        break;
                    }

                    case 0:
                        pausa = 0; 
                        break;

                    default:
                        printf("Opcao invalida!\n");
                        break;
                }
                break;
            }

            case 0:
                pausa = 0;
                break;

            default: {
                printf("Opcao invalida!\n");
                break;
            }
        }

        if(pausa && opcao != 0){
            pausar();
        }
    }
    
    salvarTudo(&listaC, &listaP, &listaB, &pedidos);

    liberarClientes(&listaC);
    liberarBebidas(&listaB);
    liberarPizzas(&listaP);
    liberarPedidos(&pedidos);

    return 0;
}

static void exibirMenuOpcao(void) {
    printf("\n=============================\n");
    printf("        PIZZARIA IFPR       \n");
    printf("=============================\n");
    printf("1. Cliente\n");
    printf("2. Bebida\n");
    printf("3. Pedido\n");
    printf("4. Pizza\n");
    printf("0. Sair\n");
    printf("-----------------------------\n");
    printf("Escolha uma opcao: ");
}

static int salvarTudo(const TClientes *clientes, const TListaPizzas *pizzas, const TListaBebidas *bebidas, const TPedidos *pedidos){

    int ok = 1;

    if(!salvarClientes(clientes, ARQ_CLIENTES)){
        ok = 0;
    }

    if(!salvarPizzas(pizzas, ARQ_PIZZAS)){
        ok = 0;
    }

    if(!salvarBebidas(bebidas, ARQ_BEBIDAS)){
        ok = 0;
    }

    if(!salvarPedidos(pedidos, ARQ_PEDIDOS)){
        ok = 0;
    }

    if(!ok){
        printf("Erro ao salvar os dados.\n");
    }
    return ok;
}
