#include "header.h"

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
    if(viagem==NULL)
        printf("Erro na alocação de memória.\n");

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
    if(data_partida==NULL)
        printf("Erro na alocação de memória.\n");

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

void regista_utilizador(Lista_utilizadores lista_principal, char *nome, int cc){
    Utilizador *utilizador;

    utilizador=(Utilizador*) malloc(sizeof(Utilizador));
    if(utilizador==NULL)
        printf("Erro na alocação de memória.\n");

    utilizador->nome=nome;
    utilizador->cc=cc;
    insere_lista_principal_utilizadores(lista_principal, utilizador);
}


void regista_utilizador_manual(Lista_utilizadores lista_principal){
    char *nome;
    int cc;

    printf("Insira o nome do utilizador: ");
    nome=devolve_nome();
    cc=devolve_cc(lista_principal);
    regista_utilizador(lista_principal, nome, cc);
    printf("Utilizador inserido com sucesso!\n");
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
    printf("\nEscolha a opção: ");
    do{
        invalido=0;
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez: ");
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
    printf("\nEscolha a opção: ");
    do{
        invalido=0;
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez: ");
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

    while(aux_u != lut_aux->utilizador)
        lut_aux=lut_aux->next;
    while(aux_v != lvgm_aux->viagem)
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
            printf("Compra bem sucedida. Utilizador colocado na lista de reservas.\n");
        }
        else{
            printf("\nNão existem vagas disponíveis:\n[1] Colocar na lista de espera\n[2] Voltar ao menu\n\nEscolha a opção: ");
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
                    printf("Compra bem sucedida. Utilizador colocado na lista de espera.\n");
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
    Lista_viagens aux_v, lv_ant, lv_atual, aux_free;

    aux_v=lista_viagens;
    if(aux_v->next==NULL){
        printf("Não existem viagens.\n");
        return;
    }
    printf("Introduza o destino que deseja: ");
    destino=devolve_nome();

    lv_ant=NULL;
    lv_atual=NULL;
    while(aux_v->next!=NULL){
        aux_v=aux_v->next;
        if(strcmp(aux_v->viagem->destino, destino)==0){
            lv_atual=cria_lista_viagens();
            lv_atual->viagem=aux_v->viagem;
            lv_atual->next=lv_ant;
            lv_ant=lv_atual;
        }
    }

    if(lv_atual==NULL)
        printf("Não existem viagens com o destino \"%s\".\n", destino);

    while(lv_atual!=NULL){
        imprime_viagem(lv_atual->viagem);
        aux_free=lv_atual;
        lv_atual=lv_atual->next;
        free(aux_free);
    }
    free(destino);
}

void viagens_utilizador(Lista_utilizadores lista_principal_utilizadores){
    Utilizador *utilizador;
    Lista_viagens lv_sec;
    Lista_utilizadores aux_u;
    int opcao, invalido;

    aux_u=lista_principal_utilizadores;
    utilizador=escolhe_utilizador(aux_u);
    if(utilizador==NULL){
        return;
    }
    while(utilizador != aux_u->utilizador)
        aux_u=aux_u->next;

    system("cls");
    printf("Escolha que viagens de %s quer listar\n[1] Viagens reservadas\n[2] Viagens em espera\n[3] Todas as viagens\n\nEscolha a opção: ", utilizador->nome);
    do{
        invalido=0;
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>3){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez: ");
        }
    }while(invalido==1);

    printf("\n");

    if(opcao==1){
        lv_sec=aux_u->vgm_registado;
        if(lv_sec->next==NULL){
            printf("%s não tem nenhuma viagem reservada.\n\n", utilizador->nome);
            return;
        }

        printf("Lista de viagens reservadas de %s:\n", utilizador->nome);
        while(lv_sec->next!=NULL){
            lv_sec=lv_sec->next;
            imprime_viagem(lv_sec->viagem);
        }
    }
    else if(opcao==2){
        lv_sec=aux_u->vgm_espera;
        if(lv_sec->next==NULL){
            printf("%s não tem nenhuma viagem em espera.\n\n", utilizador->nome);
            return;
        }

        printf("Lista de viagens em espera de %s:\n", utilizador->nome);
        while(lv_sec->next!=NULL){
            lv_sec=lv_sec->next;
            imprime_viagem(lv_sec->viagem);
        }
    }
    else{
        lv_sec=aux_u->vgm_registado;
        if(lv_sec->next==NULL)
            printf("%s não tem nenhuma viagem reservada.\n", utilizador->nome);

        else{
            printf("Lista de viagens reservadas de %s:\n", utilizador->nome);
            while(lv_sec->next!=NULL){
                lv_sec=lv_sec->next;
                imprime_viagem(lv_sec->viagem);
            }
            lv_sec=aux_u->vgm_espera;
        }

        printf("\n");

        if(lv_sec->next==NULL)
            printf("%s não tem nenhuma viagem em espera.\n", utilizador->nome);

        else{
            printf("Lista de viagens em espera de %s:\n", utilizador->nome);
            while(lv_sec->next!=NULL){
                lv_sec=lv_sec->next;
                imprime_viagem(lv_sec->viagem);
            }
        }
    }
    printf("\n");
}

void utilizadores_viagem(Lista_viagens lista_principal_viagens){
    Viagem *viagem;
    Lista_viagens aux_v;
    Lista_utilizadores lu_sec;
    int opcao, invalido;

    aux_v=lista_principal_viagens;
    viagem=escolhe_viagem(aux_v);
    if(viagem==NULL){
        return;
    }
    while(viagem != aux_v->viagem)
        aux_v=aux_v->next;

    system("cls");
    printf("Escolha que utilizadores da viagem quer listar\n[1] Utilizadores com reserva\n[2] Utilizadores em espera\n[3] Todos os utilizadores\n\nEscolha a opção: ");
    do{
        invalido=0;
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>3){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez: ");
        }
    }while(invalido==1);

    printf("\n");

    if(opcao==1){
        lu_sec=aux_v->ut_registado;
        if(lu_sec->next==NULL){
            printf("Não existem utilizadores com reserva.\n\n");
            return;
        }

        printf("Lista de utilizadores com reserva:\n");
        while(lu_sec->next!=NULL){
            lu_sec=lu_sec->next;
            imprime_utilizador(lu_sec->utilizador);
        }
    }
    else if(opcao==2){
        lu_sec=aux_v->ut_espera;
        if(lu_sec->next==NULL){
            printf("Não existem utilizadores em espera.\n\n");
            return;
        }

        printf("Lista de utilizadores em espera:\n");
        while(lu_sec->next!=NULL){
            lu_sec=lu_sec->next;
            imprime_utilizador(lu_sec->utilizador);
        }
    }
    else{
        lu_sec=aux_v->ut_registado;
        if(lu_sec->next==NULL)
            printf("Não existem utilizadores com reserva.\n");

        else{
            printf("Lista de utilizadores com reserva:\n");
            while(lu_sec->next!=NULL){
                lu_sec=lu_sec->next;
                imprime_utilizador(lu_sec->utilizador);
            }
            lu_sec=aux_v->ut_espera;
        }

        printf("\n");

        if(lu_sec->next==NULL)
            printf("Não existem utilizadores em espera.\n");

        else{
            printf("Lista de utilizadores em espera:\n");
            while(lu_sec->next!=NULL){
                lu_sec=lu_sec->next;
                imprime_utilizador(lu_sec->utilizador);
            }
        }
    }
    printf("\n");
}

