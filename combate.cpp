//
// Created by tiago on 26/11/2024.
//

#include "combate.h"
#include <iostream>
#include <sstream>

bool Combate::saoAdjacentes(int colunas, vector<Caravana*>& caravanasAtivas) {
    int linha1, coluna1, linha2, coluna2;
    bool check;
    for (const auto &caravana: caravanasAtivas) {
        linha1 = caravana->getPosicao() / colunas, coluna1 = caravana->getPosicao() % colunas;
        for (const auto &caravana2: caravanasAtivas)
            linha2 = caravana2->getPosicao() / colunas, coluna2 = caravana2->getPosicao() % colunas;
        if((abs(linha1 - linha2) + abs(coluna1 - coluna2)) == 1) // verificar a adjacência
            check = true;
    }

    return check;
}
/*
void realizarCombate(Caravana &caravana1, Caravana &caravana2) {
    int sorteio1 = rand() % (caravana1.getTripulantes() + 1);
    int sorteio2 = rand() % (caravana2.getTripulantes() + 1);

    if (sorteio1 > sorteio2) {
        int perdaVencedor = caravana1.getTripulantes() * 0.2;
        int perdaPerdedor = perdaVencedor * 2;

        caravana1.perderTripulantes(perdaVencedor);
        caravana2.perderTripulantes(perdaPerdedor);

        caravana1.receberAgua(caravana2.transferirAgua(caravana1.getCapacidadeMaximaAgua()));

        if (caravana2.getTripulantes() <= 0) {
            caravana2.destruir();
        }
    } else if (sorteio2 > sorteio1) {
        int perdaVencedor = caravana2.getTripulantes() * 0.2;
        int perdaPerdedor = perdaVencedor * 2;

        caravana2.perderTripulantes(perdaVencedor);
        caravana1.perderTripulantes(perdaPerdedor);

        caravana2.receberAgua(caravana1.transferirAgua(caravana2.getCapacidadeMaximaAgua()));

        if (caravana1.getTripulantes() <= 0) {
            caravana1.destruir();
        }
    } else {
        // Empate: pode definir o que fazer nesse caso
    }
}

void resolverCombates(vector<Caravana *> &caravanasAtivas, Grelha &grelha) {
    for (size_t i = 0; i < caravanasAtivas.size(); ++i) {
        if (caravanasAtivas[i]->isDestruida()) continue;

        for (size_t j = i + 1; j < caravanasAtivas.size(); ++j) {
            if (caravanasAtivas[j]->isDestruida()) continue;

            if (saoAdjacentes(caravanasAtivas[i]->getPos(), caravanasAtivas[j]->getPos(), grelha.getColunas())) {
                realizarCombate(*caravanasAtivas[i], *caravanasAtivas[j]);
            }
        }
    }

    // Remover caravanas destruídas do vetor
    caravanasAtivas.erase(
            std::remove_if(caravanasAtivas.begin(), caravanasAtivas.end(),
                           [](Caravana *c) { return c->isDestruida(); }),
            caravanasAtivas.end()
    );
}*/