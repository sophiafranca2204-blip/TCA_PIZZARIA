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

        printf("Nome da bebida nao pode ser vazio.\n");
        free(bebida.nome);
        return 0;
    }

    //Tipo da bebida

    bebida.teorAlcoolico = 0.0; 

    do{

        printf("\nEscolha o tipo da bebida:\n");
        printf("1 - Nao Alcoolica\n");
        printf("2 - Alcoolica\n");

        r = lerInteiro(&opcaoTipoBebida);

        if(r == -1){

            free(bebida.nome);
            return 0;
        }

        if(r == 0){

            printf("Entrada invalida. Digite um numero inteiro.\n");
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
                
                printf("Opcao invalida. Escolha novamente.\n");
                break;
        }
    } while(opcaoTipoBebida < 1 || opcaoTipoBebida > 2);

    // Teor alcoólico(apenas para bebidas alcoólicas)

    if(bebida.tipo == ALCOOLICA) {

        do{

            printf("Digite o teor alcoolico da bebida (em %%): ");

            r = lerDecimal(&bebida.teorAlcoolico);

            if(r == -1){

                free(bebida.nome);
                return 0;
            }

            if(r == 0){

                printf("Entrada invalida. Digite um numero decimal.\n");
                bebida.teorAlcoolico = -1.0; 
                continue;
            }

            if(bebida.teorAlcoolico < 0.0 || bebida.teorAlcoolico > 100.0){

                printf("Teor alcoolico invalido. Digite um valor entre 0 e 100.\n");
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

            printf("Entrada invalida. Digite um numero inteiro.\n");
            bebida.volumeMl = 0;
            continue;
        }

        if(bebida.volumeMl <= 0){

            printf("Volume invalido. Digite um valor maior que 0.\n");
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

            printf("Entrada invalida. Digite um numero decimal.\n");
            bebida.preco = -1.0; // Reinicia o preço para continuar o loop
            continue;
        }

        if(bebida.preco <= 0.0){

            printf("Preco invalido. Digite um valor maior que zero.\n");
        }
    } while(bebida.preco <= 0.0);

    //guardando a bebida na lista

    TBebida *novaLista = realloc (bebidas->itens, (bebidas->quantidade + 1) * sizeof(TBebida));

    if(novaLista == NULL){

        printf("Erro ao alocar memoria para a nova bebida.\n");
        free(bebida.nome);
        return 0;
    }

    bebidas->itens = novaLista;
    bebidas->itens[bebidas->quantidade] = bebida;
    bebidas->quantidade++;

    printf("Bebida cadastrada com sucesso!\n");
    return 1; // Sucesso
}

const char *nomeTipo(TTipoBebida tipo){

    switch(tipo){

        case NAO_ALCOOLICA:
            return "Nao Alcoolica";

        case ALCOOLICA:
            return "Alcoolica";

        default:
            return "Tipo desconhecido";
    }
}

void exibirBebida(const TBebida *bebida){

    printf("Nome: %s\n", bebida->nome);
    printf("Codigo: %d\n", bebida->codigoBebida);
    printf("Tipo: %s\n", nomeTipo(bebida->tipo));

    if(bebida->tipo == ALCOOLICA) {
        printf("Teor Alcoolico: %.1f%%\n", bebida->teorAlcoolico);
    }

    printf("Volume: %d ml\n", bebida->volumeMl);
    printf("Preco: R$ %.2f\n", bebida->preco);
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

void listarBebidasPorTipo(const TListaBebidas *bebidas, TTipoBebida tipo){

    int encontrou = 0;

    printf("\n--- Bebidas: %s ---\n", nomeTipo(tipo));

    for(int i = 0; i < bebidas->quantidade; i++){

        if(bebidas->itens[i].tipo == tipo){
            exibirBebida(&bebidas->itens[i]);
            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("Nenhuma bebida desse tipo cadastrada.\n");
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

    if(!encontrou){
        printf("Nenhuma bebida encontrada com o nome fornecido.\n");
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
    int alterou = 0;

    do{

        printf("\n ---- Menu de alteracao de Bebida ---- \n");
        printf("1. Alterar nome\n");
        printf("2. Alterar tipo\n");
        printf("3. Alterar preco\n");
        printf("4. Alterar volume\n");
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
        
            case 1:{
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
                alterou = 1;
                break;
            }
            case 2:{
                int opcaoTip = 0;
                do{
                    printf("\nEscolha o novo tipo:\n");
                    printf("1 - Nao alcoolica\n2 - Alcoolica\n");

                    r = lerInteiro(&opcaoTip);

                    if(r == -1){
                        return 0;
                    }

                    if(r == 0){
                        printf("Entrada invalida!\n");
                        opcaoTip = 0; // Reinicia a opção para forçar a repetição do loop
                        continue;
                    }

                    if(opcaoTip < 1 || opcaoTip > 2){

                        printf("Opcao de escolha invalida!\n");
                    }


                } while(opcaoTip < 1 || opcaoTip > 2);

                if(opcaoTip == 1){
                    
                    if(bebida->tipo != NAO_ALCOOLICA){
                        bebida->tipo = NAO_ALCOOLICA;
                        bebida->teorAlcoolico = 0.0;
                        alterou = 1;
                    }
                }

                else if(bebida->tipo != ALCOOLICA){

                    float novoTeor = -1.0;

                    do{

                        printf("Digite o novo teor da bebida (em %%): ");

                        r = lerDecimal(&novoTeor);

                        if(r == -1){
                            return 0;
                        }

                        if(r == 0){
                            printf("Entrada invalida. Digite um numero decimal.\n");
                            novoTeor = -1.0;
                            continue;
                        }

                        if(novoTeor < 0.0 || novoTeor > 100.0){
                            printf("Teor invalido! Digite um valor que esteja entre 0 e 100.\n");
                        }

                    } while(novoTeor < 0.0 || novoTeor > 100.0);

                    bebida->tipo = ALCOOLICA;
                    alterou = 1;
                    bebida->teorAlcoolico = novoTeor;
                }

                break;
            }

            case 3: {
                
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
                alterou = 1;
                break;
            }

            case 4: {
                int novoVolume = -1;

                do{

                    printf("Digite o novo volume da bebida(em ml): ");

                    r = lerInteiro(&novoVolume);

                    if(r == -1){
                        return 0;
                    }

                    if(r == 0){
                        printf("Volume invalido! Digite um valor numerico inteiro.\n");
                        novoVolume = -1; 
                        continue;
                    }

                    if(novoVolume <= 0){
                        printf("Volume invalido! Digite um valor positivo.\n");
                    }
                } while(novoVolume <= 0);

                bebida->volumeMl = novoVolume;
                alterou = 1;
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

    if(alterou){
        printf("Bebida alterada com sucesso!\n");
    }
    else{
        printf("Nenhuma alteracao feita.\n");
    }
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

    free(bebidas->itens[indice].nome);

    for(int i = indice; i < bebidas->quantidade - 1; i++){
        bebidas->itens[i] = bebidas->itens[i + 1];
    }

    bebidas->quantidade--;

    if(bebidas->quantidade == 0){
        free(bebidas->itens); 
        bebidas->itens = NULL;
    }
    else{
        TBebida *temp = realloc(bebidas->itens, bebidas->quantidade *sizeof(TBebida));

        if(temp != NULL){
               bebidas->itens = temp;
        }
    }

    printf("Bebida excluida com sucesso!\n");
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