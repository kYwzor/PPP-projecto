#include <stdio.h>
#include <stdlib.h>
#include "header.h"

Lista_viagens cria_lista_viagens(){
    Lista_viagens aux;

    aux = (Lista_viagens) malloc (sizeof (Lista_viagens_node));

    if (aux != NULL){
        aux->viagem = NULL;
        aux->ut_registado = NULL;
        aux->ut_espera = NULL;
        aux->next = NULL;
        return aux;
    }
    else
        printf("Erro na alocação de memória.");
}

Lista_utilizadores cria_lista_utilizadores(){
    Lista_utilizadores aux;

    aux = (Lista_utilizadores) malloc (sizeof (Lista_utilizadores_node));

    if (aux != NULL){
        aux->utilizador = NULL;
        aux->vgm_registado = NULL;
        aux->vgm_espera = NULL;
        aux->next = NULL;
        return aux;
    }
    else
        printf("Erro na alocação de memória.");
}

void retira_enter(char* nome){
    if(nome[strlen(nome)-1] == '\n')
        nome[strlen(nome)-1] = '\0';
}
