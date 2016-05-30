#include "header.h"

void menu(Lista_viagens lista_principal_viagens, Lista_utilizadores lista_principal_utilizadores){
	int opcao = 0;

    while(1){
        printf(" _____ _____ _____ _____ \n|     |   __|   | |  |  |\n| | | |   __| | | |  |  |\n|_|_|_|_____|_|___|_____|\n___________________________\n\n");
        printf("[1] Registar uma viagem\n");
        printf("[2] Registar um utilizador\n");
        printf("[3] Compra viagem para o utilizador\n");
        printf("[4] Cancelar compra de um utilizador\n");
        printf("[5] Listar viagens para um destino\n");
        printf("[6] Listar viagens de um utilizador\n");
        printf("[7] Listar utilizadores de uma viagem\n");
        printf("[8] Listar todos os utilizadores com viagens compradas\n");
        printf("[9] Sair do programa\n\n");

        opcao=devolve_inteiro();

        system("cls");
        switch(opcao){
            case 1:
                regista_viagem_manual(lista_principal_viagens);
                break;
            case 2:
                regista_utilizador_manual(lista_principal_utilizadores);
                break;
            case 3:
                compra_viagem(lista_principal_utilizadores, lista_principal_viagens);
                break;
            case 4:
                cancela_compra(lista_principal_utilizadores, lista_principal_viagens);
                break;
            case 5:
                viagens_destino(lista_principal_viagens);
                break;
            case 6:
                viagens_utilizador(lista_principal_utilizadores);
                break;
            case 7:
                utilizadores_viagem(lista_principal_viagens);
                break;
            case 8:
                todos_com_viagem(lista_principal_utilizadores);
                break;
            case 9:
                return;
                break;
            default:
                printf("Introduza uma opção válida!\n");
                break;
        }
        printf("Prima Enter para voltar ao menu.");
        while(getchar()!='\n');
        system("cls");
    }
}

int main(){
    Lista_viagens lista_principal_viagens;
    Lista_utilizadores lista_principal_utilizadores;

    lista_principal_viagens = cria_lista_viagens();
    lista_principal_utilizadores = cria_lista_utilizadores();

    verifica_ficheiros();
    carrega_listas(lista_principal_viagens, lista_principal_utilizadores);

    setlocale(LC_ALL, "Portuguese");

    menu(lista_principal_viagens, lista_principal_utilizadores);

    guarda_listas(lista_principal_viagens, lista_principal_utilizadores);
    limpa_alocacoes();

    return 0;
}
