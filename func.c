#include "header.h"

Lista_viagens cria_lista_viagens(){
    Lista_viagens aux;

    aux = (Lista_viagens) malloc (sizeof (Lista_viagens_node));

    if (aux != NULL){
        aux->viagem = NULL;
        aux->ut_registado = NULL;
        aux->ut_espera = NULL;
        aux->next = NULL;
    }
    else
        printf("Erro na alocação de memória.\n");
    return aux;
}

Lista_utilizadores cria_lista_utilizadores(){
    Lista_utilizadores aux;

    aux = (Lista_utilizadores) malloc (sizeof (Lista_utilizadores_node));

    if (aux != NULL){
        aux->utilizador = NULL;
        aux->vgm_registado = NULL;
        aux->vgm_espera = NULL;
        aux->next = NULL;
    }
    else
        printf("Erro na alocação de memória.\n");
    return aux;
}

void imprime_viagem(Viagem *viagem){
    printf("Destino: %-20s-- Data: %04d-%02d-%02d -- Hora: %02d:%02d\n",viagem->destino, (viagem->partida)->ano, (viagem->partida)->mes, (viagem->partida)->dia, (viagem->partida)->hora, (viagem->partida)->min);
}

void imprime_utilizador(Utilizador *utilizador){
    printf("CC: %08d -- Nome: %s\n", utilizador->cc, utilizador->nome);
}

void retira_enter(char* str){
    int len;
    len=strlen(str);
    if(len>0 && str[len-1] == '\n')
        str[len-1] = '\0';
}

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
    char recebe[MAX_STRING];
    int contador, i, invalido;

    do{
        i=0;
        contador=0;
        invalido=0;
        fgets(recebe, MAX_STRING, stdin);
        retira_enter(recebe);
        while(recebe[i] != '\0'){
            if((recebe[i]>='A' && recebe[i]<='Z') || (recebe[i]>='a' && recebe[i]<='z') || recebe[i] == ' ')
                contador++;
            i++;
        }
        if(recebe[0] == ' ' || recebe[0] == '\0' || recebe[strlen(recebe)-1] == ' ' || contador != i){
            printf("Nome inválido. Insira de novo: ");
            invalido=1;
        }
    }while(invalido==1);

    nome=strdup(recebe);

    return nome;
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

int devolve_cc(Lista_utilizadores lista_utilizadores){
    char cc[MAX_STRING];
    int i, aux;
    Lista_utilizadores aux_l;

    do{
        aux_l=lista_utilizadores;
        printf("Insira o número de cartão de cidadão do utilizador (8 dígitos): ");
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

    return atoi(cc);
}

void limpa_alocacoes(Lista_viagens lista_principal_viagens, Lista_utilizadores lista_principal_utilizadores){
    Lista_viagens lv_aux, lv_sec, lv_free;
    Lista_utilizadores lu_aux, lu_sec, lu_free;

    lv_aux=lista_principal_viagens->next;
    free(lista_principal_viagens);
    while(lv_aux!=NULL){
        free(lv_aux->viagem->destino);
        free(lv_aux->viagem->partida);
        free(lv_aux->viagem);
        lu_sec=lv_aux->ut_registado;
        while(lu_sec!=NULL){
            lu_aux=lu_sec;
            lu_sec=lu_sec->next;
            free(lu_aux);
        }
        lu_sec=lv_aux->ut_espera;
        while(lu_sec!=NULL){
            lu_aux=lu_sec;
            lu_sec=lu_sec->next;
            free(lu_aux);
        }
        lv_free=lv_aux;
        lv_aux=lv_aux->next;
        free(lv_free);
    }

    lu_aux=lista_principal_utilizadores->next;
    free(lista_principal_utilizadores);
    while(lu_aux!=NULL){
        free(lu_aux->utilizador->nome);
        free(lu_aux->utilizador);
        lv_sec=lu_aux->vgm_registado;
        while(lv_sec!=NULL){
            lv_aux=lv_sec;
            lv_sec=lv_sec->next;
            free(lv_aux);
        }
        lv_sec=lu_aux->vgm_espera;
        while(lv_sec!=NULL){
            lv_aux=lv_sec;
            lv_sec=lv_sec->next;
            free(lv_aux);
        }
        lu_free=lu_aux;
        lu_aux=lu_aux->next;
        free(lu_free);
    }
}
