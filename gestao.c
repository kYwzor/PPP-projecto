#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

int compara_datas(Data *d1, Data *d2){
    int a, b;
    a=(d1->ano)*10000+(d1->mes)*100+(d1->dia);
    b=(d2->ano)*10000+(d2->mes)*100+(d2->dia);
    if (a>b) return 1;
    else if (a<b) return -1;
    else{
        a=d1->hora*100+d1->min;
        b=d2->hora*100+d2->min;
        if (a>b) return 1;
        else if (a<b) return -1;
        else return 0;
    }
}

void imprime_viagem(Viagem *viagem){
    printf("Destino: %-20s-- Data: %04d-%02d-%02d -- Hora: %02d:%02d\n",viagem->destino, (viagem->partida)->ano, (viagem->partida)->mes, (viagem->partida)->dia, (viagem->partida)->hora, (viagem->partida)->min);
}

void imprime_utilizador(Utilizador *utilizador){
    printf("CC: %08d -- Nome: %s\n", utilizador->cc, utilizador->nome);
}

int verifica_data(int dia, int mes, int ano){
   	if ((dia >= 1) && (mes >= 1 && mes <= 12) && ano>=0){
        if (mes==2){
            if (dia<=28)
                return 1;
            else if (((ano % 400 == 0) || ((ano % 4 == 0) && (ano % 100 != 0))) && dia==29)
                return 1;
        }
        else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && (dia <= 30))
            return 1;
        else if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)&&(dia <=31) )
            return 1;
    }
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
        fgets(nome, MAX_STRING, stdin);
        retira_enter(nome);
        while(nome[i] != '\0'){
             if((nome[i]>='A' && nome[i]<='Z') || (nome[i]>='a' && nome[i]<='z') || (nome[i]>='À' && nome[i]<='Ö') || (nome[i]>='Ø' && nome[i]<='ö') || (nome[i]>='ø' && nome[i]<='ÿ') || nome[i] == ' ' || nome[i] == '-')
                contador++;
            i++;
        }
        if(nome[0] == ' ' || nome[0] == '\0' || nome[strlen(nome)-1] == ' ' || contador != i){
            printf("Nome inválido. Insira de novo: ");
            invalido=1;
        }
    }while(invalido==1);

    return nome;
}

int devolve_cc(Lista_utilizadores lista_utilizadores){
    char cc[MAX_STRING];
    int i, aux;
    Lista_utilizadores aux_l;

    do{
        aux_l=lista_utilizadores;
        printf("Insira o número de cartão de cidadão do cliente (8 dígitos): ");
        fgets(cc, MAX_STRING, stdin);
        retira_enter(cc);

        aux=0;
        for(i=0; cc[i] != '\0'; i++){
            if(isdigit(cc[i]))
                aux++;
        }
        if (aux != strlen(cc))
            printf("Número introduzido inválido.\n");
        else if (strlen(cc)!=8)
            printf("Número inserido não tem 8 dígitos.\n");
        else{
            i=0;
            while(aux_l->next!=NULL){
                aux_l=aux_l->next;
                if(aux_l->utilizador->cc==atoi(cc)){
                    i=1;
                    printf("Número de Cartão de Cidadão já existente.\n");
                }
            }

        }
    }while(strlen(cc)!=8 || aux != 8 || i==1);

    /*passa de char para int*/
    return atoi(cc);
}

