#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "bebidas.h"

void inicializarBebidas(TListaBebidas *bebidas) {
    bebidas->itens = NULL;
    bebidas->quantidade = 0;
}

int cadastrarBebida(TListaBebidas *bebidas){

    TBebida bebida;

    int maiorCodigo = 0;
    int opcaoTipoBebida = 0;
    int r;

    for (int i = 0; i < bebidas->quantidade; i++) {
        if (bebidas->itens[i].codigoBebida > maiorCodigo) {
            maiorCodigo = bebidas->itens[i].codigoBebida;
        }
    }
    
    bebida.codigoBebida = maiorCodigo + 1;

    //Nome

    printf("Digite o nome da bebida: ");
    bebida.nome = lerTexto();

    if(bebida.nome == NULL) {
        printf("Erro ao ler o nome da bebida.\n");
        return 0;
    }

    if(strlen(bebida.nome) == 0){

        printf("Nome da bebida não pode ser vazio.\n");
        free(bebida.nome);
        return 0;
    }

    //Tipo da bebida

    bebida.teorAlcoolico = 0.0; 

    do{

        printf("\nEscolha o tipo da bebida:\n");
        printf("1 - Não Alcoolica\n");
        printf("2 - Alcoolica\n");

        r = lerInteiro(&opcaoTipoBebida);

        if(r == -1){

            free(bebida.nome);
            return 0;
        }

        if(r == 0){

            printf("Entrada inválida. Digite um número inteiro.\n");
            opcaoTipoBebida = 0; // Reinicia a opção para continuar o loop
            continue;
        }

        switch(opcaoTipoBebida){

            case 1: 
        
                bebida.tipo = NAO_ALCOOLICA;
                break;
            
            case 2: 

                bebida.tipo = ALCOOLICA;
                break;

            default:
                
                printf("Opção inválida. Escolha novamente.\n");
                break;
        }
    } while(opcaoTipoBebida < 1 || opcaoTipoBebida > 2);

    // Teor alcoólico(apenas para bebidas alcoólicas)

    bebida.teorAlcoolico = 0.0; // Inicializa o teor alcoólico como 0.0

    if(bebida.tipo == ALCOOLICA) {

        do{

            printf("Digite o teor alcoólico da bebida (em %%): ");

            r = lerDecimal(&bebida.teorAlcoolico);

            if(r == -1){

                free(bebida.nome);
                return 0;
            }

            if(r == 0){

                printf("Entrada inválida. Digite um número decimal.\n");
                bebida.teorAlcoolico = -1.0; 
                continue;
            }

            if(bebida.teorAlcoolico < 0.0 || bebida.teorAlcoolico > 100.0){

                printf("Teor alcoólico inválido. Digite um valor entre 0 e 100.\n");
            }
        } while(bebida.teorAlcoolico < 0.0 || bebida.teorAlcoolico > 100.0);
    }
    // volume da bebida

    bebida.volumeMl = 0; // Inicializa o volume como 0

    do{

        printf("Digite o volume da bebida (em ml): ");

        r = lerInteiro(&bebida.volumeMl);

        if(r == -1){

            free(bebida.nome);
            return 0;
        }

        if(r == 0){

            printf("Entrada inválida. Digite um número inteiro.\n");
            bebida.volumeMl = 0;
            continue;
        }

        if(bebida.volumeMl <= 0){

            printf("Volume inválido. Digite um valor maior que 0.\n");
        }
    } while(bebida.volumeMl <= 0);

    //preço da bebida

    bebida.preco = -1;

    do{

        printf("Digite o preco da bebida: ");

        r = lerDecimal(&bebida.preco);

        if(r == -1){

            free(bebida.nome);
            return 0;
        }

        if(r == 0){

            printf("Entrada inválida. Digite um número decimal.\n");
            bebida.preco = -1.0; // Reinicia o preço para continuar o loop
            continue;
        }

        if(bebida.preco <= 0.0){

            printf("Preço inválido. Digite um valor maior que zero.\n");
        }
    } while(bebida.preco <= 0.0);

    //guardando a bebida na lista

    TBebida *novaLista = realloc (bebidas->itens, (bebidas->quantidade + 1) * sizeof(TBebida));

    if(novaLista == NULL){

        printf("Erro ao alocar memória para a nova bebida.\n");
        free(bebida.nome);
        return 0;
    }

    bebidas->itens = novaLista;
    bebidas->itens[bebidas->quantidade] = bebida;
    bebidas->quantidade++;

    return 1; // Sucesso
}

const char *nomeTipo(TTipobebida tipo){

    switch(tipo){

        case NAO_ALCOOLICA:
            return "Não Alcoólica";

        case ALCOOLICA:
            return "Alcoólica";

        default:
            return "Tipo desconhecido";
    }
}

void exibirBebida(const TBebida *bebida){

    printf("Nome: %s\n", bebida->nome);
    printf("Codigo: %d\n", bebida->codigoBebida);
    printf("Tipo: %s\n", nomeTipo(bebida->tipo));

    if(bebida->tipo == ALCOOLICA) {
        printf("Teor Alcoólico: %.1f%%\n", bebida->teorAlcoolico);
    }

    printf("Volume: %d ml\n", bebida->volumeMl);
    printf("Preço: R$ %.2f\n", bebida->preco);
    printf("-------------------------\n");
}

void listarBebidas(const TListaBebidas *bebidas){
    
    if(bebidas->quantidade == 0) {
        printf("Nenhuma bebida cadastrada.\n");
        return;
    }

    for(int i = 0; i < bebidas->quantidade; i++){
        exibirBebida(&bebidas->itens[i]);
    }
}

void liberarBebidas(TListaBebidas *bebidas){

    for(int i = 0; i < bebidas->quantidade; i++){
        free(bebidas->itens[i].nome);
    }

    free(bebidas->itens);

    bebidas->itens = NULL;
    bebidas->quantidade = 0;
}