//
// Created by adm on 27/12/2024.
//

#include "buffer.h"
#include "grelha.h"
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <sstream>
using namespace std;

unordered_map<string, char*> buffers;

void save(string nome, Grelha& grelha){
// Captura a saída da grelha como uma string
    ostringstream oss;
    for (int i = 0; i < grelha.getLinhas(); ++i) {
        for (int j = 0; j < grelha.getColunas(); ++j) {
            oss << grelha.getMapa()[i * grelha.getColunas() + j].getTipo();
        }
        oss << '\n';  // Nova linha após cada linha do mapa
    }

    // Converte o conteúdo para um buffer
    const string& mapaString = oss.str();
    int tamanho = mapaString.size() + 1;  // Inclui o terminador nulo '\0'
    char* novoBuffer = new char[tamanho];
    strcpy(novoBuffer, mapaString.c_str());

    // Armazena o buffer no mapa associado ao nome
    buffers[nome] = novoBuffer;

    cout << "Mapa salvo com o nome: " << nome << endl;
}

void lists(){
    for (const auto& entry : buffers) {
        cout << "Nome do buffer: " << entry.first << endl;
    }
}

void loads(string nome){
    for (const auto& entry : buffers) {
        if(entry.first == nome){
            cout << "Nome do buffer: " << entry.first << endl;
            cout << "Conteudo - \n" << entry.second;
        }
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