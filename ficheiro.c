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
        fprintf(ficheiro, "%s | %d-%d-%d %d:%d | %d\n", lv_aux->viagem->destino, lv_aux->viagem->partida->ano, lv_aux->viagem->partida->mes, lv_aux->viagem->partida->dia, lv_aux->viagem->partida->hora, lv_aux->viagem->partida->min, lv_aux->viagem->vagas);
    }
    fclose(ficheiro);

/*Utilizadores*/
    ficheiro=fopen("utilizadores.txt", "w");
    lu_aux=lista_principal_utilizadores;
    while(lu_aux->next!=NULL){
        lu_aux=lu_aux->next;
        fprintf(ficheiro, "%s | %d\n", lu_aux->utilizador->nome, lu_aux->utilizador->cc);
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
    }

    /*pela lista de utilizadores*/
    fprintf(ficheiro,"\n#\n"); /*sinal de comeco lista de utilizadores*/
    lu_aux=lista_principal_utilizadores;
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
    fprintf(ficheiro, "\n!"); /*sinal de fim*/
    fclose(ficheiro);
}

