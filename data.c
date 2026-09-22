#include <stdio.h>
#include "data.h"
#include "util.h"

void lerData(TData *data) {

    do{
        printf("Digite o dia: ");
        scanf("%d", &data->dia);
        limparBuffer(); // Limpa o buffer do teclado para evitar problemas com a leitura de strings

        printf("Digite o mês: ");
        scanf("%d", &data->mes);
        limparBuffer();

        printf("Digite o ano: ");
        scanf("%d", &data->ano);
        limparBuffer();

        // data inválida
        if(!validarData(*data)){
            printf("Data inválida!\n");
        }
    }while(!validarData(*data));
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