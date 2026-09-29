#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "pizza.h"
#include "data.h"
#include "util.h"

void inicializarIngredientes(TIngredientes *ingredientes){

    ingredientes->itens = NULL;
    ingredientes->quantidade = 0;
}
int adicionarIngrediente(TIngredientes *ingredientes, const char *ingrediente){
    
    char **temp;
    temp = realloc(ingredientes->itens, (ingredientes->quantidade + 1) *sizeof(char *));

    if(temp == NULL){
        printf("Erro ao alocar memória para o ingrediente.\n");
        return 0; 
    }

    ingredientes->itens = temp;

    char *copia = malloc(strlen(ingrediente) + 1);

    if(copia == NULL){
        printf("Erro ao alocar memoria para o ingrediente.\n");
        return 0; 
    }

    strcpy(copia, ingrediente); //copia o conteudo de ingredientes para copia

    ingredientes->itens[ingredientes->quantidade] = copia; //guarda o endereço da copia na proxima posição livre do vetor
    ingredientes->quantidade++;

    return 1;
}
void listarIngredientes(const TIngredientes *ingredientes){
    
    if(ingredientes->quantidade == 0){
        printf("Nenhum ingrediente cadastrado.\n");
        return;
    }

    for(int i = 0; i < ingredientes->quantidade; i++){
        printf("Ingrediente: %s\n", ingredientes->itens[i]);
    }
}
void liberarIngredientes(TIngredientes *ingredientes){
    for(int i = 0; i < ingredientes->quantidade; i++){
        free(ingredientes->itens[i]);
    }

    free(ingredientes->itens);

    ingredientes->itens = NULL;
    ingredientes->quantidade = 0;
}


void InicializarPizzas(TListaPizzas *pizzas){

    pizzas->itens = NULL;
    pizzas->quantidade = 0 ;
}
int cadastrarPizza(TListaPizzas *pizzas){
    
    TPizza pizza;
    int maiorCod = 0;
    int opcaoTamanho = 0;
    int opcaoCategoria = 0;

    for(int i = 0; i < pizzas->quantidade; i++){
        if(pizzas->itens[i].codigo > maiorCod){
            maiorCod = pizzas->itens[i].codigo;
        }
    }
    pizza.codigo = maiorCod + 1; 

    printf("Digite o nome da pizza: ");
    pizza.nome = lerTexto();

    if(pizza.nome == NULL){
        printf("Erro ao alocar memoria para o nome da pizza.\n");
        return 0;
    }

    do
    {
        printf("\nEscolha o tamanho da pizza:\n");
        printf("1 - Pequena\n");
        printf("2 - Media\n");
        printf("3 - Grande\n");

        if (scanf("%d", &opcaoTamanho) != 1)
        {
            printf("Entrada invalida!\n");
            limparBuffer();
            continue;
        }

        switch (opcaoTamanho)
        {
            case 1:
                pizza.tamanho = PEQUENA;
                break;

            case 2:
                pizza.tamanho = MEDIA;
                break;

            case 3:
                pizza.tamanho = GRANDE;
                break;

            default:
                printf("Opcao invalida! Escolha entre 1 e 3.\n");
        }

    } while (opcaoTamanho < 1 || opcaoTamanho > 3);

    limparBuffer();
    
    do
    {
        printf("\n Escolha a categoria da pizza:\n");
        printf("1 - TRADICIONAL\n");
        printf("2 - ESPECIAL\n");
        printf("3 - NOBRE\n");

        if (scanf("%d", &opcaoCategoria) != 1)
        {
            printf("Entrada invalida!\n");
            limparBuffer();
            continue;
        }

        switch(opcaoCategoria){
                
            case 1:
                pizza.categoria = TRADICIONAL;
                break;

            case 2:
                pizza.categoria = ESPECIAL;
                break;
                
            case 3: 
                pizza.categoria = NOBRE;
                break;
                
            default:
                printf("Opcao invalida!\n");
                break;
        }

    }while(opcaoCategoria < 1 || opcaoCategoria > 3);

    limparBuffer();

    // ingredientes

    inicializarIngredientes(&pizza.ingredientes);

    char *ingrediente;
    int tam;
    do{
        printf("Digite o ingrediente: ");
        ingrediente = lerTexto();

        if(ingrediente == NULL){
            printf("Erro ao alocar memoria para o ingrediente.\n");
            liberarIngredientes(&pizza.ingredientes);
            free(pizza.nome);
            return 0;
        }

        tam = strlen(ingrediente);

        if(tam != 0){
            adicionarIngrediente(&pizza.ingredientes, ingrediente);
        }

        free(ingrediente);

    }while(tam != 0);

    //preço da pizza

    pizza.preco = -1;

    do{

        printf("Digite o preco da pizza: ");

        if(scanf ( "%f", &pizza.preco) != 1){
            printf("Entrada invalida!\n");
            limparBuffer();
            continue;
        }

        if(pizza.preco <= 0){
            printf("Valor invalido! Digite outro: ");
        }

    } while(pizza.preco <= 0);

    limparBuffer();

    TPizza *temp;

    temp = realloc(pizzas->itens, (pizzas->quantidade +1) *sizeof(TPizza));

    if(temp == NULL){
        printf("Erro ao alocar memoria para a pizza.\n");
        liberarIngredientes(&pizza.ingredientes);
        free(pizza.nome);
        return 0;
    }

    pizzas->itens = temp;

    pizzas->itens[pizzas->quantidade] = pizza;
    pizzas->quantidade++;

    return 1;
}

