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

TBebida *buscarBebidaCodigo(TListaBebidas *bebidas, int codigo){
    
    for(int i = 0; i < bebidas->quantidade; i++){

        if(bebidas->itens[i].codigoBebida == codigo){

            return &bebidas->itens[i];
        }
    }

    return NULL;
}

void buscarBebidaNome(TListaBebidas *bebidas, const char *nome){

    int encontrou = 0;

    for(int i = 0; i < bebidas->quantidade; i++){
        if(strstr(bebidas->itens[i].nome, nome)){
            printf("Bebida encontrada\n");
            exibirBebida(&bebidas-> itens[i]);
            encontrou = 1;

        }
    }
}

int alterarBebida(TListaBebidas *bebidas, int codigo){
     int indice = -1;

    for(int i = 0; i < bebidas->quantidade; i++){
        if(bebidas->itens[i].codigoBebida == codigo){
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("Bebida nao encontrada.\n");
        return 0;
    }

    TBebida *bebida = &bebidas->itens[indice];

    int op = -1;
    int r;

    do{

        printf("\n ---- Menu de alteração de Bebida ---- \n");
        printf("1. Alterar nome\n");
        printf("2. Alterar codigo\n");
        printf("3. Alterar tipo\n");
        printf("5. Alterar preco\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");

        r = lerInteiro(&op);

        if(r == -1){
            return 0;
        }

        if(r == 0){
            printf("Entrada invalida!\n");
            op = -1; // Reinicia a opção para forçar a repetição do loop
            continue;
        }


        switch(op){
        
            case 1:
                printf("Digite o novo nome: ");

                char *novoNome = lerTexto();

                if(novoNome == NULL){
                    printf("Erro ao alocar memoria para o novo nome.\n");
                    return 0;
                }

                if(strlen(novoNome) == 0){
                    printf("Nome da bebida nao pode ser vazio.\n");
                    free(novoNome);
                    break;
                }

                free(bebida->nome);
                bebida->nome = novoNome;
                break;
            
            case 2: {
            printf("Digite a novo codigo:\n");

            TBebida newCod;

            if(lerInteiro(&newCod) != 1){
                return 0;
            }

            bebida-> codigoBebida = newCod.codigoBebida;
            break;
            }

            case 3:{
                int opcaoTip = 0;
                do{
                    printf("\nEscolha a novo tipo:\n");
                    printf("1 - NAO_ALCOOLICA\n2 - ALCOOLICA\n ");

                    r = lerInteiro(&opcaoTip);

                    if(r == -1){
                        return 0;
                    }

                    if(r == 0){
                        printf("Entrada invalida!\n");
                        opcaoTip = 0; // Reinicia a opção para forçar a repetição do loop
                        continue;
                    }

                    switch(opcaoTip){
                        case 1: bebida->tipo = NAO_ALCOOLICA; break;
                        case 2: bebida->tipo = ALCOOLICA; break;
                        default: printf("Opcao invalida!\n");
                    }
                } while(opcaoTip < 1 || opcaoTip > 2);

                break;
            }


            case 5: {
                
                float novoPreco = -1;

                do{

                    printf("Digite o novo preco da bebida: ");

                    r = lerDecimal(&novoPreco);

                    if(r == -1){
                        return 0;
                    }

                    if(r == 0){
                        printf("Preco invalido! Digite um valor numerico positivo.\n");
                        novoPreco = -1; // Reinicia o preço para forçar a repetição do loop
                        continue;
                    }

                    if(novoPreco <= 0){
                        printf("Preco invalido! Digite um valor positivo.\n");
                    }
                } while(novoPreco <= 0);

                bebida->preco = novoPreco;
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

int excluirBebida(TListaBebidas *bebidas, int codigo){

     int indice = -1;

    for(int i = 0; i < bebidas->quantidade; i++){
        if(bebidas->itens[i].codigoBebida == codigo){
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("Bebida nao encontrada.\n");
        return 0;
    }
    bebidas->quantidade--;

    if(bebidas->quantidade == 0){
        free(bebidas->itens);
        bebidas->itens = NULL;
    }
    else{
        TBebida *temp = realloc(bebidas->itens, bebidas->quantidade *sizeof(TBebida));

        if(temp == NULL){
            printf("Erro ao alocar memoria para as bebidas.\n");
            return 0;
        }

       bebidas->itens = temp;
    }
    return 1;
}

void liberarBebidas(TListaBebidas *bebidas){

    for(int i = 0; i < bebidas->quantidade; i++){
        free(bebidas->itens[i].nome);
    }

    free(bebidas->itens);

    bebidas->itens = NULL;
    bebidas->quantidade = 0;
}