int devolve_inteiro(){
    char numero[MAX_STRING];
    int i, aux;

    do{
        fgets(numero, MAX_STRING, stdin);
        retira_enter(numero);

        aux=0;
        for(i=0; numero[i] != '\0'; i++){
            if(isdigit(numero[i]))
                aux++;
        }
        if (aux != i || i==0)
            printf("Número introduzido inválido. Introduza de novo: ");
        else if (strlen(numero)>9)
            printf("Apenas permitidos números até 9 dígitos. Introduza de novo: ");
    }while(aux != i || i==0 || strlen(numero)>9);

    /*passa de char para int*/

    return atoi(numero);
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
    no = cria_lista_viagens();

    reg = cria_lista_utilizadores();
    no->ut_registado=reg;

    esp = cria_lista_utilizadores();
    no->ut_espera=esp;

    if (no != NULL) {
        no->viagem=viagem;
        procura_lista_principal_viagens(lista, viagem->partida, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
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

    data_partida=(Data*) malloc(sizeof(Data));

    printf("Destino da nova viagem: ");
    destino=devolve_nome();

    printf("Número de vagas da nova viagem: ");
    vagas=devolve_inteiro();

    printf("Insira a data de partida\n");
    do{
        printf("Ano:");
        data_partida->ano=devolve_inteiro();
        printf("Mês:");
        data_partida->mes=devolve_inteiro();
        printf("Dia:");
        data_partida->dia=devolve_inteiro();
        aux=verifica_data(data_partida->dia, data_partida->mes, data_partida->ano);
        if(aux==0)
            printf("Data inválida. Introduza a data novamente!\n");
        else if(data_partida->ano > 9999)
            printf("Apenas permitidas datas até ao ano 9999. Introduza a data novamente!\n");
    }while((aux==0)||(data_partida->ano > 9999));

    printf("Insira as horas da partida\n");
    do{
        aux=0;
        printf("Hora:");
        data_partida->hora=devolve_inteiro();
        printf("Minutos:");
        data_partida->min=devolve_inteiro();
        if(data_partida->hora<0 || data_partida->hora>23 || data_partida->min<0 || data_partida->min>59){
            aux=1;
            printf("Hora inválida. Introduza a hora novamente!\n");
        }
    }while(aux==1);

    regista_viagem(lista_principal, destino, data_partida, vagas);
    printf("Viagem inserida com sucesso!\n");
}

void insere_lista_principal_utilizadores(Lista_utilizadores lista_principal, Utilizador *utilizador){
    Lista_utilizadores lu_aux, no;
    Lista_viagens reg, esp;
    no = cria_lista_utilizadores();
    reg = cria_lista_viagens();
    esp = cria_lista_viagens();

    no->vgm_registado=reg;
    no->vgm_espera=esp;
    no->utilizador=utilizador;

    lu_aux=lista_principal;
    while(lu_aux->next!=NULL){
        lu_aux=lu_aux->next;
    }
    lu_aux->next=no;
}

void regista_cliente(Lista_utilizadores lista_principal, char *nome, int cc){
    Utilizador *utilizador;

    utilizador=(Utilizador*) malloc(sizeof(Utilizador));

    utilizador->nome=nome;
    utilizador->cc=cc;
    insere_lista_principal_utilizadores(lista_principal, utilizador);
}


void regista_cliente_manual(Lista_utilizadores lista_principal){
    char *nome;
    int cc;

    printf("Insira o nome do cliente: ");
    nome=devolve_nome();
    cc=devolve_cc(lista_principal);
    regista_cliente(lista_principal, nome, cc);
    printf("Cliente inserido com sucesso!\n");
}

Viagem* escolhe_viagem(Lista_viagens lista_viagens){
    Lista_viagens aux;
    int i, invalido, opcao;

    aux=lista_viagens;
    system("cls");

    i=0;
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
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez.\n");
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

    aux=lista_utilizadores;
    system("cls");

    i=0;
    if(aux->next==NULL){
        printf("Sem utilizadores disponíveis!\n");
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
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez.\n");
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
    percorre_vgm=node_ut->vgm_espera;
    while(percorre_vgm->viagem!=aux_v && percorre_vgm->next!=NULL)
        percorre_vgm=percorre_vgm->next;
    if(percorre_vgm->viagem==aux_v)
        return -1;
    return 0;
}

int encontra_posicao_utilizador(Lista_utilizadores lista_principal_utilizadores, Utilizador* ut){
    Lista_utilizadores lu_aux;
    int i;
    lu_aux=lista_principal_utilizadores;
    for(i=0;lu_aux->utilizador!=ut;i++)
        lu_aux=lu_aux->next;
    return i;
}

Utilizador *utilizador_por_posicao(Lista_utilizadores lista_principal_utilizadores, int posicao){
    Lista_utilizadores lu_aux;
    int i;
    lu_aux=lista_principal_utilizadores;
    for(i=0;i<posicao; i++)
        lu_aux=lu_aux->next;
    return lu_aux->utilizador;
}

int encontra_posicao_viagem(Lista_viagens lista_principal_viagens, Viagem* vgm){
    Lista_viagens lv_aux;
    int i;
    lv_aux=lista_principal_viagens;
    for(i=0;lv_aux->viagem!=vgm;i++)
        lv_aux=lv_aux->next;
    return i;
}

Viagem *viagem_por_posicao(Lista_viagens lista_principal_viagens, int posicao){
    Lista_viagens lv_aux;
    int i;
    lv_aux=lista_principal_viagens;
    for(i=0;i<posicao;i++)
        lv_aux=lv_aux->next;
    return lv_aux->viagem;
}

void compra_viagem(Lista_utilizadores lista_utilizadores, Lista_viagens lista_viagens){
    Lista_utilizadores node_u, lut_aux, lu_sec;
    Lista_viagens node_v, lvgm_aux, lv_sec;
    Utilizador *aux_u;
    Viagem *aux_v;
    int aux_int, opcao;

    aux_u=escolhe_utilizador(lista_utilizadores);
    if(aux_u==NULL)
        return;

    aux_v=escolhe_viagem(lista_viagens);
    if(aux_v==NULL)
        return;

    lut_aux=lista_utilizadores->next;
    lvgm_aux=lista_viagens->next;

    while(aux_u != lut_aux->utilizador && lut_aux->next!=NULL)
        lut_aux=lut_aux->next;
    while(aux_v != lvgm_aux->viagem && lvgm_aux->next!=NULL)
        lvgm_aux=lvgm_aux->next;

    aux_int=procura_viagem_de_utilizador(lut_aux, aux_v);
    if(aux_int==1){
        printf("Utilizador já comprou a viagem [lista de reservas]\n");
        return;
    }
    else if (aux_int==-1){
        printf("Utilizador já comprou a viagem [lista de espera]\n");
        return;
    }
    else if (aux_int==0){
        node_u = cria_lista_utilizadores();
        node_u->utilizador=lut_aux->utilizador;

        node_v = cria_lista_viagens();
        node_v->viagem=lvgm_aux->viagem;

        if(lvgm_aux->viagem->vagas > 0){
            lu_sec=lvgm_aux->ut_registado;
            while(lu_sec->next != NULL)
                lu_sec=lu_sec->next;
            lu_sec->next=node_u;

            lv_sec=lut_aux->vgm_registado;
            while(lv_sec->next != NULL)
                lv_sec=lv_sec->next;
            lv_sec->next=node_v;

            lvgm_aux->viagem->vagas=(lvgm_aux->viagem->vagas)-1;
            printf("Compra bem sucedida. Cliente colocado na lista de reservas.\n");
        }
        else{
            printf("Não existem vagas disponíveis:\n[1] Colocar na lista de espera\n[2] Voltar ao menu\n");
            do{
                opcao=devolve_inteiro();
                if(opcao==1){
                    lu_sec=lvgm_aux->ut_espera;
                    while(lu_sec->next != NULL)
                        lu_sec=lu_sec->next;
                    lu_sec->next=node_u;

                    lv_sec=lut_aux->vgm_espera;
                    while(lv_sec->next != NULL)
                        lv_sec=lv_sec->next;
                    lv_sec->next=node_v;
                    printf("Compra bem sucedida. Cliente colocado na lista de espera.\n");
                }
                else if(opcao!=2)
                    printf("Opção inexistente. Escolha de novo: ");
            }while((opcao!=1) && (opcao!=2));
            return;
        }
    }
}

void viagens_destino(Lista_viagens lista_viagens){
    char* destino;
    int found;
    Lista_viagens aux_v, lv_ant, lv_header, lv_atual, aux_free;

    lv_header=cria_lista_viagens();
    aux_v=lista_viagens;
    if(aux_v->next==NULL){
        printf("Não existem viagens.\n");
        return;
    }
    printf("Introduza o destino que deseja: ");
    destino=(char*) malloc(MAX_STRING * sizeof(char));
    destino=devolve_nome();

    found=0;

    while(aux_v->next!=NULL){
        aux_v=aux_v->next;
        if(strcmp(aux_v->viagem->destino, destino)==0){
            if(found==0){
                lv_ant=(Lista_viagens) malloc(sizeof(Lista_viagens_node));
                lv_ant->ut_espera=aux_v->ut_espera;
                lv_ant->ut_registado=aux_v->ut_registado;
                lv_ant->viagem=aux_v->viagem;
                lv_ant->next=NULL;
                lv_header->next=lv_ant;
                found=1;
            }

            else{
                lv_atual=(Lista_viagens) malloc(sizeof(Lista_viagens_node));
                lv_atual->ut_espera=aux_v->ut_espera;
                lv_atual->ut_registado=aux_v->ut_registado;
                lv_atual->viagem=aux_v->viagem;

                lv_atual->next=lv_ant;
                lv_header->next=lv_atual;

                lv_ant=lv_atual;
                found=1;
            }
        }
    }
    aux_free=lv_header;
    if(found!=0){
        while(lv_header->next!=NULL){
            lv_header=lv_header->next;
            imprime_viagem(lv_header->viagem);
            free(aux_free->next);
            free(aux_free->ut_espera);
            free(aux_free->ut_registado);
            free(aux_free->viagem);
            free(aux_free);
            aux_free=lv_header->next;
        }
    }
    else
        printf("Não existem viagens com o destino %s.\n", destino);

    free(destino);
}

void viagens_utilizador(Lista_utilizadores node_ut){
    Utilizador *utilizador;
    Lista_viagens lv_sec;
    Lista_utilizadores aux_u;

    aux_u=node_ut;
    utilizador=escolhe_utilizador(aux_u);
    if(utilizador==NULL){
        return;
    }

    while(utilizador != aux_u->utilizador || aux_u->next!=NULL)
            aux_u=aux_u->next;

    lv_sec=aux_u->vgm_registado;
    if(lv_sec->next==NULL)
        printf("Este cliente ainda não adquiriu nenhuma viagem.\n");

    while(lv_sec->next!=NULL){
        lv_sec=lv_sec->next;
        imprime_viagem(lv_sec->viagem);
    }
}

void todos_com_viagem(Lista_utilizadores lista_utilizadores){
    Lista_viagens lv_reg, lv_esp;
    Lista_utilizadores aux_u;
    int flag;

    flag=0;
    aux_u=lista_utilizadores->next;

    if(aux_u==NULL){
        printf("Não existe nenhum cliente na base de dados.\n");
        return;
    }

    lv_reg=aux_u->vgm_registado;
    lv_esp=aux_u->vgm_espera;

    while(aux_u!=NULL){;
        if(lv_esp->next!=NULL || lv_reg->next!=NULL){
            imprime_utilizador(aux_u->utilizador);
            flag=1;
        }
        aux_u=aux_u->next;
    }

    if(flag==0)
        printf("Não existe nenhum cliente com viagens registadas.\n");
}

