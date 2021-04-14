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

#include "libs/funcs.h"

//Funçao principal
int main(int argc, char *argv[]){
	int status;
	if(argc != 2 ){
		fprintf(stderr, "Use: %s [DIRETORIO]", argv[0]);
		return 1;
	}

	WhatIsDir(argv[1]);
	connectserver();
	
	return 0;
}


