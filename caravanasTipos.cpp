//
// Created by adm on 24/12/2024.
//

#include "caravana.h"
#include "caravanasTipos.h"
#include "item.h"
#include <iostream>
#include "combate.h"

using namespace std;

Comercio::Comercio(int id, int pos) : Caravana(id, pos, 0, 40, 200, 200, 20, 2, "Comercio", false, 5, false) {}

void
Comercio::mover(int colunas, string &direcao, Grelha &grelha, int pos, int id, vector<Item *> &item, Jogador &jogador,
                vector<Caravana *> &caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

void Comercio::comportamentoAutonomo(Grelha &grelha, Jogador &jogador, vector<Item *> &itens,
                                     vector<Caravana *> &caravanasAtivas) {
    if (getTripulantes() == 0) {
        moverAleatorio(grelha, getPosicao(), getId(), itens, jogador, caravanasAtivas);
        return;
    }

    if (Item *itemProximo = encontrarItemProximo(itens, 2, grelha)) { // Alcance de 2 para itens
        moverPara(itemProximo->getPos(), grelha, itens, jogador, caravanasAtivas); // Move para pegar o item
    }
    if (Caravana *caravanaProxima = encontrarCaravanaProxima(caravanasAtivas, grelha)) {
        moverPara(caravanaProxima->getPosicao(), grelha, itens, jogador,
                  caravanasAtivas); // Move em direção da caravana mais próxima
    } else {
        moverAleatorio(grelha, getPosicao(), getId(), itens, jogador,
                       caravanasAtivas); // Caso contrário, move-se aleatoriamente
    }
}

Militar::Militar(int id, int pos) : Caravana(id, pos, 0, 5, 400, 400, 40, 3, "Militar", false, 7, false) {}

void
Militar::mover(int colunas, string &direcao, Grelha &grelha, int pos, int id, vector<Item *> &item, Jogador &jogador,
               vector<Caravana *> &caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

void Militar::comportamentoAutonomo(Grelha &grelha, Jogador &jogador, vector<Item *> &itens,
                                    vector<Caravana *> &caravanasAtivas) {
    if (getTripulantes() == 0) {
        string movimento = getUltimoMovimento();
        mover(grelha.getColunas(), movimento, grelha, getPosicao(), getId(), itens, jogador, caravanasAtivas);
    } else {
        Caravana *barbaraProxima = encontrarCaravanaBarbaraProxima(caravanasAtivas, grelha,
                                                                   6); // Encontrar bárbara próxima
        if (barbaraProxima) {
            moverPara(barbaraProxima->getPosicao(), grelha, itens, jogador, caravanasAtivas); // Persegue bárbara
        } else {
            // Fica parada
        }
    }
}

Secreta::Secreta(int id, int pos) : Caravana(id, pos, 0, 300, 300, 300, 15, 2, "Secreta", false, 10, false) {}

void
Secreta::mover(int colunas, string &direcao, Grelha &grelha, int pos, int id, vector<Item *> &item, Jogador &jogador,
               vector<Caravana *> &caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

Barbara::Barbara(int id, int pos) : Caravana(id, pos, 0, 0, 0, 0, 40, 1, "Barbara", false, 60, true) {}

void Barbara::comportamentoAutonomo(Grelha &grelha, Jogador &jogador, vector<Item *> &itens,
                                    vector<Caravana *> &caravanasAtivas) {
    Caravana *caravanaProxima = encontrarCaravanaBarbaraProxima(caravanasAtivas, grelha,
                                                                8); // Encontrar caravana próxima
    if (caravanaProxima) {
        moverPara(caravanaProxima->getPosicao(), grelha, itens, jogador, caravanasAtivas); // Persegue caravana
    } else {
        moverAleatorio(grelha, getPosicao(), getId(), itens, jogador, caravanasAtivas);
    }
    if (Combate::saoAdjacentes(grelha.getColunas(), caravanasAtivas)) {
        if (caravanaProxima) {
            Combate::realizarCombate(*this, *caravanaProxima);
        }
    }
}