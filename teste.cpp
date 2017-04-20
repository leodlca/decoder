/* Esse arquivo contém as funções necessárias para o funcionamento do */
/* menu Teste, requisitado como prova de funcionamento do programa    */

#include "header.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

void teste() {

	char fraseOriginal[100],
		fraseCodificada[100],
		fraseDecodificada[100],
		data[80];

	/* Gera uma string formatada com a data e o horario atual */

	dataAtual(data);
	
	if(!temArquivo("teste.txt")) {
		salvarArquivo("teste.txt", "w", "The quick brown jumps over the lazy dog", "", "");
	}

	/* Exibição do Menu Teste */

	printf("*********************************************************\n");
	printf("Bem-Vindo ao Menu Teste.\n\n");
	printf("Este menu tem como funcao provar o bom funcionamento do \n");
	printf("projeto, para isso, os seguintes passos serao realizados: \n\n");
	printf("1 - A frase 'The quick brown jumps over the lazy dog' sera \n");
	printf("codificada, exibida no console, e armazenada no arquivo \n");
	printf("txt_codificado.txt.\n\n");
	printf("2 - A mesma frase sera decodificada, exibida no console  \n");
	printf("e armazenada no arquivo txt_decodificado.txt.\n\n");
	printf("*********************************************************\n\n");
	printf("Pressione qualquer tecla para iniciar o primeiro passo... ");
	getch();

	system("cls");

	/* Lê o arquivo teste.txt e codifica a string contida no mesmo. */

	lerArquivo(fraseOriginal, "teste.txt");
	codificar(fraseCodificada, fraseOriginal);

	/* Exibe resultado e a data atual. */

	printf("\nTraduzido e arquivado em txt_codificado.txt as %s\n\n%s\n\n", data, fraseCodificada);
	
	/* Armazena dados nos seus respecitos arquivos de registro */
	/* de sistema e usuário.                                   */

	salvarArquivo("user_log.txt", "a", fraseCodificada, "TESTE-CODIFICAÇÃO", data);
	salvarArquivo("txt_decodificado.txt", "w", fraseCodificada, "", "");

	/* Espera alguma entrada do usuário para iniciar o passo 2. */

	printf("\nPressione qualquer tecla para iniciar o passo 2... ");
	getch();
	
	/**********************************************************************/
	/*                            PASSO 2                                 */
	/**********************************************************************/

	system("cls");

	/* Essa etapa não será comentada para evitar repetição de comentários */
	
	decodificar(fraseDecodificada, fraseCodificada);

	printf("\nTraduzido e arquivado em txt_codificado.txt as %s\n\n%s\n\n", data, fraseDecodificada);

	salvarArquivo("user_log.txt", "a", fraseDecodificada, "TESTE-DECODIFICAÇÃO", data);
	salvarArquivo("txt_decodificado.txt", "w", fraseDecodificada, "", "");

	printf("\nPressione qualquer tecla para voltar ao menu principal... ");
	getch();

}
