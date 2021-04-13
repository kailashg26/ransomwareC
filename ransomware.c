#include <stdio.h>  // Entrada e saida padrao de dados
#include <stdlib.h> // Biblioteca padrao
#include <string.h> // Tratar strings
#include <dirent.h> // Entrada de diretorios
#include <errno.h> 
#include <sys/types.h>

struct dirent *getdir;

/*
struct dirent {
    ino_t          d_ino;      
	off_t          d_off;      
	unsigned short d_reclen;   
	unsigned char  d_type;     

	char           d_name[256]; 
};
Funçao: DIR *opendir(const char *name);
	Preliminares: | MT-Safe | Pilha AS-insegura 
				  | AC-Unsafe mem fd | Consulte os Conceitos de segurança POSIX .

	A opendirfunção abre e retorna um fluxo de diretório para ler o 
	diretório cujo nome de arquivo é dirname . O fluxo tem tipo DIR *.

	Se malsucedido, opendir retorna um ponteiro nulo. Além dos erros usuais de nome
	de arquivo (consulte Erros de nome de arquivo ), as seguintes errnocondições de erro
	são definidas para esta função:

	EACCES
		A permissão de leitura foi negada para o diretório nomeado por dirname.

	EMFILE
		O processo tem muitos arquivos abertos.

	ENFILE
		O sistema inteiro, ou talvez o sistema de arquivos que contém o diretório, não pode suportar
		nenhum arquivo aberto adicional no momento. (Este problema não pode acontecer em sistemas GNU / Hurd.)

	ENOMEM
		Memória insuficiente disponível.

Função: struct dirent * readdir (DIR * dirstream )
	Preliminares: | MT-Safe | Fechadura AS-Insegura | Bloqueio AC-Inseguro | Consulte os Conceitos de segurança POSIX .
	Esta função lê a próxima entrada do diretório. Normalmente retorna um ponteiro 
	para uma estrutura que contém informações sobre o arquivo. Essa estrutura está 
	associada ao identificador dirstream e pode ser 
	reescrita por uma chamada subsequente.
*/

//Funçao que faz a criptografia de arquivos
void criptografar(char *criptografa);

//Funçao que procura arquivos & diretorios
void localedir(char *nome_diretorio);

//Verifica se é arquivo ou diretorio
int isFile(const char *name);

//Funçao principal
int main(int argc, char *argv[]){
	 
	if(argc != 2 ){
		fprintf(stderr, "Use: %s [DIRETORIO]", argv[0]);
		return 1;
	}

	localedir(argv[1]);

	return 0;
}

void localedir(char *nome_diretorio){
	/* Data Type: DIR
	 * The DIR data type represents a directory stream.
     */
	const unsigned long KILOBYTE = 1024;

	DIR *diretorio;
	char arquivo[1024];
	int isdir;
	// Function: DIR * opendir (const char *dirname)
	diretorio = opendir(nome_diretorio);
	
	if(diretorio == NULL){
		fprintf(stderr, "[INFO]: Ocorreu um erro ao abrir diretorio");
		exit(1);
	}
	//readdir esta sendo explicada no cabeçalho do codigo!
	while((getdir = readdir(diretorio)) != NULL){
		//Verifica se o diretorio guardado na d_name é .. ou .
		if(strncmp(getdir->d_name, ".", sizeof(getdir->d_name)) == 0 || 
		strncmp(getdir->d_name, "..", sizeof(getdir->d_name)) == 0) continue;
		
		//A funçao isFile retorna 0 se for diretorio & 1 para arquivo
		if( (isdir = isFile(getdir->d_name)) == 0){
			
			printf("Diretorio -> %s\n", getdir->d_name);
		}

		
	}
}

void criptografar(char *criptografa){
	// Abre o arquivo
	FILE *arq = fopen(criptografa,"w");
	if(arq == NULL)
	{
		fprintf(stderr , "[ERRO]: Erro ao abrir arquivo");
		return;
	}

	// Sobrescreve o arquivo (O CONTEUDO SERA PERDIDO)
	fputs(arquivo , arq);
	fclose(arq);

	return;
}

int isFile(const char* name)
{
    DIR* directory = opendir(name);

    if(directory != NULL){
     closedir(directory);
     return 0;
    }

    if(errno == ENOTDIR){
     return 1;
    }
    return -1;
}

