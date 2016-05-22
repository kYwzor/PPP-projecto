#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

int compara_datas(Data *d1, Data *d2){
    int a, b;
    a=(d1->ano)*10000000000+(d1->mes)*100000000+(d1->dia)*1000000+(d1->hora)*10000+(d1->min)*100+(d1->seg);
    b=(d2->ano)*10000000000+(d2->mes)*100000000+(d2->dia)*1000000+(d2->hora)*10000+(d2->min)*100+(d2->seg);
    if (a>b) return 1;
    else if (a<b) return -1;
    else return 0;
}

void imprime_viagem(Viagem *viagem){
    printf("%s\t%d do %d de %d às %d hora e %d minutos.\n",viagem->destino, (viagem->partida)->dia, (viagem->partida)->mes,(viagem->partida)->ano, (viagem->partida)->hora, (viagem->partida)->min);
}

void imprime_utilizador(Utilizador *utilizador){
    printf("Nome: %s\tNúmero de CC:%d", utilizador->nome, utilizador->CC);
}

void regista_viagem(Lista_viagens lista_principal){
    char destino[100];
    int vagas;
    Data *data_partida;
    data_partida=(Data*) malloc(sizeof(Data));

    data_partida->seg=0;
    printf("Destino da nova viagem: ");  gets(destino);
    printf("Número de vagas da nova viagem: "); scanf("%d", &vagas);
    printf("Data de partida [dia / mes / ano]: "); scanf("%d %d %d", &(data_partida->dia), &(data_partida->mes), &(data_partida->ano));
    printf("Hora da partida [hora / min]: "); scanf("%d %d", &(data_partida->hora), &(data_partida->min));
    getchar();
    insere_lista_principal_viagens(lista_principal, data_partida, vagas, destino);
}

void procura_lista_principal_viagens (Lista_viagens lista, Data *chave, Lista_viagens *ant, Lista_viagens *actual){
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && compara_datas(((*actual)->viagem)->partida,chave)==-1){
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && compara_datas(((*actual)->viagem)->partida,chave)!=0)
        *actual = NULL; /* Se elemento não encontrado*/
}

void insere_lista_principal_viagens (Lista_viagens lista, Data *partida, int vagas, char *destino){
    Lista_viagens no;
    Lista_viagens ant, inutil;
    no = (Lista_viagens) malloc (sizeof (Lista_viagens_node));
    if (no != NULL) {
        (no->viagem)-> partida = partida;
        (no->viagem)-> vagas = vagas;
        (no->viagem)-> destino = strdup(destino);
        procura_lista_principal_viagens(lista, partida, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
        printf("Viagem inserida com sucesso!\n");
    }
}

char* devolve_nome(){
    char *nome;
    int contador=0, i=0, invalido;

    nome=(char*) malloc(MAX_STRING*sizeof(char));

    printf("Insira o nome do cliente: ");
    do{
        invalido=0;
        gets(nome);
        retira_enter(nome);
        while(nome[i] != '\0'){
            if((nome[i]>='A' && nome[i]<='Z') || (nome[i]>='a' && nome[i]<='z') || nome[i] == ' ')
                contador++;
            i++;
        }
        if(nome[0] == ' ' || nome[0] == '\0' || nome[strlen(nome)-1] == ' ' || contador != i){
            printf("Nome inválido. Insira de novo.\n");
            invalido=1;
        }
    }while(invalido==1);

    return nome;
}

int devolve_cc(){
    char cc[50];
    int ncc = 0, i, aux=0;

    printf("Insira o número de cartão de cidadão do cliente (8 dígitos): ");
    gets(cc);
    retira_enter(cc);


    for(i=0; cc[i] != '\0'; i++){
        if(isdigit(cc[i]))
            aux++;
    }
    while(strlen(cc)!=8 || aux != 8){
        aux = 0;
        printf("Número de Cartão de Cidadão inválido. Insira de novo:");
        gets(cc);
        retira_enter(cc);

        for(i=0; cc[i] != '\0'; i++){
            if(isdigit(cc[i]))
                aux++;
        }
    }
    /*passa de char para int*/
    ncc = atoi(cc);
    return ncc;
}

void regista_cliente(Lista_utilizadores lista_principal){
    char *nome;
    int CC;
    printf("Nome do cliente: ");  nome=devolve_nome();
    printf("Número do cartão de cidadão: "); CC=devolve_cc();
    insere_lista_principal_utilizadores(lista_principal, nome, CC);
}

void insere_lista_principal_utilizadores(Lista_utilizadores lista_principal, char *nome, int CC){
    Lista_utilizadores no;
    no = (Lista_utilizadores) malloc (sizeof (Lista_utilizadores_node));
    while(lista_principal->next!=NULL){
        lista_principal=lista_principal->next;
    }
    (no->utilizador)-> nome = nome;
    (no->utilizador)-> CC = CC;
    no->next=NULL;
    lista_principal->next=no;
}


Viagem* escolhe_viagem(Lista_viagens lista_viagens){
    Lista_viagens aux;
    aux=lista_viagens->next;
    int i=0, invalido;
    int opcao;
    system("cls");

    if(aux->next==NULL) printf("Sem viagens disponiveis!\n");
    else{
        printf("Escolha Viagem:\n");
        while(aux->next!=NULL){
            i++;
            printf("[%d] ", i);
            aux=aux->next;
            imprime_viagem(aux);
        }
    }
    do{
        invalido=0;
        printf("Escolha a opção");
        scanf("%d",&opcao);
        getchar();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inválida. Escolha outra vez.");
        }
    }while(invalido==1);

    aux=lista_viagens->next;
    for(i=1;i<opcao;i++){
        aux=aux->next;
    }
    return aux->viagem;
}

Utilizador* escolhe_utilizador(Lista_utilizadores lista_utilizadores){
    Lista_utilizadores aux;
    aux=lista_utilizadores->next;
    int i, invalido, opcao;
    i=0;
    system("cls");

    if(aux->next==NULL) printf("Sem viagens disponiveis!\n");
    else{
        printf("Escolha Viagem:\n");
        while(aux->next!=NULL){
            i++;
            printf("[%d] ", i);
            aux=aux->next;
            imprime_utilizador(aux->utilizador);
        }
    }
    do{
        invalido=0;
        printf("Escolha a opção");
        scanf("%d",&opcao);
        getchar();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inválida. Escolha outra vez.");
        }
    }while(invalido==1);

    aux=lista_utilizadores->next;
    for(i=1;i<opcao;i++){
        aux=aux->next;
    }
    return aux->utilizador;
}



