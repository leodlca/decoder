/*  Esse arquivo contém as funções acionadas quando o usuário solicita a opção 1 - */
/*  Codificar no Menu Principal                                                    */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

extern int chaveAtual;

/* Cabeçalho do arquivo */

void codificarArquivo();
void codificarInput();
void codificar(char*, char*);

/* codificarMenu() é responsável por redirecionar o usuário para uma das 2 funções    */
/* desejadas da opção Codificar.                                                      */

void codificarMenu() {
	char escolhaStr[50];
	int escolha;
	bool repetir;

	printf("*********************************************************\n");
	printf("1 - Codificar arquivo (txt_decodificado)\n");
	printf("2 - Codificar texto do usuario\n\n");
	printf("*********************************************************\n");

	/* O Menu será exibido ao menos uma vez, e entrará em loop */
	/* até que uma opção válida seja selecionada.              */

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

/*	codificarArquivo() lerá a string contida em txt_decodificado e a traduzirá por meio */
/*	da função codificar().                                                              */

void codificarArquivo() {

	char txtOriginal[10000],
		txtCodificado[10000],
		data[80];
		
	/* Gera uma string com a data atual, lê arquivo e */
	/* decodifica a string nele contida.              */

	dataAtual(data);
	lerArquivo(txtOriginal, "txt_decodificado.txt");
	codificar(txtCodificado, txtOriginal);

	/* Caso o arquivo esteja vazio, lançar erro. */

	if (!temTexto("txt_decodificado.txt")) {
		strcpy(txtCodificado, "\nERRO: O Arquivo txt_decodificado nao contem texto.\n");
	}

	/* Exibe o resultado e a data atual. */

	printf("Traduzido e arquivado em txt_decodificado.txt as %s\n\n%s\n\n", data, txtCodificado);

	/* Armazena o conteúdo decodificado formatado nos arquivos de registro */

	salvarArquivo("user_log.txt", "a", txtCodificado, "CODIFICAÇÃO", data);
	salvarArquivo("txt_codificado.txt", "w", txtCodificado, "", "");

	/* Espera alguma entrada do usuário para voltar ao menu principal. */

	printf("Pressione qualquer tecla para voltar ao menu... ");
	getch();

}

/* 	codificarInput() lerá uma string inserida pelo usuário e a traduzirá por meio */
/*	da função codificar().                                                        */

void codificarInput() {

	char txtOriginal[10000] = "", 
		 txtCodificado[10000],
		 data[80];
	
	/* Pede ao usuário o texto a ser codificado. */

	system("cls");
	printf("Insira o texto a ser codificado: ");
	fgets(txtOriginal, 9999, stdin); // fgets() é uma solução mais segura à gets().

	/* Codifica o texto entrado pelo usuário. */

	dataAtual(data);
	codificar(txtCodificado, txtOriginal);

	/* Exibe o conteúdo traduzido com a data. */

	printf("\nTraduzido e arquivado em txt_codificado.txt as %s\n\n%s\n\n", data, txtCodificado);

	/* Salvar Conteúdo. */

	salvarArquivo("user_log.txt", "a", txtCodificado, "CODIFICAÇÃO", data);
	salvarArquivo("txt_codificado.txt", "w", txtCodificado, "", "");
	
	/* Espera entrada do usuário para voltar ao menu. */

	printf("\nPressione qualquer tecla para voltar ao menu... ");
	getch();

}                             

/* gerarChave() gera um número aleatório */
/* que vai de 1 até o argumento limite.  */                   

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
	/* pois se x < 10, 10/10*10 = 0, para evitar confusão de  */
	/* casas decimais, atribui-se 80.                         */
	
	if (chaveOriginal < 10) {
		chave += 80;
	} 
	
	/* Tabela switch de codificação de chave */
	
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
				// não faça nada.	
		}
	}
	
	return chave;
}

/* codificar() codifica a string txtOriginal */
/* e a armazena na string destino.           */

void codificar (char* destino, char* txtOriginal) {
	char txtCodificado[10000] = "",
		txtTabela[10000];
		
	const char* atual;
	const char* atual_1;
			
	int chave = gerarChave(29); // Gera chave de 1 a 29.
	int contador = 0;
	
	/* Chave de codificação gravada na string */
	
	txtCodificado[0] = 32 + gerarChave(126);
	txtCodificado[1] = (codificarChave(chave) / 10 + '0') + 10;
	txtCodificado[2] = 32 + gerarChave(126);
	txtCodificado[3] = (codificarChave(chave) % 10 + '0') + 10;
	
	/* Codificação real da string de acordo com a chave */
	
	for(int i = 4; i < strlen(txtOriginal)+4; i++) {
		txtCodificado[i] = (int)txtOriginal[contador] - chave;
		
		atual = &txtOriginal[contador];
		
		strncat(txtTabela, atual, 1);
		strcat(txtTabela, "\t");
		
		atual_1 = &txtCodificado[i];
		
		strncat(txtTabela, atual_1, 1);
		strcat(txtTabela, "\n");
		
		contador++;
	}
	
	/* Armazena txtCodificado na string destino. */
	
	salvarArquivo("tabela.txt", "w", txtTabela, "", "");
	strcpy(destino, txtCodificado);
}


