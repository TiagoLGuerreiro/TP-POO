//
// Created by adm on 27/12/2024.
//

#ifndef BUFFER_H
#define BUFFER_H
#include <string>
using namespace std;

void deleteBuffer(char*& buffer);
char* save(string nome,const char* data);
void lists();
void loads(string nome);
void limparBuffer(string nome);

#endif // BUFFER_H

