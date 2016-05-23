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
    printf("%s\t Dia %d do %d de %d às %d hora e %d minutos.\n",viagem->destino, (viagem->partida)->dia, (viagem->partida)->mes,(viagem->partida)->ano, (viagem->partida)->hora, (viagem->partida)->min);
}

void imprime_utilizador(Utilizador *utilizador){
    printf("Nome: %s\t\t\tNúmero de CC: %d\n", utilizador->nome, utilizador->cc);
}

int verifica_data(int dia, int mes, int ano){
   	if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12)){
            if ((dia == 29 && mes == 2) && ((ano % 400 == 0) || (ano % 4 == 0) && (ano % 100 != 0))) {
                return 1;
            }
            if (dia <= 28 && mes == 2){
                return 1;
            }
            if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) {
                return 1;
            }
            if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) {
                return 1;
            }
            else{
                return 0;
            }
      }
       else{
                return 0;
           }
}

void regista_viagem(Lista_viagens lista_principal){
    Viagem* viagem;
    char* destino;
    int vagas, aux;
    Data* data_partida;
    viagem=(Viagem*) malloc(sizeof(Viagem));
    data_partida=(Data*) malloc(sizeof(Data));
    data_partida->seg=0;

    destino=(char*) malloc(MAX_STRING*sizeof(char));

    printf("Destino da nova viagem: ");  gets(destino);
    printf("Número de vagas da nova viagem: "); scanf("%d", &vagas);
    do{
        printf("Data de partida [dia / mes / ano]: "); scanf("%d %d %d", &(data_partida->dia), &(data_partida->mes), &(data_partida->ano));
        if(verifica_data(data_partida->dia, data_partida->mes, data_partida->ano)==0) printf("Data inválida. Introduza a data novamente!");
    }while(verifica_data(data_partida->dia, data_partida->mes, data_partida->ano==0));

    do{
        aux=0;
        printf("Hora da partida [hora / min]: "); scanf("%d %d", &(data_partida->hora), &(data_partida->min));
        if(data_partida->hora>0 && data_partida->hora<24 && data_partida->min>0 && data_partida->min<60){ aux=1; printf("Hora inválida. Introduza a hora novamente!");
    while(aux==1)
        getchar();


    viagem->destino=destino;
    viagem->partida=data_partida;
    viagem->vagas=vagas;
    insere_lista_principal_viagens(lista_principal, viagem);
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

void insere_lista_principal_viagens (Lista_viagens lista, Viagem *viagem){
    Lista_viagens no;
    Lista_utilizadores reg,esp;
    Lista_viagens ant, inutil;
    no = (Lista_viagens) malloc(sizeof (Lista_viagens_node));
    reg = (Lista_utilizadores) malloc(sizeof(Lista_utilizadores_node));
    esp = (Lista_utilizadores) malloc(sizeof(Lista_utilizadores_node));
    no->ut_registado=reg;
    no->ut_espera=esp;
    if (no != NULL) {
        no->viagem=viagem;
        procura_lista_principal_viagens(lista, viagem->partida, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
        printf("Viagem inserida com sucesso!\n");
    }
}

char* devolve_nome(){
    char *nome;
    int contador, i, invalido;

    nome=(char*) malloc(MAX_STRING*sizeof(char));

    printf("Insira o nome do cliente: ");
    do{
        i=0;
        contador=0;
        invalido=0;
        gets(nome);
        retira_enter(nome);
        while(nome[i] != '\0'){
            if((nome[i]>='A' && nome[i]<='Z') || (nome[i]>='a' && nome[i]<='z') || nome[i] == ' ')
                contador++;
            i++;
        }
        if(nome[0] == ' ' || nome[0] == '\0' || nome[strlen(nome)-1] == ' ' || contador != i){
            printf("Nome inválido. Insira de novo:\n");
            invalido=1;
        }
    }while(invalido==1);

    return nome;
}

int devolve_cc(Lista_utilizadores lista_utilizadores){
    char cc[50];
    int ncc, i, aux, j;
    Lista_utilizadores aux_l;
    aux_l=lista_utilizadores;
    do{
        printf("Insira o número de cartão de cidadão do cliente (8 dígitos): ");
        gets(cc);
        retira_enter(cc);

        aux=0;
        j=0;

        for(i=0; cc[i] != '\0'; i++){
            if(isdigit(cc[i]))
                aux++;
        }
        while(aux_l->next!=NULL){
            aux_l=aux_l->next;
            if(aux_l->utilizador->cc==atoi(cc))
                j=1;
        }

        if (strlen(cc)!=8 || aux != 8 || j==1){
            aux_l=lista_utilizadores;
            printf("Número de Cartão de Cidadão inválido.\n");
        }
    }while(strlen(cc)!=8 || aux != 8 || j==1);

    /*passa de char para int*/

    ncc = atoi(cc);
    return ncc;
}

void regista_cliente(Lista_utilizadores lista_principal){
    char *nome;
    int cc;
    Utilizador *utilizador;
    nome=devolve_nome();
    cc=devolve_cc(lista_principal);
    utilizador=(Utilizador*) malloc(sizeof(Utilizador));
    utilizador->nome=nome;
    utilizador->cc=cc;
    insere_lista_principal_utilizadores(lista_principal, utilizador);
    printf("Cliente inserido com sucesso!\n");
}

void insere_lista_principal_utilizadores(Lista_utilizadores lista_principal, Utilizador *utilizador){
    Lista_utilizadores no;
    Lista_viagens reg, esp;
    no = (Lista_utilizadores) malloc (sizeof(Lista_utilizadores_node));
    reg = (Lista_viagens) malloc(sizeof(Lista_viagens_node));
    esp = (Lista_viagens) malloc(sizeof(Lista_viagens_node));
    no->vgm_registado=reg;
    no->vgm_espera=esp;
    while(lista_principal->next!=NULL){
        lista_principal=lista_principal->next;
    }
    no->utilizador=utilizador;
    no->next=NULL;
    lista_principal->next=no;
}


Viagem* escolhe_viagem(Lista_viagens lista_viagens){
    Lista_viagens aux;
    aux=lista_viagens;
    int i=0, invalido;
    int opcao;
    system("cls");

    if(aux->next==NULL){
            printf("Sem viagens disponiveis!\n");
            return NULL;
    }
    else{
        printf("Escolha viagem:\n");
        while(aux->next!=NULL){
            i++;
            printf("[%d] ", i);
            aux=aux->next;
            imprime_viagem(aux->viagem);
        }
    }
    do{
        invalido=0;
        printf("Escolha a opção: ");
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
    aux=lista_utilizadores;
    int i, invalido, opcao;
    i=0;
    system("cls");

    if(aux->next==NULL){
        printf("Sem utilizadores disponiveis!\n");
        return NULL;
    }
    else{
        printf("Escolha utilizador: \n");
        while(aux->next!=NULL){
            aux=aux->next;
            i++;
            printf("[%d] ", i);
            imprime_utilizador(aux->utilizador);
        }
    }
    do{
        invalido=0;
        printf("Escolha a opção: ");
        scanf("%d",&opcao);
        getchar();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inválida.");
        }
    }while(invalido==1);

    aux=lista_utilizadores->next;
    for(i=1;i<opcao;i++){
        aux=aux->next;
    }
    return aux->utilizador;
}

void compra_viagem(Lista_utilizadores lista_utilizadores, Lista_viagens lista_viagens){
    Utilizador *aux_u;
    Viagem *aux_v;
    Lista_utilizadores node_u;
    Lista_viagens node_v;

    aux_u=escolhe_utilizador(lista_utilizadores);
    aux_v=escolhe_viagem(lista_viagens);

    lista_viagens=lista_viagens->next;
    lista_utilizadores=lista_utilizadores->next;

    while(aux_v->destino != lista_viagens->viagem->destino && aux_v->partida != lista_viagens->viagem->partida && lista_viagens->next!=NULL)
            lista_viagens=lista_viagens->next;
    while(aux_u->nome != lista_utilizadores->utilizador->nome && aux_u->cc != lista_utilizadores->utilizador->cc && lista_utilizadores->next!=NULL)
            lista_utilizadores=lista_utilizadores->next;
    node_u = (Lista_utilizadores) malloc (sizeof (Lista_utilizadores_node));
    node_u->utilizador=lista_utilizadores->utilizador;
    node_u->next=NULL;
    node_u->vgm_espera=NULL;
    node_u->vgm_registado=NULL;

    node_v = (Lista_viagens) malloc (sizeof (Lista_viagens_node));
    node_v->viagem=lista_viagens->viagem;
    node_v->next=NULL;
    node_v->ut_espera=NULL;
    node_v->ut_registado=NULL;

    if(lista_viagens->viagem->vagas > 0){
            while(lista_viagens->ut_registado->next != NULL){
                lista_viagens->ut_registado=lista_viagens->ut_registado->next;}

            lista_viagens->ut_registado->next=node_u;

            while(lista_viagens->ut_registado->next != NULL){ 
                lista_viagens->ut_registado=lista_viagens->ut_registado->next;}

            lista_utilizadores->vgm_registado->next=node_v;

    }
    else{
            while(lista_viagens->ut_espera->next != NULL){
                lista_viagens->ut_espera=lista_viagens->ut_espera->next;}

            lista_viagens->ut_espera->next=node_u;

            while(lista_viagens->ut_espera->next != NULL){
                lista_viagens->ut_espera=lista_viagens->ut_espera->next;}

            lista_utilizadores->vgm_espera->next=node_v;
    }

    lista_viagens->viagem->vagas=(lista_viagens->viagem->vagas)-1;
}
