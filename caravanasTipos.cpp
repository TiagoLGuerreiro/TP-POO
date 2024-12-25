//
// Created by adm on 24/12/2024.
//

#include "caravana.h"
#include "caravanasTipos.h"
#include <iostream>
using namespace std;

Comercio::Comercio(int id, int pos) : Caravana(id, pos, 200, 40, 20, "Comercio") {}

void Comercio::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

Militar::Militar(int id, int pos) : Caravana(id, pos, 400, 5, 40, "Militar") {}

void Militar::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

Secreta::Secreta(int id, int pos) : Caravana(id, pos, 300, 20, 15, "Secreta") {}

void Secreta::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) {
    Caravana::mover(colunas, direcao, grelha, pos, id, item, jogador, caravanasAtivas);
}

Barbara::Barbara(int id, int pos) : Caravana(id, pos, 0, 0, 40, "Barbara") {}

void Barbara::mover(int colunas, const string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) {
}