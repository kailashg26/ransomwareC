#include <stdio.h>
#include <stdlib.h>
#include "libs/funcs.h"


int main(int argc, char *argv[]){

	char *uuid;
	char *hostname;
	if(argc != 2 ){
		fprintf(stderr, "Use: %s [DIRETORIO]", argv[0]);
		return 1;
	}
	hostname = getpcname();
	uuid = getuuid();
	WhatIsDir(argv[1]);
	connectserver(uuid, hostname);

	return 0;
}
