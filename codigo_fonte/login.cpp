/* Esse cont�m todas as fun��es necess�rias para controlar o login */
/* do usu�rio.                                                     */
/* OBS: A senha entrada pelo usu�rio � codificada por padr�o.      */

#include "header.h"

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

extern bool loginFeito;

/* pedirSenha() � respons�vel pelo login do usu�rio, ela recebe */
/* uma string digitada pelo usu�rio, verifica se ela � igual a  */
/* string no arquivo senha.txt e deixa o usu�rio entrar ou n�o. */

void pedirSenha() {
	int chances = 3;
	char senhaDigitada[30],
		senhaCodificada[30],
		senhaDecodificada[30];

	printf("Caso todas as suas 3 tentativas sejam esgotadas, todos os\n");
	printf("arquivos de registro serao deletados e sua senha sera resetada.\n");

	lerArquivo(senhaCodificada, "pass.txt");
	decodificar(senhaDecodificada, senhaCodificada);
	
	/* D� ao usu�rio 3 chances para acertar a senha, ao final da */
	/* �ltima tentativa, todos os arquivos .txt, com exce��o do  */
	/* arquivo teste, s�o deletados.                             */

	for (int i = 0; i < 3; i++) {
		printf("\n[%d chance(s)] Insira sua senha: ", chances);
		fgets(senhaDigitada, 29, stdin);
		
		//senhaDigitada[strcspn(senhaDigitada, "\n")] = '\0'; ex-solu��o para arrumar strcmp().
	
		if (strcmp(senhaDigitada, senhaDecodificada) == 0) {
			loginFeito = true;
			break;
		}
		else {
			chances--;
		}

		if (chances == 0) {
			removerArquivos();
			printf("\n\nPressione qualquer tecla para fechar o programa... ");
			getch();
			exit(1);
		}
	}
}

/* temSenha() retorna true se uma senha j� tenha sido criada */
/* e vice-versa.                                             */

bool temSenha() {
	
	if (!temArquivo("pass.txt") || !temTexto("pass.txt")) {
		return(false);
	}

	return(true);
}

/* novaSenha() recebe uma nova senha definida pelo usu�rio */
/* e a grava no arquivo senha.txt                          */

void novaSenha() {
	/* As senhas s�o codificadas por padr�o. */
	
	int chances = 3, contador = 0;
	char senhaDigitada[30],
		senhaDigitada_2[30],
		senhaCodificada[30], 
		data[80];

	dataAtual(data);

	printf("Favor inserir uma nova senha de ate 30 caracteres: ");
	fgets(senhaDigitada, 29, stdin);
	printf("\nConfirme sua senha: ");
	fgets(senhaDigitada_2, 29, stdin);
	
	/* Repete a fun��o caso o usu�rio erre a confirma��o de senha */
	
	if (strcmp(senhaDigitada, senhaDigitada_2) != 0) {
		printf("\nAs senhas digitadas nao sao iguais.\n\n");
		novaSenha();
		return;
	}

	codificar(senhaCodificada, senhaDigitada);
	
	salvarArquivo("pass.txt", "w", senhaCodificada, "", "");
	salvarArquivo("user_log.txt", "a", "CONFIDENCIAL", "TROCA DE SENHA", data);

	loginFeito = true;

}
