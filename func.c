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
        printf("Erro na alocação de memória.");
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
        printf("Erro na alocação de memória.");
    return aux;
}

void retira_enter(char* str){
    int len;
    len=strlen(str);
    if(len>0 && str[len-1] == '\n')
        str[len-1] = '\0';
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
