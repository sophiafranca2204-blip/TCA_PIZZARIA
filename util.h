#include <stdio.h> 
#ifndef UTIL_H
#define UTIL_H

char *lerTexto(void);
void limparBuffer(void);
int lerInteiro(int *valor);
int lerDecimal(float *valor);
char *lerLinhaArquivo(FILE *arq);
int lerInteiroArquivo(FILE *arq, int *valor);
int lerDecimalArquivo(FILE *arq, float *valor);

void limparTela(void);
void pausar(void);

void escreverSeparador(FILE *arq);
int lerSeparadorArquivo(FILE *arq);

#endif