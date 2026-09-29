#ifndef CLIENTE_H
#define CLIENTE_H

#include "endereco.h"
#include "data.h"

typedef struct{
    char *nome;
    char cpf[12];
    TData dataNascimento;
    TEndereco endereco;
    TData dtCadastro;
    TData PrimeiraCompra;
    TData UltimaCompra;
    int possuiCompra;
} TCliente;

typedef struct{
    TCliente *itens;
    int quantidade;
} TClientes;

//protótipos das funções

void exibirCliente(const TCliente *cliente);
void exibirCPF(const char *cpf);
void inicializarClientes(TClientes *clientes);
int cadastrarCliente(TClientes *clientes);
void listarClientes(TClientes *clientes);
TCliente *buscarClienteCPF(TClientes *clientes, const char *cpf);
void buscarClienteNome(TClientes *clientes, const char *nome);
int alterarCliente(TClientes *clientes, const char *cpf);
int excluirCliente(TClientes *clientes, const char *cpf);
void atualizarCompraCliente(TClientes *clientes, const char * cpf, TData data);
void liberarClientes(TClientes *clientes);


#endif