void todos_com_viagem(Lista_utilizadores lista_utilizadores){
    Lista_viagens lv_reg, lv_esp;
    Lista_utilizadores aux_u;
    int flag;

    flag=0;
    aux_u=lista_utilizadores->next;

    if(aux_u==NULL){
        printf("Não existe nenhum utilizador na base de dados.\n");
        return;
    }

    while(aux_u!=NULL){
        lv_reg=aux_u->vgm_registado;
        lv_esp=aux_u->vgm_espera;
        if(lv_esp->next!=NULL || lv_reg->next!=NULL){
            imprime_utilizador(aux_u->utilizador);
            flag=1;
        }
        aux_u=aux_u->next;
    }

    if(flag==0)
        printf("Não existe nenhum utilizador com viagens registadas.\n");
}

void cancela_compra(Lista_utilizadores lista_principal_utilizadores, Lista_viagens lista_principal_viagens){
    Lista_utilizadores node_u, lu_sec, lu_sec_aux;
    Lista_viagens node_v, lv_sec, lv_sec_aux;
    Utilizador *aux_u;
    Viagem *aux_v;
    int opcao, invalido;

    aux_u=escolhe_utilizador(lista_principal_utilizadores);
    if(aux_u==NULL)
        return;

    node_u=lista_principal_utilizadores->next;
    while(node_u->utilizador!=aux_u)
        node_u=node_u->next;

    system("cls");
    printf("Escolha o tipo de compra que deseja cancelar\n[1] Viagem reservada\n[2] Viagem na lista de espera\n\nEscolha a opção: ");
    do{
        invalido=0;
        opcao=devolve_inteiro();
        if(opcao!=1 && opcao!=2){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez: ");
        }
    }while(invalido==1);


    if(opcao==1){
        aux_v=escolhe_viagem(node_u->vgm_registado);
        if(aux_v==NULL)
            return;

        lv_sec=node_u->vgm_registado;
        while(lv_sec->next->viagem != aux_v)
            lv_sec=lv_sec->next;

        lv_sec_aux=lv_sec->next;
        lv_sec->next=lv_sec_aux->next;
        free(lv_sec_aux);                                       /*libertada node da lista de viagens registadas*/

        node_v=lista_principal_viagens->next;
        while(node_v->viagem != aux_v)
            node_v=node_v->next;

        lu_sec=node_v->ut_registado;
        while(lu_sec->next->utilizador != aux_u)
            lu_sec=lu_sec->next;

        lu_sec_aux=lu_sec->next;
        lu_sec->next=lu_sec_aux->next;
        free(lu_sec_aux);                                   /*libertada node da lista de utilizadores registados*/
        printf("Reserva cancelada.\n");

        if(node_v->ut_espera->next == NULL){                /*se não houver ninguém na lista de espera*/
            node_v->viagem->vagas++;
            printf("Libertada uma vaga para a viagem.\n");
            return;
        }


        while(lu_sec->next != NULL)
            lu_sec=lu_sec->next;

        lu_sec_aux=node_v->ut_espera->next;                             /*primeiro elemento da lista de espera*/
        lu_sec->next=lu_sec_aux;                                        /*ultimo elemento da lista de reservados é o primeiro da lista de espera*/
        (node_v->ut_espera)->next=lu_sec_aux->next;                     /*liga header ao segundo elemento em espera*/
        lu_sec_aux->next=NULL;                                          /*next do ultimo elemento em reserva é NULL*/

        aux_u=lu_sec_aux->utilizador;
        node_u=lista_principal_utilizadores->next;
        while(node_u->utilizador!=aux_u)
            node_u=node_u->next;

        lv_sec=node_u->vgm_espera;
        while(lv_sec->next->viagem != aux_v)
            lv_sec=lv_sec->next;

        lv_sec_aux=lv_sec->next;                                        /*lv_sec_aux é a node em que está a viagem*/
        lv_sec->next=lv_sec_aux->next;                                  /*anterior a node da viagem passa a apontar para o que esta a seguir a viagem*/
        lv_sec_aux->next=NULL;                                          /*node da viagem aponta para NULL pois vai ser o final da outra lista*/

        lv_sec=node_u->vgm_registado;
        while(lv_sec->next != NULL)
            lv_sec=lv_sec->next;

        lv_sec->next=lv_sec_aux;                                        /*node da viagem posta no final da lista de registados*/
        printf("Utilizador %s movido da lista de espera para a lista de reservas.\n", aux_u->nome);
    }

    else{
        aux_v=escolhe_viagem(node_u->vgm_espera);
        if(aux_v==NULL)
            return;

        lv_sec=node_u->vgm_espera;
        while(lv_sec->next->viagem != aux_v)
            lv_sec=lv_sec->next;

        lv_sec_aux=lv_sec->next;
        lv_sec->next=lv_sec_aux->next;
        free(lv_sec_aux);                                               /*libertada node da lista de viagens espera*/


        node_v=lista_principal_viagens->next;
        while(node_v->viagem != aux_v)
            node_v=node_v->next;

        lu_sec=node_v->ut_espera;
        while(lu_sec->next->utilizador != aux_u)
            lu_sec=lu_sec->next;

        lu_sec_aux=lu_sec->next;
        lu_sec->next=lu_sec_aux->next;
        free(lu_sec_aux);                                               /*libertada node da lista de utilizadores registados*/
        printf("Utilizador retirado da lista de espera.\n");
    }
}
