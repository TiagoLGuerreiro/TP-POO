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
    cout << novoBuffer;
    return novoBuffer;  // Retorna o ponteiro para o buffer
}

void lists(){
    for (const auto& entry : buffers) {
        cout << "Nome do buffer: " << entry.first << endl;
    }
}

void loads(string nome){
    for (const auto& entry : buffers) {
        if(entry.first == nome)
            cout << "Nome do buffer: " << entry.first << endl;
            cout << "Conteudo - \n" << entry.second;
    }
}

void limparBuffer(string nome) {
    auto it = buffers.find(nome);  // Tenta encontrar o buffer pelo nome
    if (it != buffers.end()) {  // verifica se o buffer existe
        delete[] it->second;  // Libera a memória alocada para o buffer
        buffers.erase(it);  // Remove o buffer do mapa
        cout << "Buffer '" << nome << "' apagado com sucesso!" << endl;
    } else
        cout << "Buffer '" << nome << "' nao encontrado!" << endl;
}