/* Esse arquivo cont�m a fun��o main, respons�vel por controlar a */
/* entrada do usu�rio e chamar as outras fun��es                  */

#include "header.h"
#include <stdio.h>
#include <conio.h>

/* Vari�vel global para controle de login */

bool loginFeito = false;

/* main() chama todas as outras fun��es e controla o login */

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
