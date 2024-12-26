//
// Created by adm on 24/12/2024.
//

#include "caravana.h"
#include "caravanasTipos.h"
#include "item.h"
#include <iostream>
using namespace std;

Comercio::Comercio(int id, int pos) : Caravana(id, pos, 200, 40, 20, 2, "Comercio") {}

void Comercio::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

void Comercio::comportamentoAutonomo(Grelha& grelha, Jogador& jogador, vector<Item*>& itens, vector<Caravana*>& caravanasAtivas) {
    if (getTripulantes() == 0) {
        moverAleatorio(grelha, getPosicao(), getId());
        return;
    }

    if (Item* itemProximo = encontrarItemProximo(itens, 2, grelha)) { // Alcance de 2 para itens
        moverPara(itemProximo->getPos(), grelha); // Move para pegar o item
    } if (Caravana* caravanaProxima = encontrarCaravanaProxima(caravanasAtivas, grelha)) {
        moverPara(caravanaProxima->getPosicao(), grelha); // Move em direção da caravana mais próxima
    } else {
        moverAleatorio(grelha, getPosicao(), getId()); // Caso contrário, move-se aleatoriamente
    }
}

Militar::Militar(int id, int pos) : Caravana(id, pos, 400, 5, 40, 3,"Militar") {}

void Militar::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

void Militar::comportamentoAutonomo(Grelha& grelha, Jogador& jogador, vector<Item*>& itens, vector<Caravana*>& caravanasAtivas) {
    /*Caravana* barbaraProxima = encontrarCaravanaBarbaraProxima(caravanasAtivas, 6); // Encontrar bárbara próxima
    if (barbaraProxima) {
        moverPara(barbaraProxima->getPosicao(), grelha); // Persegue bárbara
    } else {
        // Fica parada
    }*/
}

Secreta::Secreta(int id, int pos) : Caravana(id, pos, 300, 20, 15, 2, "Secreta") {}

void Secreta::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

Barbara::Barbara(int id, int pos) : Caravana(id, pos, 0, 0, 40, 1, "Barbara") {}

void Barbara::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) {
}