#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "cliente.h"
#include "util.h"
#include "endereco.h"

// Protótipos das funções auxiliares
int validarCPF(const char *cpf);
int cpfjaExiste(TClientes *clientes, const char *cpf);

void inicializarClientes(TClientes *clientes) {
    clientes-> itens = NULL;
    clientes-> quantidade = 0;
}

int validarCPF(const char *cpf) {
    // Verifica se o CPF tem 11 dígitos
    if (strlen(cpf) != 11) {
        return 0;
    }

    // Verifica se todos os caracteres são dígitos
    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') {
            return 0;
        }
    }

    //Verifica se os digitos são todos iguais

    int todosIguais = 1;

    for(int i = 1; i < 11; i++){
        if(cpf[i] != cpf[0]){
            todosIguais = 0;
            break;
        }
    }

    if(todosIguais){
        return 0;
    }

    // Validar ultimos dois digitos do cpf
    int soma = 0;

    for(int i = 0; i < 9; i++){
        soma += (cpf[i] - '0') * (10 - i);
    }

    int digito1 = (soma * 10) % 11;
    if (digito1 == 10) digito1 = 0;

    int soma2 = 0;
    for(int i = 0; i < 10; i++){
        soma2 += (cpf[i] - '0') * (11 - i);
    }

    int digito2 = (soma2 * 10) % 11;
    if (digito2 == 10) digito2 = 0;

    if (cpf[9] - '0' != digito1 || cpf[10] - '0' != digito2) {
        return 0;
    }

    return 1; // CPF válido
}

int cpfjaExiste(TClientes *clientes, const char *cpf) {
    
    for (int i = 0; i < clientes->quantidade; i++) {
        if (strcmp(clientes->itens[i].cpf, cpf) == 0) {
            return 1; // CPF já existe
        }
    }
    return 0; 
}

void exibirCPF(const char *cpf){
    printf("%.3s.%.3s.%.3s-%.2s\n", cpf, cpf + 3, cpf + 6, cpf + 9);
}

void exibirCliente(const TCliente *cliente){

    printf("Nome: %s\n", cliente->nome);
    printf("CPF: ");
    exibirCPF(cliente->cpf);

    printf("Data de nascimento: ");
    exibirData(cliente->dataNascimento);

    printf("Data de Cadastro: ");
    exibirData(cliente->dtCadastro);

    if(cliente->possuiCompra){
        printf("Primeira Compra: ");
        exibirData(cliente->PrimeiraCompra);

        printf("Ultima compra: ");
        exibirData(cliente->UltimaCompra);
    }

    printf("Endereco do cliente:\n");

    printf("Logradouro: %s\n", cliente->endereco.logradouro);
    printf("Número: %s\n", cliente->endereco.numero);
    printf("Complemento: %s\n", cliente->endereco.complemento);
    printf("Bairro: %s\n", cliente->endereco.bairro);
    printf("Cidade: %s\n", cliente->endereco.cidade);
    printf("Estado: %s\n", cliente->endereco.estado);
    printf("CEP: ");
    exibirCEP(cliente->endereco.cep);
    printf("-------------------------\n");

}

