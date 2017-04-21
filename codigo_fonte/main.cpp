/* Esse arquivo contém a função main, responsável por controlar a */
/* entrada do usuário e chamar as outras funções                  */

#include "header.h"
#include <stdio.h>
#include <conio.h>

/* Variável global para controle de login */

bool loginFeito = false;

/* main() chama todas as outras funções e controla o login */

int main() {
	while (true) {
		if (loginFeito) {
			while (true) {
				menu();
			}
		}
		else if (temSenha()) {
			pedirSenha();
		}
		else if (!temSenha()) {
			novaSenha();
		}
	}
}
