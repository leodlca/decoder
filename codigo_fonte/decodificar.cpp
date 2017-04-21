/*  Esse arquivo cont�m as fun��es acionadas quando o usu�rio solicita a op��o 2 - */
/*  Decodificar no Menu Principal                                                  */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void decodificarArquivo();
void decodificarInput();
void decodificar(char*, char*);

/* decodificarMenu() � respons�vel por redirecionar o usu�rio para uma das 2 fun��es */
/* desejadas da op��o Decodificar.                                                   */

void decodificarMenu() {
	char escolhaStr[50];
	int escolha;
	bool repetir;

	printf("*********************************************************\n");
	printf("1 - Decodificar arquivo (txt_codificado)\n");
	printf("2 - Decodificar texto do usuario\n\n");
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
			decodificarArquivo();
			repetir = false;
			break;
		case 2:
			system("cls");
			decodificarInput();
			repetir = false;
			break;
		default:
			printf("Entrada Invalida\n\n");
			break;
		}
	} while (repetir);
}

/*	decodificarArquivo() ler� a string contida em txt_codificado e a traduzir� por meio */
/*	da fun��o decodificar().                                                            */

void decodificarArquivo() {
	int contador = 0;
	char txtOriginal[10000],
		txtDecodificado[10000],
		data[80];

	/* Gera uma string com a data e hor�rio atual  */

	dataAtual(data);

	/* L� arquivo e decodifica a string nele contida. */

	lerArquivo(txtOriginal, "txt_codificado.txt");
	decodificar(txtDecodificado, txtOriginal);

	/* Caso o arquivo esteja vazio, lan�ar erro. */

	if (!temTexto("txt_codificado.txt")) {
		strcpy(txtDecodificado, "\nERRO: O Arquivo txt_decodificado nao contem texto.\n");
	}

	/* Exibe o Resultado e a data atual. */

	printf("Traduzido e arquivado em txt_decodificado.txt as %s\n\n%s\n\n", data, txtDecodificado);

	/* Armazena dados nos seus respecitos arquivos de registro */
	/* de sistema e usu�rio.                                   */

	salvarArquivo("txt_decodificado.txt", "w", txtDecodificado, "", "");
	salvarArquivo("user_log.txt", "a", txtDecodificado, "DECODIFICA��O", data);

	/* Espera alguma entrada do usu�rio para voltar ao menu principal. */

	printf("Pressione qualquer tecla para voltar ao menu... ");
	getch();

}

/* 	decodificarInput() decodifica uma string inserida pelo usu�rio e */
/*  a armazena nos respecitos arquivos de registro.                    */

void decodificarInput() {
	char txtOriginal[10000] = "",
		 txtDecodificado[10000],
		 data[80];

	dataAtual(data);

	/* Pede ao usu�rio o texto a ser decodificado */

	fflush(stdin);
	printf("Insira o texto que voce deseja decodificar: ");
	fgets(txtOriginal, 9999, stdin);

	/* Decodifica o texto inserido pelo usu�rio e o armazena */
	/* em uma string.                                        */

	decodificar(txtDecodificado, txtOriginal);

	/* Exibe o resultado e a data atual */

	printf("\nTraduzido e arquivado em codificado.txt as %s\n\n%s\n\n", data, txtDecodificado);

	/* Armazena dados nos seus respecitos arquivos de registro */
	/* de sistema e usu�rio.                                   */

	salvarArquivo("txt_decodificado.txt", "w", txtDecodificado, "", "");                                          
	salvarArquivo("user_log.txt", "a", txtDecodificado, "DECODIFICA��O", data);

	/* Espera alguma entrada do usu�rio para voltar ao menu principal. */

	printf("\nPressione qualquer tecla para voltar ao menu ");
	getch();

}

/* decodificarChave() recebe a chave original como argumento */
/* e a retorna codificada no tipo int.                       */

int decodificarChave (int chaveOriginal) {
	int chave = 0;
	
	/* Formata a chave */
	
	int numeros[2] = {(chaveOriginal/10)*10, chaveOriginal%10};
	
	/* Tabela switch de decoficica��o de chave */
	
	for(int i = 0; i < 2; i++){
		switch(numeros[i]) {
			case 7:
				chave += 5;
				break;
			case 4:
				chave += 1;
				break;
			case 5:
				chave += 2;
				break;
			case 1:
				chave += 3;
				break;
			case 6:
				chave += 4;
				break;
			case 80:
			case 0:
				chave += 0;
				break;
			case 8:
				chave += 6;
				break;
			case 9:
				chave += 7;
				break;
			case 2:
				chave += 8;
				break;
			case 3:
				chave += 9;
				break;
			case 50: 
				chave += 10;
				break;
			case 30:
				chave += 20;
				break;
			case 60:
				chave += 30;
				break;
			case 90:
				chave += 40;
				break;
			default:
				// n�o fa�a nada
				break;		
		}
	}
	return(chave);
}

/* decodificar() decodifica a string txtOriginal e */
/* a grava na string destino                       */

void decodificar (char* destino, char* txtOriginal) {
	
	char txtDecodificado[10000] = "";
	
	int chave_1 = ((int)txtOriginal[1] - '0') - 10;
	int chave_2 = ((int)txtOriginal[3] - '0') - 10;
	int chave = decodificarChave(chave_1*10 + chave_2);
	int contador = 0;
	
	if(((int)txtOriginal[1] - '0') - 10 > 9 || ((int)txtOriginal[3] - '0') - 10 > 9) {
		strcpy(destino, "ERRO: String entrada pelo usuario nao contem chave de decodificacao.");
		return;
	}
	
	for(int i=4; i < strlen(txtOriginal); i++){
		txtDecodificado[contador] = (int)txtOriginal[i] + chave;
		contador++;
	}
	
	strcpy(destino, txtDecodificado);
}

