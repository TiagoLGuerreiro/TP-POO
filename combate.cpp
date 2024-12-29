//
// Created by tiago on 26/11/2024.
//

#include "combate.h"
#include <iostream>
#include <sstream>
#include <cmath>

bool Combate::saoAdjacentes(int colunas, vector<Caravana *> &caravanasAtivas) {
    int linha1, coluna1, linha2, coluna2;
    bool check;
    for (const auto &caravana: caravanasAtivas) {
        linha1 = caravana->getPosicao() / colunas, coluna1 = caravana->getPosicao() % colunas;
        for (const auto &caravana2: caravanasAtivas) {
            linha2 = caravana2->getPosicao() / colunas, coluna2 = caravana2->getPosicao() % colunas;
            if ((abs(linha1 - linha2) + abs(coluna1 - coluna2)) == 1) // verificar a adjacência
                check = true;
        }
    }

    return check;
}

void Combate::realizarCombate(Caravana &caravana1, Caravana &caravana2) {
    int sorteio1 = rand() % (caravana1.getTripulantes() + 1);
    int sorteio2 = rand() % (caravana2.getTripulantes() + 1);

    if (sorteio1 > sorteio2) { //caravana 1 Ganha
        int perda = floor(caravana1.getTripulantes() * 0.2);

        caravana1.setTripulantes(floor(caravana1.getTripulantes() - perda));
        caravana2.setTripulantes(floor(caravana2.getTripulantes() - (2 * perda)));

        if (caravana2.getTripulantes() <= 0) {
            int agua2 = caravana2.getAgua();
            int agua1 = caravana1.getAgua();

            caravana1.setAgua(agua1 + agua2);

            if(caravana1.getAgua() > caravana1.getCapacidadeAgua())
                caravana1.setAgua(caravana1.getCapacidadeAgua());

            caravana2.setDestruida(true);
        }
    } else if (sorteio2 > sorteio1) { //caravana 2 Ganha
        int perda = floor(caravana2.getTripulantes() * 0.2);

        caravana2.setTripulantes(floor(caravana2.getTripulantes() - perda));
        caravana1.setTripulantes(floor(caravana1.getTripulantes() - (2 * perda)));

        if (caravana1.getTripulantes() <= 0) {
            int agua2 = caravana2.getAgua();
            int agua1 = caravana1.getAgua();

            caravana2.setAgua(agua1 + agua2);

            if(caravana2.getAgua() > caravana2.getCapacidadeAgua())
                caravana2.setAgua(caravana2.getCapacidadeAgua());

            caravana1.setDestruida(true);
        }
    }
}

/*void resolverCombates(vector<Caravana *> &caravanasAtivas, Grelha &grelha) {
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