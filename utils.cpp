//
// Created by adm on 24/12/2024.
//
#include "utils.h"
#include "item.h"
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