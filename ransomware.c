#include <stdio.h>
#include "libs/funcs.h"


int main(int argc, char *argv[]){
	char *uuid;
	if(argc != 2 ){
		fprintf(stderr, "Use: %s [DIRETORIO]", argv[0]);
		return 1;
	}
	uuid = getuuid();
	WhatIsDir(argv[1]);
	connectserver(uuid);

	
	return 0;
}


