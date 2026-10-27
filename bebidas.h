#ifndef BEBIDAS_H
#define BEBIDAS_H


typedef enum{
    NAO_ALCOOLICA,
    ALCOOLICA
} TTipoBebida;

typedef struct{
    char *nome;
    float preco;
    TTipoBebida tipo;
    int codigoBebida;
    float teorAlcoolico;
    int volumeMl;
} TBebida;

typedef struct{
    TBebida *itens;
    int quantidade;
} TListaBebidas;

//protótipos das funções das bebidas

void inicializarBebidas(TListaBebidas *bebidas);
int cadastrarBebida(TListaBebidas *bebidas);
void listarBebidas(const TListaBebidas *bebidas);
void listarBebidasPorTipo(const TListaBebidas *bebidas, TTipoBebida tipo);
TBebida *buscarBebidaCodigo(TListaBebidas *bebidas, int codigo);
void buscarBebidaNome(TListaBebidas *bebidas, const char *nome);
int alterarBebida(TListaBebidas *bebidas, int codigo);
int excluirBebida(TListaBebidas *bebidas, int codigo);
void liberarBebidas(TListaBebidas *bebidas);

//aux
const char *nomeTipo(TTipoBebida tipo);
void exibirBebida(const TBebida *bebida);

#endif // BEBIDAS_H