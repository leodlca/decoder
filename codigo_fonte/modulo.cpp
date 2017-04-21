/* Esse arquivo t�m como prop�sito tornar o programa ainda mais modular ao   */
/* tornar o c�digo respons�vel manipular arquivos em fun��es independentes.  */

#include "header.h" // Cabe�alho que une as fun��es de todos os arquivos.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

/* salvarArquivo() recebe 5 par�metros, s�o eles:                        */
/*                                                                       */
/* arqNome = string com o nome do arquivo, com extens�o incluida         */
/* modo = string com o modo de execu��o (w, r, a, r+, etc)               */
/* dados = string com todos os dados a serem escritos                    */
/* [userLog] = string com o t�tulo para a formata��o dos dados em algo   */
/* mais agrad�vel ao usu�rio.                                            */
/* [data] = string formatada com a data, para os mesmos fins de userLog  */
/*                                                                       */
/* OBS: os 2 ultimos s�o opcionais, para n�o utiliz�-los insira como     */
/* par�metro uma string vazia "".                                        */

void salvarArquivo(const char* arqNome, const char* modo, const char* dados, const char* userLog, 
	const char* data) {
	FILE *arquivo;
	arquivo = fopen(arqNome, modo);

	/* Lan�a erro caso o arquivo n�o possa ser aberto */

	if (arquivo == NULL) {
		system("cls");
		printf("\nErro de grava��o: O Arquivo %s nao pode ser aberto.", arqNome);
		printf("\n\nPossiveis causas: ");
		printf("\n\n- O programa nao tem permissao necessaria.");
		printf("\n- O arquivo esta aberto neste instante.");
		printf("\n- Arquivo corrompido.");
		printf("\n\nPressione qualquer tecla para fechar o programa... ");
		getch();
		exit(1);
	}

	/* Checa se os par�metros opcionais foram inseridos ou n�o   */
	/* para realizar a formata��o da string e insere os dados no */
	/* arquivo.                                                  */

	if (!(strcmp(userLog, "") == 0 || strcmp(data, "") == 0)) {
		fprintf(arquivo, "\n******************************%s******************************\n", userLog);
		fprintf(arquivo, "Traduzido as %s\n____________________________________________________________\n\n", data);
		fprintf(arquivo, "%s\n\n____________________________________________________________\n", dados);
	}
	else {
		fprintf(arquivo, "%s", dados);
	}

	/* Fecha arquivo para evitar erros. */

	fclose(arquivo);
};

/* lerArquivo() recebe uma array char e uma string constante como */
/* argumento. O primeiro � a string na qual o texto presente no   */
/* arquivo ser� gravada, e o segundo � o diret�rio do arquivo.     */

void lerArquivo(char* destino, const char* diretorio) {
	FILE *arquivo;
	arquivo = fopen(diretorio, "r");

	char conteudo[10000] = "";
	int contador = 0;

	/* Lan�a erro caso o arquivo n�o possa ser aberto */

	if (arquivo == NULL) {
		system("cls");
		printf("Erro de leitura: O Arquivo %s nao pode ser lido.", diretorio);
		printf("\n\nPossiveis causas: ");
		printf("\n\n- O programa nao tem a permissao necessaria.");
		printf("\n- Arquivo esta aberto neste instante.");
		printf("\n- Arquivo corrompido.");
		printf("\n- Arquivo nao existe. ");
		printf("\n\nSUGESTAO:\n\nCaso voce esteja executando a opcao 1 do menu decodificar ou");
		printf("\ncodificar, verifique se o arquivo correspondente foi criado.");
		printf("\n\nPressione qualquer tecla para fechar o programa... ");
		getch();
		exit(1);
	}

	rewind(arquivo);

	while (!feof(arquivo)) {
		fscanf(arquivo, "%c", &conteudo[contador]);
		contador++;
	}

	conteudo[strcspn(conteudo, "\n")] = '\0';

	fclose(arquivo);

	strcpy(destino, conteudo);
}

/* temArquivo() retorna true ou false se o arquivo -> diret�rio existir */

bool temArquivo(const char* diretorio) {
	FILE *arquivo;
	arquivo = fopen(diretorio, "r");

	if (arquivo == NULL) {
		return(false);
	}
	
	return(true);
}

/* removerArquivos() remove todos os arquivos de registro criados. */

void removerArquivos() {
	unlink("txt_decodificado.txt");
	unlink("txt_codificado.txt");
	unlink("user_log.txt");
	salvarArquivo("pass.txt", "w", "", "", "");
	unlink("pass.txt");
	
	printf("\nSenha Resetada e Arquivos deletados.");
}

/* stringNum checa se uma string � formada apenas por caract�res num�ricos.    */
/* caso seja, o numero da string � retornado como int, caso n�o seja, o n�mero */
/* -9999 � retornado.                                                          */

int stringNum(const char* entrada) {
	for (int i = 0; i < strlen(entrada) - 1; i++) {
		if (isdigit(entrada[i]) == 0) {
			return (-9999);
		}
	}

	return(atoi(entrada));
}

/* Checa se o arquivo -> diret�rio cont�m texto ou n�o, e */
/* respectivamente retorna true ou false.                 */

bool temTexto(const char* diretorio) {
	char checar[10000] = "";

	lerArquivo(checar, diretorio);

	if (strcmp(checar, "") == 0 || strcmp(checar, " ") == 0) {
		return(false);
	}

	return(true);
}

/* Checa se uma string cont�m ou n�o caracteres (est� vazia), e */
/* respectivamente retorna true ou false                        */

bool temCaracteres(const char* string) {
	if (strcmp(string, "") == 0 || strcmp(string, " ") == 0) {
		return(false);
	}
	return(true);
}
