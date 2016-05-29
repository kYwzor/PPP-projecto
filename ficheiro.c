#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "header.h"

void verifica_ficheiros(){
	FILE *ficheiro;

	if (access("viagens.txt",F_OK)==-1){
    	ficheiro=fopen("viagens.txt","w");
    	fclose(ficheiro);
	}
	if (access("utilizadores.txt",F_OK)==-1){
    	ficheiro=fopen("utilizadores.txt","w");
    	fclose(ficheiro);
	}
	if (access("compras.txt",F_OK)==-1){
    	ficheiro=fopen("compras.txt","w");
    	fclose(ficheiro);
	}
}

void guarda_listas(Lista_viagens lista_principal_viagens, Lista_utilizadores lista_principal_utilizadores){
    Lista_utilizadores lu_aux;
    Lista_viagens lv_aux;
    FILE *ficheiro;
    int int_aux;

/*Viagens*/
    ficheiro=fopen("viagens.txt", "w");
    lv_aux=lista_principal_viagens;
    while(lv_aux->next!=NULL){
        lv_aux=lv_aux->next;
        fprintf(ficheiro, "%04d%02d%02d%02d%02d%09d%s", lv_aux->viagem->partida->ano, lv_aux->viagem->partida->mes, lv_aux->viagem->partida->dia, lv_aux->viagem->partida->hora, lv_aux->viagem->partida->min, lv_aux->viagem->vagas, lv_aux->viagem->destino);
        if(lv_aux->next!=NULL)
            fprintf(ficheiro, "\n");
    }
    fclose(ficheiro);

/*Utilizadores*/
    ficheiro=fopen("utilizadores.txt", "w");
    lu_aux=lista_principal_utilizadores;
    while(lu_aux->next!=NULL){
        lu_aux=lu_aux->next;
        fprintf(ficheiro, "%08d%s",lu_aux->utilizador->cc, lu_aux->utilizador->nome);
        if(lu_aux->next!=NULL)
            fprintf(ficheiro, "\n");
    }
    fclose(ficheiro);

/*Compras*/
    ficheiro=fopen("compras.txt", "w");

    /*pela lista de viagens*/
    lv_aux=lista_principal_viagens;
    while(lv_aux->next!=NULL){
        lv_aux=lv_aux->next;
        /*registados*/
        lu_aux=lv_aux->ut_registado;
        while(lu_aux->next!=NULL){
            lu_aux=lu_aux->next;
            int_aux=encontra_posicao_utilizador(lista_principal_utilizadores, lu_aux->utilizador);
            fprintf(ficheiro, "%d|", int_aux);
        }
        /*espera*/
        fprintf(ficheiro, "\n"); /*mudanca de paragrafo divide registados de espera*/
        lu_aux=lv_aux->ut_espera;
        while(lu_aux->next!=NULL){
            lu_aux=lu_aux->next;
            int_aux=encontra_posicao_utilizador(lista_principal_utilizadores, lu_aux->utilizador);
            fprintf(ficheiro, "%d|", int_aux);
        }
        if(lv_aux->next!=NULL)
            fprintf(ficheiro, "\n_\n"); /*sinal de mudanca de viagem*/
        else
            fprintf(ficheiro,"\n");
    }

    /*pela lista de utilizadores*/
    fprintf(ficheiro,"#"); /*sinal de comeco lista de utilizadores*/
    lu_aux=lista_principal_utilizadores;
    if(lu_aux->next!=NULL)
        fprintf(ficheiro,"\n");
    while(lu_aux->next!=NULL){
        lu_aux=lu_aux->next;
        /*registados*/
        lv_aux=lu_aux->vgm_registado;
        while(lv_aux->next!=NULL){
            lv_aux=lv_aux->next;
            int_aux=encontra_posicao_viagem(lista_principal_viagens, lv_aux->viagem);
            fprintf(ficheiro, "%d|", int_aux);
        }
        /*espera*/
        fprintf(ficheiro, "\n"); /*mudanca de paragrafo divide registados de espera*/
        lv_aux=lu_aux->vgm_espera;
        while(lv_aux->next!=NULL){
            lv_aux=lv_aux->next;
            int_aux=encontra_posicao_viagem(lista_principal_viagens, lv_aux->viagem);
            fprintf(ficheiro, "%d|", int_aux);
        }
        if(lu_aux->next!=NULL)
            fprintf(ficheiro, "\n_\n"); /*sinal de mudanca de utilizador*/
    }

    /*FIM*/
    fclose(ficheiro);
}


void carrega_listas(Lista_viagens lista_principal_viagens, Lista_utilizadores lista_principal_utilizadores){
    Lista_utilizadores lu_aux;
    Lista_viagens lv_aux;
    FILE *ficheiro;
    char linha[MAX_STRING], copia[MAX_STRING];
    char *char_aux;
    Data *data_partida;
    int int_aux;

/*Viagens*/
    ficheiro=fopen("viagens.txt", "r");
    while(fgets(linha, MAX_STRING, ficheiro)!=NULL){
        data_partida=(Data*) malloc(sizeof(Data));

        strncpy(copia, linha, 4);
        copia[4]='\0';
        data_partida->ano=atoi(copia);

        strncpy(copia, linha+4, 2);
        copia[2]='\0';
        data_partida->mes=atoi(copia);

        strncpy(copia, linha+6, 2);
        copia[2]='\0';
        data_partida->dia=atoi(copia);

        strncpy(copia, linha+8, 2);
        copia[2]='\0';
        data_partida->hora=atoi(copia);

        strncpy(copia, linha+10, 2);
        copia[2]='\0';
        data_partida->min=atoi(copia);

        strncpy(copia, linha+12, 9);
        copia[9]='\0';
        int_aux=atoi(copia);

        strcpy(copia, linha+21);
        retira_enter(copia);
        char_aux=strdup(copia);

        regista_viagem(lista_principal_viagens, char_aux, data_partida, int_aux);
    }
    fclose(ficheiro);

/*Utilizadores*/
    ficheiro=fopen("utilizadores.txt", "r");
    while(fgets(linha, MAX_STRING, ficheiro)!=NULL){
        strncpy(copia, linha, 8);
        copia[8]='\0';
        int_aux=atoi(copia);

        strcpy(copia, linha+8);
        retira_enter(copia);
        char_aux=strdup(copia);

        regista_cliente(lista_principal_utilizadores, char_aux, int_aux);
    }
}

