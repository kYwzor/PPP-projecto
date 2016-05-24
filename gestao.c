#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

int compara_datas(Data *d1, Data *d2){
    int a, b;
    a=(d1->ano)*100000000+(d1->mes)*1000000+(d1->dia)*10000+(d1->hora)*100+(d1->min);
    b=(d2->ano)*100000000+(d2->mes)*1000000+(d2->dia)*10000+(d2->hora)*100+(d2->min);
    if (a>b) return 1;
    else if (a<b) return -1;
    else return 0;
}

void imprime_viagem(Viagem *viagem){
    printf("%s\t Dia %d do %d de %d �s %d hora e %d minutos.\n",viagem->destino, (viagem->partida)->dia, (viagem->partida)->mes,(viagem->partida)->ano, (viagem->partida)->hora, (viagem->partida)->min);
}

void imprime_utilizador(Utilizador *utilizador){
    printf("Nome: %s\t\t\tN�mero de CC: %d\n", utilizador->nome, utilizador->cc);
}

int verifica_data(int dia, int mes, int ano){
   	if ((dia >= 1) && (mes >= 1 && mes <= 12) && ano>=0){
            if (mes==2){
                if (dia<=28)
                    return 1;
                else if (((ano % 400 == 0) || ((ano % 4 == 0) && (ano % 100 != 0))) && dia==29)
                    return 1;
                else
                    return 0;
            }
            else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && (dia <= 30))
                return 1;
            else if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)&&(dia <=31) )
                return 1;
            else
                return 0;
    }
    else
        return 0;
}

char* devolve_nome(){
    char *nome;
    int contador, i, invalido;

    nome=(char*) malloc(MAX_STRING*sizeof(char));

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
            printf("Nome inv�lido. Insira de novo:\n");
            invalido=1;
        }
    }while(invalido==1);

    return nome;
}

int devolve_cc(Lista_utilizadores lista_utilizadores){
    char cc[50];
    int ncc, i, aux, j;
    Lista_utilizadores aux_l;

    do{
        aux_l=lista_utilizadores;
        printf("Insira o n�mero de cart�o de cidad�o do cliente (8 d�gitos): ");
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

        if (strlen(cc)!=8 || aux != 8)
            printf("N�mero de Cart�o de Cidad�o inv�lido.\n");
        else if (j==1)
            printf("N�mero de Cart�o de Cidad�o j� existente.\n");
    }while(strlen(cc)!=8 || aux != 8 || j==1);

    /*passa de char para int*/

    ncc = atoi(cc);
    return ncc;
}

void regista_viagem(Lista_viagens lista_principal, char* destino, Data* data_partida, int vagas){
    Viagem* viagem;

    viagem=(Viagem*)malloc(sizeof(Viagem));

    viagem->destino=destino;
    viagem->partida=data_partida;
    viagem->vagas=vagas;
    insere_lista_principal_viagens(lista_principal, viagem);
}

void regista_viagem_manual(Lista_viagens lista_principal){
    char* destino;
    int vagas, aux;
    Data* data_partida;

    destino=(char*) malloc(MAX_STRING*sizeof(char));
    data_partida=(Data*) malloc(sizeof(Data));

    printf("Destino da nova viagem: ");
    destino=devolve_nome();

    printf("N�mero de vagas da nova viagem: ");
    scanf("%d", &vagas);
    getchar();

    do{
        printf("Data de partida [dia / mes / ano]: ");
        scanf("%d %d %d", &(data_partida->dia), &(data_partida->mes), &(data_partida->ano));
        if(verifica_data(data_partida->dia, data_partida->mes, data_partida->ano)==0)
            printf("Data inv�lida. Introduza a data novamente!\n");
    }while(verifica_data(data_partida->dia, data_partida->mes, data_partida->ano)==0);

    do{
        aux=0;
        printf("Hora da partida [hora / min]: ");
        scanf("%d %d", &(data_partida->hora), &(data_partida->min));
        if(data_partida->hora<0 && data_partida->hora>23 && data_partida->min<0 && data_partida->min>59){
            aux=1;
            printf("Hora inv�lida. Introduza a hora novamente!\n");
        }
    }while(aux==1);

    regista_viagem(lista_principal, destino, data_partida, vagas);
    printf("Viagem inserida com sucesso!\n");
    getchar();
}

void procura_lista_principal_viagens (Lista_viagens lista, Data *chave, Lista_viagens *ant, Lista_viagens *actual){
    *ant = lista;
    *actual = lista->next;
    while ((*actual) != NULL && compara_datas(((*actual)->viagem)->partida,chave)==-1){
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if ((*actual) != NULL && compara_datas(((*actual)->viagem)->partida,chave)!=0)
        *actual = NULL; /* Se elemento n�o encontrado*/
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
    }
}

