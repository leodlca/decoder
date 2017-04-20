#include "header.h"

#include <time.h>
#include <string.h>

/* Grava a data e horário atual na string destino. */

void dataAtual(char* destino) {
	char data[80];

	time_t rawTime;
	struct tm *info;
	time(&rawTime);
	info = localtime(&rawTime);
	strftime(data, 80, "%x - %I:%M%p", info);

	strcpy(destino, data);
}