const char *nomeTamanho(TTamanhoPizza tamanho){

    switch(tamanho){
        case PEQUENA:
            return "Pequena";
        
        case MEDIA:
            return "Media";

        case GRANDE:
            return "Grande";

        default:
            return "Tamanho desconhecido";
    }
}

const char *nomeCategoria(TCategoriaPizza categoria){

    switch(categoria){
        case TRADICIONAL:
            return "Tradicional";

        case ESPECIAL:
            return "Especial";

        case NOBRE:
            return "Nobre";

        default:
            return "Categoria desconhecida";
    }
}
void listarPizzas(const TListaPizzas *pizzas){
 
    if(pizzas->quantidade == 0){
        printf("Nenhuma pizza cadastrada.\n");
        return;
    }

    for(int i = 0; i < pizzas->quantidade; i++){
        TPizza *pizza = &pizzas->itens[i];

        exibirPizza(pizza);
    }
}

void listarPizzasPorTamanho(const TListaPizzas *pizzas, TTamanhoPizza tamanho){
    
    int encontrou = 0;

    for(int i = 0; i < pizzas->quantidade; i++){
        if(pizzas->itens[i].tamanho == tamanho){
            exibirPizza(&pizzas->itens[i]);
            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("Nenhuma pizza encontrada com esse tamanho.\n");
    }
}

void listarPizzasPorCategoria(const TListaPizzas *pizzas, TCategoriaPizza categoria){

    int encontrou = 0;

    for(int i = 0; i < pizzas->quantidade; i++){
        if(pizzas->itens[i].categoria == categoria){
            exibirPizza(&pizzas->itens[i]);
            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("Nenhuma pizza encontrada com essa categoria.\n");
    }
}

void exibirPizza(const TPizza *pizza){

    printf("Nome: %s\n", pizza->nome);
    printf("Codigo: %d\n",pizza->codigo);
    printf("Tamanho: %s\n", nomeTamanho(pizza->tamanho));
    printf("Categoria: %s\n", nomeCategoria(pizza->categoria));
    printf("Ingredientes: ");
    listarIngredientes(&pizza->ingredientes);
    printf("Preco: %.2f\n", pizza->preco);
    printf("------------------------\n");
}

TPizza buscarPizzaCodigo(TListaPizzas *pizzas, int codigo){

    for(int i = 0; i < pizzas->quantidade; i++){
        if(pizzas->itens[i].codigo == codigo){
            return pizzas->itens[i];
        }
    }

    TPizza naoEncontrada;
    naoEncontrada.codigo = -1;
    naoEncontrada.nome = NULL;
    naoEncontrada.preco = 0;
    naoEncontrada.tamanho = PEQUENA;
    naoEncontrada.categoria = TRADICIONAL;
    inicializarIngredientes(&naoEncontrada.ingredientes);

    return naoEncontrada;
}

void buscarPizzaNome(TListaPizzas *pizzas, const char *nome){

    int encontrou = 0;

    for(int i = 0; i < pizzas->quantidade; i++){
        if(strstr(pizzas->itens[i].nome, nome) != NULL){
            printf("Pizza encontrada!\n");
            exibirPizza(&pizzas->itens[i]);
            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("Nenhuma pizza foi encontrada com o nome fornecido.\n");
    }
}
int alterarPizza(TListaPizzas *pizzas, int codigo){
    int indice = -1;

    for(int i = 0; i < pizzas->quantidade; i++){
        if(pizzas->itens[i].codigo == codigo){
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("Pizza nao encontrada.\n");
        return 0;
    }

    TPizza *pizza = &pizzas->itens[indice];

    int op = -1;

    do{

        printf("\n ---- Menu de alteração de pizza ---- \n");
        printf("1. Alterar nome\n");
        printf("2. Alterar tamanho\n");
        printf("3. Alterar categoria\n");
        printf("4. Alterar ingredientes\n");
        printf("5. Alterar preco\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");

        if(scanf("%d", &op) != 1){
            printf("Entrada invalida!\n");
            limparBuffer();
            op = -1;
            continue;
        }

        limparBuffer();

        switch(op){
        
            case 1:
                printf("Digite o novo nome: ");

                char *novoNome = lerTexto();

                if(novoNome == NULL){
                    printf("Erro ao alocar memoria para o novo nome.\n");
                    return 0;
                }

                free(pizza->nome);
                pizza->nome = novoNome;
                break;
            
            case 2: {
                int opcaoTam = 0;

                do{
                    printf("\nEscolha o novo tamanho:\n");
                    printf("1 - Pequena\n2 - Media\n3 - Grande\n");

                    if(scanf("%d", &opcaoTam) != 1){
                        printf("Entrada invalida!\n");
                        limparBuffer();
                        continue;
                    }

                    switch(opcaoTam){
                        case 1: pizza->tamanho = PEQUENA; break;
                        case 2: pizza->tamanho = MEDIA; break;
                        case 3: pizza->tamanho = GRANDE; break;
                        default: printf("OPcao invalida!\n");
                    }
                } while(opcaoTam < 1 || opcaoTam > 3);

                limparBuffer();
                break;
            }

            case 3:{
                int opcaoCat = 0;
                do{
                    printf("\nEscolha a nova categoria:\n");
                    printf("1 - Tradicional\n2 - Especial\n3 - Nobre\n");

                    if(scanf("%d", &opcaoCat) != 1){
                        printf("Entrada invalida!\n");
                        limparBuffer();
                        continue;
                    }

                    switch(opcaoCat){
                        case 1: pizza->categoria = TRADICIONAL; break;
                        case 2: pizza->categoria = ESPECIAL; break;
                        case 3: pizza->categoria = NOBRE; break;
                        default: printf("Opcao invalida!\n");
                    }
                } while(opcaoCat < 1 || opcaoCat > 3);

                limparBuffer();
                break;
            }

            case 4: {
                liberarIngredientes(&pizza->ingredientes);

                char *ingrediente;
                int tam;

                do{
                    printf("Digite o ingrediente: ");
                    ingrediente = lerTexto();
                    
                    if(ingrediente == NULL){
                        printf("Erro ao alocar memoria para o ingrediente.\n");
                        return 0;
                    }

                    tam = strlen(ingrediente);

                    if(tam != 0){
                        adicionarIngrediente(&pizza->ingredientes, ingrediente);
                    }

                    free(ingrediente);
                } while(tam != 0);

                break;
            }

            case 5: {
                
                float novoPreco = -1;

                do{
                    printf("Digite o novo preco: \n");

                    if(scanf("%f", &novoPreco) != 1){
                        printf("Invalido!\n");
                        limparBuffer();
                        continue;
                    }

                    if(novoPreco <= 0){
                        printf("Preco invalido!\n");
                    }
                    
                } while(novoPreco <= 0);

                limparBuffer();

                pizza->preco = novoPreco;
                break;
            }

            case 0: 
                printf("Voltando ao menu principal.\n");
                break;
            
            default: 
                printf("Opcao invalida!\n");
                break;
        }
    } while(op != 0);

    return 1;
}
int excluirPizza(TListaPizzas *pizzas, int codigo){

    int indice = -1;

    for(int i = 0; i < pizzas->quantidade; i++){
        if(pizzas->itens[i].codigo == codigo){
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("Pizza nao encontrada.\n");
        return 0;
    }

    liberarIngredientes(&pizzas->itens[indice].ingredientes);
    free(pizzas->itens[indice].nome);

    for(int i = indice; i < pizzas->quantidade - 1; i++){
        pizzas->itens[i] = pizzas->itens[i + 1];
    }

    pizzas->quantidade--;

    if(pizzas->quantidade == 0){
        free(pizzas->itens);
        pizzas->itens = NULL;
    }
    else{
        TPizza *temp = realloc(pizzas->itens, pizzas->quantidade *sizeof(TPizza));

        if(temp == NULL){
            printf("Erro ao alocar memoria para as pizzas.\n");
            return 0;
        }

       pizzas->itens = temp;
    }
    return 1;
}
void liberarPizzas(TListaPizzas *pizzas){
    
    for(int i = 0; i < pizzas->quantidade; i++){
        liberarIngredientes(&pizzas->itens[i].ingredientes);
        free(pizzas->itens[i].nome);
    }

    free(pizzas->itens);

    pizzas->itens = NULL;
    pizzas->quantidade = 0;
}
