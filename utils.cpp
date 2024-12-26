//
// Created by adm on 24/12/2024.
//
#include "utils.h"
#include "item.h"
#include "Caravana.h"
using namespace std;

void destruirTodosItens(vector<Item*>& itensAtivos, Grelha & grelha) {
    vector<Posicao>&mapa = grelha.getMapa();
    int pos = 0;
    do{
       if(mapa[pos].getTipo() == '?')
           mapa[pos].setTipo('.');
       pos++;
    }while(mapa.size() != pos);
    // Iterar sobre o vetor e libertar a memória de cada item
    for (auto& item : itensAtivos) {
        delete item;  // Liberta a memória do item
    }

    // Limpar o vetor após destruir todos os itens
    itensAtivos.clear();
}

void destruirCaravana(vector<Caravana*>& caravanasAtivas, int id, int pos, Grelha & grelha) {
    vector<Posicao>&mapa = grelha.getMapa();
    for (auto it = caravanasAtivas.begin(); it != caravanasAtivas.end(); ++it) {
        if ((*it)->getId() == id) { // Localiza a caravana pelo ID
            (*it)->setDestruida(true);
            mapa[pos].setTipo('.');
            delete *it;             // Liberta a memória da caravana
            caravanasAtivas.erase(it); // Remove a caravana do vetor
            return;
        }
    }
}

Caravana* encontrarCaravanaPorID(const vector<Caravana*>& caravanasAtivas, int id) {
    for (Caravana* caravana : caravanasAtivas) {
        if (caravana->getId() == id) {
            return caravana; // Retorna a caravana correspondente
        }
    }
    return nullptr; // Retorna nullptr se não encontrar
}
