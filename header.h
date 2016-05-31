#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define MAX_STRING 500
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

typedef struct data{
    int min,hora,dia,mes,ano;
}Data;

typedef struct utilizador{
    char *nome;
    int cc;
}Utilizador;

typedef struct viagem{
    char *destino;
    Data *partida;
    int vagas;
}Viagem;

typedef struct lnode_uti *Lista_utilizadores;
typedef struct lnode_vgm *Lista_viagens;

typedef struct lnode_uti{
    Utilizador *utilizador;
    Lista_viagens vgm_registado;
    Lista_viagens vgm_espera;
    Lista_utilizadores next;
}Lista_utilizadores_node;

typedef struct lnode_vgm{
    Viagem *viagem;
    Lista_utilizadores ut_registado;
    Lista_utilizadores ut_espera;
    Lista_viagens next;
}Lista_viagens_node;

/*func.c*/
Lista_viagens cria_lista_viagens();
Lista_utilizadores cria_lista_utilizadores();
void imprime_viagem(Viagem *viagem);
void imprime_utilizador(Utilizador *utilizador);
void retira_enter(char* str);
int compara_datas(Data *d1, Data *d2);
int verifica_data(int dia, int mes, int ano);
char* devolve_nome();
int devolve_inteiro();
int devolve_cc(Lista_utilizadores lista_utilizadores);
void limpa_alocacoes(Lista_viagens lista_principal_viagens, Lista_utilizadores lista_principal_utilizadores);

/*gestao.c*/
void procura_lista_principal_viagens (Lista_viagens lista, Data *chave, Lista_viagens *ant, Lista_viagens *actual);
void insere_lista_principal_viagens (Lista_viagens lista, Viagem *viagem);
void insere_lista_principal_utilizadores(Lista_utilizadores lista_principal, Utilizador *utilizador);
void regista_viagem(Lista_viagens lista_principal, char* destino, Data* data_partida, int vagas);
void regista_viagem_manual(Lista_viagens lista_principal);
void regista_utilizador(Lista_utilizadores lista_principal, char *nome, int cc);
void regista_utilizador_manual(Lista_utilizadores lista_principal);
Viagem* escolhe_viagem(Lista_viagens lista_viagens);
Utilizador* escolhe_utilizador(Lista_utilizadores lista_utilizadores);
int procura_viagem_de_utilizador(Lista_utilizadores node_ut, Viagem* aux_v);
int encontra_posicao_utilizador(Lista_utilizadores lista_principal_utilizadores, Utilizador* ut);
Utilizador *utilizador_por_posicao(Lista_utilizadores lista_principal_utilizadores, int posicao);
int encontra_posicao_viagem(Lista_viagens lista_principal_viagens, Viagem* vgm);
Viagem *viagem_por_posicao(Lista_viagens lista_principal_viagens, int posicao);
void compra_viagem(Lista_utilizadores lista_utilizadores, Lista_viagens lista_viagens);
void viagens_destino(Lista_viagens lista_viagens);
void viagens_utilizador(Lista_utilizadores lista_principal_utilizadores);
void utilizadores_viagem(Lista_viagens lista_principal_viagens);
void todos_com_viagem(Lista_utilizadores lista_utilizadores);
void cancela_compra(Lista_utilizadores lista_principal_utilizadores, Lista_viagens lista_principal_viagens);

/*ficheiro.c*/
void verifica_ficheiros();
void guarda_listas(Lista_viagens lista_principal_viagens, Lista_utilizadores lista_principal_utilizadores);
void carrega_listas(Lista_viagens lista_principal_viagens, Lista_utilizadores lista_principal_utilizadores);


#endif
