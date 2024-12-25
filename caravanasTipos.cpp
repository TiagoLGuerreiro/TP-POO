//
// Created by adm on 24/12/2024.
//

#include "caravanasTipos.h"
#include <iostream>
using namespace std;

Comercio::Comercio(int id, int pos) : Caravana(id, pos, 200, 40, 20) {}

void Comercio::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador);
}

Militar::Militar(int id, int pos) : Caravana(id, pos, 400, 5, 40) {}

void Militar::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador);
}

Secreta::Secreta(int id, int pos) : Caravana(id, pos, 300, 20, 15) {}

void Secreta::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador);
}

Barbara::Barbara(int id, int pos) : Caravana(id, pos, 0, 0, 40) {}

void Barbara::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador) {
}