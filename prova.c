#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_CPF 11
#define MAX_PROFISSAO 100
#define MAX_FONE 10
#define MAX_CONTATOS 100
#define VAZIO 0
#define CONTEM 1

typedef struct
{
    char nome[MAX_NOME];
    char cpf[MAX_CPF];
    char profissao[MAX_PROFISSAO];
    char fone[MAX_FONE];
} Contato;

void imprimirMenu();
void iniciarMenu(Contato agenda[], int *totalContatos);
void adicionarContato(Contato agenda[], int *totalContatos);
void imputarDadosContato(Contato agenda[], int totalContatos);
void imprimirContatoSalvo();
void imprimirAgendaCompleta(Contato agenda[], int totalContatos);
void imprimirContato(Contato contato);
void imprimirProgramaFinalizado();
void imprimirAgendaVazia();
void imprimirAgendaCheia();
void removerContato(Contato agenda[], int *totalContatos);
void atualizarContato(Contato agenda[], int *totalContatos);
void buscarContato(Contato agenda[], int totalContatos);
int buscarIndiceContato(Contato agenda[], int totalContatos);

int main()
{
    int totalContatos = VAZIO;
    Contato agenda[MAX_CONTATOS];

    imprimirMenu();
    iniciarMenu(agenda, &totalContatos);

    return 0;
}

void iniciarMenu(Contato agenda[], int *totalContatos)
{
    char entrada[10];
    int resultScan = -1;

    while (resultScan != 6)
    {
        printf("\n----------------------------------------------------\n");
        printf("---------------------- MENU ------------------------\n");
        printf("1 - Adicionar pessoa na agenda\n");
        printf("2 - Remover pessoa da agenda\n");
        printf("3 - Atualizar pessoa da agenda\n");
        printf("4 - Imprimir pessoas da agenda\n");
        printf("5 - Filtrar e Imprimir pessoa da agenda\n");
        printf("6 - Sair \n");
        printf("Escolha: ");

        fgets(entrada, sizeof(entrada), stdin);
        resultScan = atoi(entrada);

        switch (resultScan)
        {
        case 1:
            adicionarContato(agenda, totalContatos);
            break;
        case 2:
            removerContato(agenda, totalContatos);
            break;
        case 3:
            atualizarContato(agenda, totalContatos);
            break;
        case 4:
            imprimirAgendaCompleta(agenda, *totalContatos);
            break;
        case 5:
            buscarContato(agenda, *totalContatos);
            break;
        case 6:
            break;
        default:
            imprimirOpcaoInvalida();
        }
    }

    imprimirProgramaFinalizado();
}

void imprimirAgendaCompleta(Contato agenda[], int totalContatos)
{
    if (totalContatos == VAZIO)
    {
        imprimirAgendaVazia();
        return;
    }

    printf("\n----------------------------------------------------\n");
    printf("--------------------- Contatos ---------------------\n");

    for (int i = 0; i < totalContatos; i++)
    {
        imprimirContato(agenda[i]);
    }
}

void adicionarContato(Contato agenda[], int *totalContatos)
{
    if (*totalContatos >= MAX_CONTATOS)
    {
        imprimirAgendaCheia();
        return;
    }

    imputarDadosContato(agenda, *totalContatos);
    (*totalContatos)++;
    imprimirContatoSalvo();
}

int buscarIndiceContato(Contato agenda[], int totalContatos)
{
    int indice = -1;
    char nomeContatoAtualizar[MAX_NOME];

    if (totalContatos == VAZIO)
    {
        imprimirAgendaVazia();
        return indice;
    }

    printf("\nDigite o nome do contato: ");
    fgets(nomeContatoAtualizar, sizeof(nomeContatoAtualizar), stdin);
    tratarDadoImputado(nomeContatoAtualizar);

    for (int i = 0; i < totalContatos; i++)
    {
        if (strcmp(agenda[i].nome, nomeContatoAtualizar) == 0)
        {
            indice = i;
            break;
        }
    }

    if (indice == -1)
    {
        imprimirContatoNaoEncontrado();
    }

    return indice;
}

void buscarContato(Contato agenda[], int totalContatos)
{
    int indice = buscarIndiceContato(agenda, totalContatos);

    if (indice != -1)
    {
        imprimirContato(agenda[indice]);
    }
}

void atualizarContato(Contato agenda[], int *totalContatos)
{
    int indice = buscarIndiceContato(agenda, *totalContatos);

    if (indice != -1)
    {
        imputarDadosContato(agenda, indice);
        imprimirContatoSalvo();
    }
}

void removerContato(Contato agenda[], int *totalContatos)
{
    int indice = buscarIndiceContato(agenda, *totalContatos);

    if (indice != -1)
    {
        for (int i = indice; i < *totalContatos - 1; i++)
        {
            agenda[i] = agenda[i + 1];
        }

        (*totalContatos)--;
        imprimirContatoRemovido();
    }
}

void imputarDadosContato(Contato agenda[], int totalContatos)
{
    printf("\n-----------------------------------------------------\n");
    printf("----------------- Adicione os Dados -----------------\n");

    printf("Nome: ");
    fgets(agenda[totalContatos].nome, sizeof(agenda[totalContatos].nome), stdin);
    tratarDadoImputado(agenda[totalContatos].nome);

    printf("Cpf: ");
    fgets(agenda[totalContatos].cpf, sizeof(agenda[totalContatos].cpf), stdin);
    tratarDadoImputado(agenda[totalContatos].cpf);

    printf("Profissao: ");
    fgets(agenda[totalContatos].profissao, sizeof(agenda[totalContatos].profissao), stdin);
    tratarDadoImputado(agenda[totalContatos].profissao);

    printf("Fone: ");
    fgets(agenda[totalContatos].fone, sizeof(agenda[totalContatos].fone), stdin);
    tratarDadoImputado(agenda[totalContatos].fone);
}

void tratarDadoImputado(char *campo)
{
    if (strchr(campo, '\n') == NULL)
    {
        limparBuffer();
    }
    else
    {
        campo[strcspn(campo, "\n")] = '\0';
    }
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void imprimirMenu()
{
    printf("----------------------------------------------------\n");
    printf("---------------- Agenda Eletronica -----------------\n");
    printf("----------------------------------------------------\n\n");
}

void imprimirProgramaFinalizado()
{
    printf("\n----------------------------------------------------\n");
    printf("----------------- Programa Finalizado ---------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirAgendaVazia()
{
    printf("\n-----------------------------------------------------\n");
    printf("------------------- Agenda Vazia --------------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirAgendaCheia()
{
    printf("\n-----------------------------------------------------\n");
    printf("------------------- Agenda Cheia --------------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirContatoSalvo()
{
    printf("\n-----------------------------------------------------\n");
    printf("------------------ Contato Salvo! -------------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirOpcaoInvalida()
{
    printf("\n-----------------------------------------------------\n");
    printf("------------------ Opcao Invalida! ------------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirContatoNaoEncontrado()
{
    printf("\n-----------------------------------------------------\n");
    printf("-------------- Contato nao encontrado! --------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirContatoRemovido()
{
    printf("\n-----------------------------------------------------\n");
    printf("----------------- Contato removido! -----------------\n");
    printf("-----------------------------------------------------\n\n");
}

void imprimirContato(Contato contato)
{
    printf("\nNome --------------------- %s\n", contato.nome);
    printf("Cpf ---------------------- %s\n", contato.cpf);
    printf("Profissao ---------------- %s\n", contato.profissao);
    printf("Fone --------------------- %s\n", contato.fone);
}
