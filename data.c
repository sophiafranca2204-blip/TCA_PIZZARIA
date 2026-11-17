#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "util.h"

int lerData(TData *data){

    while(1){

        printf("Digite a data (dd mm aaaa): ");

        char *texto = lerTexto();

        if(texto == NULL){
            return -1; // Erro ao ler o texto
        }

        int dia, mes, ano;
        int n = 0;

        int lidos = sscanf(texto, "%d %d %d%n", &dia, &mes, &ano, &n);

        if(lidos == 3 && texto[n] == '\0'){

            TData temp;
            temp.dia = dia;
            temp.mes = mes;
            temp.ano = ano;

            if(validarData(temp)){
                *data = temp;
                free(texto);
                return 1; // Data válida
            }

            printf("Data invalida! Digite novamente.\n");
        }
        else{
            printf("Formato invalido! Digite novamente.\n");
        }

        free(texto);
    }
}

int validarData(TData data){

    if(data.ano <= 0){
        return 0;
    }

    if(data.mes < 1 || data.mes > 12) {
        return 0;
    }

    if(data.dia < 1 || data.dia > 31){
        return 0;
    }

    //fevereiro

    if(data.mes == 2){

        if((data.ano % 4 == 0 && data.ano % 100 != 0) || (data.ano % 400 == 0)){

            if(data.dia > 29){
                return 0;
            }
        }

        else{

            if(data.dia > 28){
                return 0;
            }
        }
    }

    //meses com 30 dias

    if(data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11){

        if(data.dia > 30){
            return 0;
        }
    }

    return 1;
}

int compararDatas(TData data1, TData data2){

    if(data1.ano < data2.ano){

        return -1;// data1 é menor que data2
    }

    else if(data1.ano > data2.ano){
        
        return 1; // data1 é maior que data2
    }
    else{
        if(data1.mes < data2.mes){
            return -1; // data1 é menor que data2
        }
        else if(data1.mes > data2.mes){
            return 1; // data1 é maior que data2
        }
        else{
            if(data1.dia < data2.dia){
                return -1; // data1 é menor que data2
            }
            else if(data1.dia > data2.dia){
                return 1; // data1 é maior que data2
            }
            else{
                return 0; // datas são iguais
            }
        }
    }
}

void exibirData(TData data){
    printf("%02d/%02d/%04d\n", data.dia, data.mes, data.ano);
}

int lerDataArquivo(FILE *arq, TData *data){

    char *linha = lerLinhaArquivo(arq);

    if(linha == NULL){
        return 0;
    }

    int lidos = sscanf(linha, "%d %d %d", &data->dia, &data->mes, &data->ano);
    free(linha);

    return lidos == 3;
}