int cadastrarCliente(TClientes *clientes){

    printf("Digite o CPF do cliente (somente numeros): ");
    char *cpfDigitado = lerTexto();

    if(cpfDigitado == NULL){
        printf("Erro ao ler memoria para o CPF.\n");
        return 0;
    }

    if(!validarCPF(cpfDigitado)){
        printf("CPF invalido.\n");
        free(cpfDigitado);
        return 0;
    }

    if(cpfjaExiste(clientes, cpfDigitado)){
        printf("CPF já cadastrado.\n");
        free(cpfDigitado);
        return 0;
    }

    TCliente *temp = realloc(clientes->itens, (clientes->quantidade + 1) *sizeof(TCliente));

    if(temp == NULL){
        printf("Erro ao alocar memoria para o novo cliente.\n");
        free(cpfDigitado);
        return 0;
    }

    clientes->itens = temp;
    TCliente *novoCliente = &clientes->itens[clientes->quantidade];

    strncpy(novoCliente->cpf, cpfDigitado, 11);
    novoCliente->cpf[11] = '\0';
    free(cpfDigitado);

    printf("Digite o nome do cliente: ");
    novoCliente->nome = lerTexto();

    if(novoCliente->nome == NULL){
        printf("Erro ao ler o nome do cliente.\n");
        return 0;
    }

    if(strlen(novoCliente->nome) == 0){
        printf("Nome do cliente não pode ser vazio.\n");
        free(novoCliente->nome);
        return 0;
    }

    novoCliente->possuiCompra = 0;

    printf("Digite a data de nascimento do cliente:\n");

    if(lerData(&novoCliente->dataNascimento) != 1){
        free(novoCliente->nome);
        return 0;
    }

    printf("Digite o endereco do cliente:\n");

    if(lerEndereco(&novoCliente->endereco) != 1){
        free(novoCliente->nome);
        return 0;
    }

    printf("Digite a data de cadastro do cliente:\n");

    if(lerData(&novoCliente->dtCadastro) != 1){
        liberarEndereco(&novoCliente->endereco);
        free(novoCliente->nome);
        return 0;
    }

    clientes->quantidade++;

    printf("Cliente %s cadastrado com sucesso! CPF: ", novoCliente->nome);
    exibirCPF(novoCliente->cpf);

    return 1;
}
void listarClientes(TClientes *clientes){

    if(clientes->quantidade == 0){
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for(int i = 0; i < clientes->quantidade; i++){
        
        TCliente *cliente = &clientes->itens[i];

        exibirCliente(cliente);
    }
}
TCliente *buscarClienteCPF(TClientes *clientes, const char *cpf){

    for(int i = 0; i < clientes->quantidade; i++){
        if(strcmp(clientes->itens[i].cpf, cpf) == 0){
            return &clientes->itens[i];
        }
    }

    return NULL;
}
void buscarClienteNome(TClientes *clientes, const char *nome){

    int encontrou = 0;
    
    for(int i = 0; i < clientes->quantidade; i++){

        if(strstr(clientes->itens[i].nome, nome) != NULL){

            printf("Cliente encontrado:\n");
            exibirCliente(&clientes->itens[i]);

            encontrou = 1;
        }
    }

    if(!encontrou){
        printf("Nenhum cliente encontrado com o nome fornecido.\n");
    }
}


int alterarCliente(TClientes *clientes, const char *cpf){

    printf("Alterar cliente com CPF: %s\n", cpf);

    TCliente *cliente = buscarClienteCPF(clientes, cpf);

    if(cliente == NULL){
        printf("Cliente não encontrado.\n");
        return 0;
    }

    int opcao = -1;

    do{

        printf("\n ---- Menu de Alteração de Cliente ----\n");
        printf("1. Alterar nome\n");
        printf("2. Alterar data de nascimento\n");
        printf("3. Alterar endereço\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");

        int r = lerInteiro(&opcao);

        if(r == -1){
            return 0;
        }

        if(r == 0){
            printf("Entrada invalida!\n");
            opcao = -1;
            continue;
        }

        switch(opcao){

        case 1: {
            printf("Digite o novo nome: ");

            char *novoNome = lerTexto();

            if(novoNome == NULL){
                printf("Erro ao ler o novo nome.\n");
                return 0;
            }

            if(strlen(novoNome) == 0){
                printf("O nome nao pode ser vazio. Nome mantido.\n");
                free(novoNome);
                break;
            }

            free(cliente->nome);
            cliente->nome = novoNome;
            break;
        }

        case 2: {
            printf("Digite a nova data de nascimento:\n");

            TData novaData;

            if(lerData(&novaData) != 1){
                return 0;
            }

            cliente->dataNascimento = novaData;
            break;
        }

        case 3: {
            printf("Digite o novo endereço:\n");

            TEndereco novoEndereco;

            if(lerEndereco(&novoEndereco) != 1){
                return 0;
            }

            liberarEndereco(&cliente->endereco);
            cliente->endereco = novoEndereco;
            break;
        }

        case 0:
            printf("Voltando ao menu principal.\n");
            break;

        default:
            printf("Opção inválida.\n");
            break;
        }

    } while(opcao != 0);

    return 1;
}

int excluirCliente(TClientes *clientes, const char *cpf){

    int indice = -1;

    for(int i = 0; i < clientes->quantidade; i++){
        if(strcmp(clientes->itens[i].cpf, cpf) == 0){
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("Cliente não encontrado.\n");
        return 0;
    }

    liberarEndereco(&clientes->itens[indice].endereco);
    free(clientes->itens[indice].nome);

    for(int i = indice; i < clientes->quantidade - 1; i++){
        clientes->itens[i] = clientes->itens[i + 1];
    }

    clientes->quantidade--;

    if(clientes->quantidade == 0){
        free(clientes->itens);
        clientes->itens = NULL;
    }
    else{

        TCliente *temp = realloc(clientes->itens, clientes->quantidade *sizeof(TCliente)); //realoca a memória para o tamanho correto

        if(temp == NULL){
            printf("Erro ao realocar memória para os clientes.\n");
            return 0;
        }

        clientes->itens = temp; //atualiza para o novo endereço de memória
    }
    return 1;
}

void atualizarCompraCliente(TClientes *clientes, const char * cpf, TData data){

    TCliente *cliente = buscarClienteCPF(clientes, cpf);

    if(cliente == NULL){
        printf("Cliente não encontrado.\n");
        return;
    }
    if(cliente->possuiCompra == 0){

        cliente->PrimeiraCompra = data;
        cliente->UltimaCompra = data;
        cliente->possuiCompra = 1;
    }
    else{

        if(compararDatas(data, cliente->UltimaCompra) > 0){
            cliente->UltimaCompra = data;
        }
    }
}
void liberarClientes(TClientes *clientes){

    for(int i = 0; i < clientes->quantidade; i++){

        liberarEndereco(&clientes->itens[i].endereco);
        free(clientes->itens[i].nome);
    }

    free(clientes->itens);

    clientes->itens = NULL;
    clientes->quantidade = 0;
}