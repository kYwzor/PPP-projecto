#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "header.h"

void menu(Lista_viagens lista_principal_viagens, Lista_utilizadores lista_principal_utilizadores){
	int opcao = 0;

    verifica_ficheiros(); /*verifica que os ficheiros estão disponíveis e funcionais*/

    do{
        printf("[ADMIN -> 0] Registar uma viagem\n");
        printf("[ADMIN -> 1] Registar um utilizador\n");
        printf("[2] Registar pedido de um utilizador\n");
        printf("[9] Sair do programa\n");

        scanf("%d",&opcao);
        getchar();

        system("cls");
        switch(opcao){
            case 0:
                regista_viagem_manual(lista_principal_viagens);
                /*lista_para_ficheiro(lista_principal,"listas.txt");*/
                break;
            case 1:
                regista_cliente(lista_principal_utilizadores);
                /*lista_para_ficheiro(lista_principal,"listas.txt");*/
                break;
            case 2:
                compra_viagem_manual(lista_principal_utilizadores, lista_principal_viagens);
                /*lista_para_ficheiro(lista_principal,"listas.txt");*/
                break;
            case 9:
                /*sai do programa... Free, etc.*/
                break;
            default:
                printf("Introduza uma opção válida!\n");
                break;
        }
        if(opcao!=9){
            printf("Prima Enter para voltar ao menu.");
            getchar();
        }
        system("cls");
    }while(opcao!=9);
}

int main(){
    setlocale(LC_ALL, "");
    Lista_viagens lista_principal_viagens;
    Lista_utilizadores lista_principal_utilizadores;
    lista_principal_viagens = cria_lista_viagens();
    lista_principal_utilizadores = cria_lista_utilizadores();


    /*verifica_ficheiros(); verifica que os ficheiros estão disponíveis e funcionais
    ficheiro_para_lista(lista_principal ,"listas.txt");*/

    menu(lista_principal_viagens, lista_principal_utilizadores);
    return 0;
}
