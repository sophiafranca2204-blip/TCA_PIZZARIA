#include <stdio.h>
#include "data.h"
#include "util.h"

int lerData(TData *data) {

    int r;

    do{

        data->dia = 0;
        data->mes = 0;
        data->ano = 0;

        printf("Digite o dia: ");
        r = lerInteiro(&data->dia);

        if(r == -1){
            return -1;
        }

        if(r == 0){
            printf("Entrada invalida!\n");
            continue;
        }

        printf("Digite o mes: ");
        r = lerInteiro(&data->mes);

        if(r == -1){
            return -1;
        }

        if(r == 0){
            printf("Entrada invalida!\n");
            continue;
        }

        printf("Digite o ano: ");
        r = lerInteiro(&data->ano);

        if(r == -1){
            return -1;
        }

        if(r == 0){
            printf("Entrada invalida!\n");
            continue;
        }

        if(!validarData(*data)){
            printf("Data invalida!\n");
        }
    } while(!validarData(*data));

    return 1;
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