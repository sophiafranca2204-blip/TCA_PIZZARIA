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
    int opcaoTamanho;
    int opcaoCategoria;

    for(int i = 0; i < pizzas->quantidade; i++){
        if(pizzas->itens[i].codigo > maiorCod){
            maiorCod = pizzas->itens[i].codigo;
        }
    }
    pizza.codigo = maiorCod + 1; 

    printf("Digite o nome da pizza: ");
    pizza.nome = lerTexto();

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

        printf("Nome: %s\n", pizza->nome);
        printf("Codigo: %d\n",pizza->codigo);
        printf("Tamanho: %s\n", nomeTamanho(pizza->tamanho));
        printf("Categoria: %s\n", nomeCategoria(pizza->categoria));
        printf("Ingredientes: ");
        listarIngredientes(&pizza->ingredientes);
        printf("Preco: %.2f\n", pizza->preco);
        printf("------------------------\n");
    }
}