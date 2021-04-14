#include <stdio.h>
#include "libs/funcs.h"


int main(int argc, char *argv[]){
	if(argc != 2 ){
		fprintf(stderr, "Use: %s [DIRETORIO]", argv[0]);
		return 1;
	}

	WhatIsDir(argv[1]);
	connectserver();
	
	return 0;
}


