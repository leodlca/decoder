/*  Esse arquivo cont�m as fun��es acionadas quando o usu�rio solicita a op��o 1 - */
/*  Codificar no Menu Principal                                                    */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

extern int chaveAtual;

/* Cabe�alho do arquivo */

void codificarArquivo();
void codificarInput();
void codificar(char*, char*);

/* codificarMenu() � respons�vel por redirecionar o usu�rio para uma das 2 fun��es    */
/* desejadas da op��o Codificar.                                                      */

void codificarMenu() {
	char escolhaStr[50];
	int escolha;
	bool repetir;

	printf("*********************************************************\n");
	printf("1 - Codificar arquivo (txt_decodificado)\n");
	printf("2 - Codificar texto do usuario\n\n");
	printf("*********************************************************\n");

	/* O Menu ser� exibido ao menos uma vez, e entrar� em loop */
	/* at� que uma op��o v�lida seja selecionada.              */

	do {

		repetir = true;

		printf("Insira o numero correspondente a funcao desejada: ");
		fgets(escolhaStr, 49, stdin);
		if (stringNum(escolhaStr) == -9999) {
			escolha = 99;
		}
		else {
			escolha = stringNum(escolhaStr);
		}
		switch (escolha) {
		case 1:
			system("cls");
			repetir = false;
			codificarArquivo();
			break;
		case 2:
			system("cls");
			repetir = false;
			codificarInput();
			break;
		default:
			printf("Entrada Invalida\n");
			break;
		}
	} while (repetir);
}

/*	codificarArquivo() ler� a string contida em txt_decodificado e a traduzir� por meio */
/*	da fun��o codificar().                                                              */

void codificarArquivo() {

	char txtOriginal[10000],
		txtCodificado[10000],
		data[80];
		
	/* Gera uma string com a data atual, l� arquivo e */
	/* decodifica a string nele contida.              */

	dataAtual(data);
	lerArquivo(txtOriginal, "txt_decodificado.txt");
	codificar(txtCodificado, txtOriginal);

	/* Caso o arquivo esteja vazio, lan�ar erro. */

	if (!temTexto("txt_decodificado.txt")) {
		strcpy(txtCodificado, "\nERRO: O Arquivo txt_decodificado nao contem texto.\n");
	}

	/* Exibe o resultado e a data atual. */

	printf("Traduzido e arquivado em txt_decodificado.txt as %s\n\n%s\n\n", data, txtCodificado);

	/* Armazena o conte�do decodificado formatado nos arquivos de registro */

	salvarArquivo("user_log.txt", "a", txtCodificado, "CODIFICA��O", data);
	salvarArquivo("txt_codificado.txt", "w", txtCodificado, "", "");

	/* Espera alguma entrada do usu�rio para voltar ao menu principal. */

	printf("Pressione qualquer tecla para voltar ao menu... ");
	getch();

}

/* 	codificarInput() ler� uma string inserida pelo usu�rio e a traduzir� por meio */
/*	da fun��o codificar().                                                        */

void codificarInput() {

	char txtOriginal[10000] = "", 
		 txtCodificado[10000],
		 data[80];
	
	/* Pede ao usu�rio o texto a ser codificado. */

	system("cls");
	printf("Insira o texto a ser codificado: ");
	fgets(txtOriginal, 9999, stdin); // fgets() � uma solu��o mais segura � gets().

	/* Codifica o texto entrado pelo usu�rio. */

	dataAtual(data);
	codificar(txtCodificado, txtOriginal);

	/* Exibe o conte�do traduzido com a data. */

	printf("\nTraduzido e arquivado em txt_codificado.txt as %s\n\n%s\n\n", data, txtCodificado);

	/* Salvar Conte�do. */

	salvarArquivo("user_log.txt", "a", txtCodificado, "CODIFICA��O", data);
	salvarArquivo("txt_codificado.txt", "w", txtCodificado, "", "");
	
	/* Espera entrada do usu�rio para voltar ao menu. */

	printf("\nPressione qualquer tecla para voltar ao menu... ");
	getch();

}                             

/* gerarChave() gera um n�mero aleat�rio */
/* que vai de 1 at� o argumento limite.  */                   

int gerarChave (int limite) {
	srand((unsigned)time(NULL));
	
	int chave; 
	chave = rand() % limite;
	return 1 + chave;
}

/* codificarChave() retorna a chaveOriginal */
/* codificada de acordo com a tabela switch */

int codificarChave (int chaveOriginal) {
	int chave = 0;
	
	/* Formata a chave */
	
	int numeros[2] = {(chaveOriginal/10)*10, chaveOriginal % 10};
	
	/* Caso o valor seja menor que 10, a chave inicia com 80, */
	/* pois se x < 10, 10/10*10 = 0, para evitar confus�o de  */
	/* casas decimais, atribui-se 80.                         */
	
	if (chaveOriginal < 10) {
		chave += 80;
	} 
	
	/* Tabela switch de codifica��o de chave */
	
	for(int i=0; i<2; i++) {
		switch(numeros[i]) {
			case 0:
				chave += 0;
				break;
			case 1:
				chave += 4;
				break;
			case 2:
				chave += 5;
				break;
			case 3:
				chave += 1;
				break;
			case 4:
				chave += 6;
				break;
			case 5:
				chave += 7;
				break;
			case 6:
				chave += 8;
				break;
			case 7:
				chave += 9;
				break;
			case 8:
				chave += 2;
				break;
			case 9:
				chave += 3;
				break;
			case 10: 
				chave += 50;
				break;
			case 20:
				chave += 30;
				break;
			case 30:
				chave += 60;
				break;
			case 40:
				chave += 90;
				break;	
			default:
				break;
				// n�o fa�a nada.	
		}
	}
	
	return chave;
}

/* codificar() codifica a string txtOriginal */
/* e a armazena na string destino.           */

void codificar (char* destino, char* txtOriginal) {
	char txtCodificado[10000] = ""; 	
	int chave = gerarChave(29); // Gera chave de 1 a 29.
	int contador = 0;
	
	/* Chave de codifica��o gravada na string */
	
	txtCodificado[0] = 32 + gerarChave(126);
	txtCodificado[1] = (codificarChave(chave) / 10 + '0') + 10;
	txtCodificado[2] = 32 + gerarChave(126);
	txtCodificado[3] = (codificarChave(chave) % 10 + '0') + 10;
	
	/* Codifica��o real da string de acordo com a chave */
	
	for(int i = 4; i < strlen(txtOriginal)+4; i++) {
		txtCodificado[i] = (int)txtOriginal[contador] - chave;
		contador++;
	}
	
	/* Armazena txtCodificado na string destino. */
	
	strcpy(destino, txtCodificado);
}




