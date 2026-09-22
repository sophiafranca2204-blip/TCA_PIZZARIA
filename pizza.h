#ifndef PIZZA_H
#define PIZZA_H

typedef enum{
    PEQUENA,
    MEDIA,
    GRANDE
} TTamanhoPizza;

typedef enum{
    TRADICIONAL,
    ESPECIAL,
    NOBRE
} TCategoriaPizza;

typedef struct{
    char **itens;
    int quantidade;
} TIngredientes;

typedef struct{
    int codigo;
    char *nome;
    TTamanhoPizza tamanho;
    TCategoriaPizza categoria;
    TIngredientes ingredientes;
    float preco;
} TPizza;

typedef struct{
    TPizza *itens;
    int quantidade;
} TListaPizzas;

typedef struct {
    int codigoPizza;
    int quantidade;
    float precoUnitario;
    float subtotal;
} TPizzaPedido;

typedef struct{
    TPizzaPedido *itens;
    int quantidade;
} TListaPizzaPedido;

// Protótipos das funções dos ingredientes

void inicializarIngredientes(TIngredientes *ingredientes);
int adicionarIngrediente(TIngredientes *ingredientes, const char *ingrediente);
void listarIngredientes(const TIngredientes *ingredientes);
void liberarIngredientes(TIngredientes *ingredientes);

// Protótipos das funções da pizza

void InicializarPizzas(TListaPizzas *pizzas);
int cadastrarPizza(TListaPizzas *pizzas);
void listarPizzas(const TListaPizzas *pizzas);
TPizza buscarPizzaCodigo(TListaPizzas *pizzas, int codigo);
void buscarPizzaNome(TListaPizzas *pizzas, const char *nome);
int alterarPizza(TListaPizzas *pizzas, int codigo);
int excluirPizza(TListaPizzas *pizzas, int codigo);
void liberarPizzas(TListaPizzas *pizzas);

//aux
const char *nomeTamanho(TTamanhoPizza tamanho);
const char *nomeCategoria(TCategoriaPizza categoria);

#endif