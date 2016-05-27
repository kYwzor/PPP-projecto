#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define MAX_STRING 100

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

#endif // HEADER_H_INCLUDED
