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

    if (caravana1.getGalinha() > 0) {
        cout << "Devido Ao Seu Item Acomulou " << caravana1.getGalinha() << " Galinhas" << endl;
        cout << "Elas Irao Ajuda-lo Neste Combate!" << endl;

        sorteio1 += floor(caravana1.getGalinha());
        caravana1.setGalinha(0);
    }

    if (sorteio1 > sorteio2) { //caravana 1 Ganha
        int perda = floor(caravana1.getTripulantes() * 0.2);

        cout << "A Caravana Barbara Ganhou!" << endl;

        caravana1.setTripulantes(floor(caravana1.getTripulantes() - perda));
        caravana2.setTripulantes(floor(caravana2.getTripulantes() - (2 * perda)));

        if (caravana2.getTripulantes() <= 0) {
            int agua2 = caravana2.getAgua();
            int agua1 = caravana1.getAgua();

            caravana1.setAgua(agua1 + agua2);

            if (caravana1.getAgua() > caravana1.getCapacidadeAgua())
                caravana1.setAgua(caravana1.getCapacidadeAgua());

            caravana2.setDestruida(true);
        }
    } else if (sorteio2 > sorteio1) { //caravana 2 Ganha
        int perda = floor(caravana2.getTripulantes() * 0.2);

        cout << "A Caravana De " << caravana2.getTipo() << " Ganhou O Combate." << endl;

        caravana2.setTripulantes(floor(caravana2.getTripulantes() - perda));
        caravana1.setTripulantes(floor(caravana1.getTripulantes() - (2 * perda)));

        if (caravana1.getTripulantes() <= 0) {
            int agua2 = caravana2.getAgua();
            int agua1 = caravana1.getAgua();

            caravana2.setAgua(agua1 + agua2);

            if (caravana2.getAgua() > caravana2.getCapacidadeAgua())
                caravana2.setAgua(caravana2.getCapacidadeAgua());

            caravana1.setDestruida(true);
        }
    }
}
