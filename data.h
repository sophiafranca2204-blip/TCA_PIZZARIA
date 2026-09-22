#include <stdio.h>
#include <string.h>
#ifndef DATA_H
#define DATA_H
typedef struct{
    int dia;
    int mes;
    int ano;
} TData;

//Protótipos das funções
void lerData(TData *data);
int validarData(TData data);
int compararDatas(TData data1, TData data2);

#endif