void regista_cliente(Lista_utilizadores lista_principal){
    char *nome;
    int cc;
    Utilizador *utilizador;
    printf("Insira o nome do cliente: ");
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
    int i=0, invalido;
    int opcao;

    aux=lista_viagens;
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
        printf("Escolha a op��o: ");
        scanf("%d",&opcao);
        getchar();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Op��o inv�lida. Escolha outra vez.\n");
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
    int i, invalido, opcao;
    i=0;

    system("cls");
    aux=lista_utilizadores;

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
        printf("Escolha a op��o: ");
        scanf("%d",&opcao);
        getchar();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Op��o inv�lida. Escolha outra vez.\n");
        }
    }while(invalido==1);

    aux=lista_utilizadores->next;
    for(i=1;i<opcao;i++){
        aux=aux->next;
    }
    return aux->utilizador;
}

int procura_viagem_de_utilizador(Lista_utilizadores node_ut, Viagem* aux_v){
    Lista_viagens percorre_vgm;
    percorre_vgm=node_ut->vgm_registado;
    while(percorre_vgm->viagem!=aux_v && percorre_vgm->next!=NULL)
        percorre_vgm=percorre_vgm->next;
    if(percorre_vgm->viagem==aux_v)
        return 1;
    else if(percorre_vgm->next==NULL){
        percorre_vgm=node_ut->vgm_espera;
        while(percorre_vgm->viagem!=aux_v && percorre_vgm->next!=NULL)
            percorre_vgm=percorre_vgm->next;
        if(percorre_vgm->viagem==aux_v)
            return -1;
        else
            return 0;
    }
    return 2;
}

void compra_viagem(Lista_utilizadores lista_utilizadores, Lista_viagens lista_viagens){
    Lista_utilizadores node_u, lut_aux;
    Lista_viagens node_v, lvgm_aux;
    Utilizador *aux_u;
    Viagem *aux_v;
    int aux_int, opcao;

    aux_u=escolhe_utilizador(lista_utilizadores);
    aux_v=escolhe_viagem(lista_viagens);

    if(aux_u==NULL || aux_v==NULL) return;

    lut_aux=lista_utilizadores->next;
    lvgm_aux=lista_viagens->next;

    while(aux_u->nome != lut_aux->utilizador->nome && aux_u->cc != lut_aux->utilizador->cc && lut_aux->next!=NULL)
            lut_aux=lut_aux->next;
    while(aux_v->destino != lvgm_aux->viagem->destino && aux_v->partida != lvgm_aux->viagem->partida && lvgm_aux->next!=NULL)
            lvgm_aux=lvgm_aux->next;

    node_u = (Lista_utilizadores) malloc (sizeof (Lista_utilizadores_node));
    node_v = (Lista_viagens) malloc (sizeof (Lista_viagens_node));

    node_u->utilizador=lut_aux->utilizador;
    node_u->next=NULL;
    node_u->vgm_espera=NULL;
    node_u->vgm_registado=NULL;

    node_v->viagem=lvgm_aux->viagem;
    node_v->next=NULL;
    node_v->ut_espera=NULL;
    node_v->ut_registado=NULL;

    aux_int=procura_viagem_de_utilizador(lut_aux, aux_v);
    if(aux_int==1){
        printf("Utilizador j� comprou a viagem [lista de reservas]\n");
        return;
    }
    else if (aux_int==-1){
        printf("Utilizador j� comprou a viagem [lista de espera]\n");
        return;
    }
    else if (aux_int==0){
        if(lvgm_aux->viagem->vagas > 0){
            while(lvgm_aux->ut_registado->next != NULL)
                lvgm_aux->ut_registado=lvgm_aux->ut_registado->next;

            lvgm_aux->ut_registado->next=node_u;

            while(lut_aux->vgm_registado->next != NULL)
                lvgm_aux->ut_registado=lvgm_aux->ut_registado->next;

            lut_aux->vgm_registado->next=node_v;
            lvgm_aux->viagem->vagas=(lvgm_aux->viagem->vagas)-1;
            printf("Compra bem sucedida. Cliente colocado na lista de reservas.\n");
        }
        else{
                do{
                    printf("N�o existem vagas dispon�veis:\n[1] Colocar na lista de espera\n[2] Voltar ao menu\n");
                    scanf("%d", &opcao);
                    getchar();
                    if(opcao==1){
                       while(lvgm_aux->ut_espera->next != NULL)
                                lvgm_aux->ut_espera=lvgm_aux->ut_espera->next;

                            lvgm_aux->ut_espera->next=node_u;

                            while(lut_aux->vgm_espera->next != NULL)
                                lut_aux->vgm_espera=lut_aux->vgm_espera->next;

                            lut_aux->vgm_espera->next=node_v;
                            printf("Compra bem sucedida. Cliente colocado na lista de espera.\n");
                    }
                    else if(opcao!=2)
                        printf("Op��o inv�lida. Escolha de novo.\n");
                }while((opcao!=1) && (opcao!=2));
                return;
        }
    }
}
