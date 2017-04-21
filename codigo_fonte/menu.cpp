/*  Esse arquivo cont�m a fun��o Menu, respons�vel por redirecionar o usu�rio � */
/*  uma das 5 fun��es desejadas.                                                */

#include "header.h" // Cabe�alho que une as fun��es de todos os arquivos.

#include <stdio.h>
#include <stdlib.h>

void menu() {
	bool repetir;
	int escolha;
	char escolhaStr[50];

	/* Limpa a tela, altera o t�tulo e configura as cores de fundo e fonte. */

	system("cls");
	system("color 0F");
	system("title [de]coder");

	printf("*********************************************************\n");
	printf("1 - Codificar\n");
	printf("2 - Decodificar\n");
	printf("3 - Teste\n");
	printf("4 - Modificar Senha\n");
	printf("5 - Sair\n\n");
	printf("*********************************************************");
	
	/* Roda um loop pedindo a fun��o desejada at� que o usu�rio */
	/* selecione uma op��o v�lida.                              */

	do {
		repetir = true;

		printf("\nInsira o numero correspondente a funcao desejada: ");
		fgets(escolhaStr, 49, stdin);
		
		/* Caso o usu�rio insira uma string ao inv�s de um n�mero, */
		/* esse bloco de c�digo previne erros.                     */
		
		if (stringNum(escolhaStr) == -9999) {
			escolha = 99;
		}
		else {
			escolha = stringNum(escolhaStr);
		}
		switch (escolha) {
		case 1:
			system("cls");
			codificarMenu();
			repetir = false;
			break;
		case 2:
			system("cls");
			decodificarMenu();
			repetir = false;
			break;
		case 3:
			system("cls");
			teste();
			repetir = false;
			break;
		case 4:
			system("cls");
			pedirSenha();
			novaSenha();
			repetir = false;
			break;
		case 5:
			char sair[20];

			printf("\nVoce tem certeza que deseja sair?[S/N] ");
			fgets(sair, 19, stdin);

			if (sair[0] == 'S' || sair[0] == 's') {
				exit(1);
			}
			break;
		default:
			printf("\n\nEntrada Invalida\n");
			break;
		}
	} while (repetir);

}
