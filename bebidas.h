#ifndef BEBIDAS_H
#define BEBIDAS_H


typedef enum{
    NAO_ALCOOLICA,
    ALCOOLICA
} TTipobebida;

typedef struct{
    char *nome;
    float preco;
    TTipobebida tipo;
    int codigoBebida;
    float teorAlcoolico;
    int volumeMl;
} TBebida;

typedef struct{
    TBebida **bebidas;
    int qtdBebidas;
} TItensBebidas;

typedef struct{
    TBebida *itens;
    int quantidade;
} TListaBebidas;

//protótipos das funções das bebidas

void inicializarBebidas(TListaBebidas *bebidas);
int cadastrarBebida(TListaBebidas *bebidas);
void listarBebidas(const TListaBebidas *bebidas);
TBebida *buscarBebidaCodigo(TListaBebidas *bebidas, int codigo);
void buscarBebidaNome(TListaBebidas *bebidas, const char *nome);
int alterarBebida(TListaBebidas *bebidas, int codigo);
int excluirBebida(TListaBebidas *bebidas, int codigo);
void liberarBebidas(TListaBebidas *bebidas);

//aux
const char *nomeTipo(TTipobebida tipo);
void exibirBebida(const TBebida *bebida);

#endif // BEBIDAS_H