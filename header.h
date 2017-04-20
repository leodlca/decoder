/*          Funções de Menu          */

void menu();
void codificarMenu();
void decodificarMenu();
void teste();
void pedirSenha();
bool temSenha();
void novaSenha();
void removerArquivos();

/*          Funções específicas          */

void codificar(char* destino, char* txtOriginal);
void decodificar(char* destino, char* txtOriginal);
int gerarChave(int limite);

/*          Funções independentes          */


/* Arquivos */

bool temArquivo(const char* diretorio);
void lerArquivo(char* destino, const char* diretorio);
void salvarArquivo(const char* arqNome, const char* modo, const char* dados, const char* userLog, 
	const char* data);

/* Strings e data */

int stringNum(const char* entrada);
void dataAtual(char* destino);
bool temTexto(const char* diretorio);
bool temCaracteres(const char* string);

