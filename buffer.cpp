//
// Created by adm on 27/12/2024.
//

#include "buffer.h"
#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;

unordered_map<string, char*> buffers;

void deleteBuffer(char*& buffer) {
    if (buffer != nullptr) {
        delete[] buffer; // Liberta a memória
        buffer = nullptr; // Evitar ponteiro pendente
        cout << "Buffer deleted com sucesso." << endl;
    } else {
        cout << "Copia do buffer nao existe." << endl;
    }
}

char* save(string nome, const char* data){

    // Atribui a memória para o novo buffer
    int tamanho = strlen(data) + 1;  // Inclui o terminador nulo '\0'
    char* novoBuffer = new char[tamanho];

    // Copia os dados para o novo buffer
    strcpy(novoBuffer, data);

    // Armazena o buffer no mapa, associado ao nome
    buffers[nome] = novoBuffer;

    return novoBuffer;  // Retorna o ponteiro para o buffer
}
