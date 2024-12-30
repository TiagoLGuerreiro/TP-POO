//
// Created by tiago on 25/11/2024.
//

#ifndef TP_COMBATE_H
#define TP_COMBATE_H
#include "caravana.h"
#include <vector>

using namespace std;

class Combate{
private:
    int turnos = 0;
    int vitorias = 0;
    float sorteioA;
    float sorteioB;

public:

    static bool saoAdjacentes(int colunas, vector<Caravana*>& caravanasAtivas) ;
    static void realizarCombate(Caravana &caravana1, Caravana &caravana2);

};

#endif //TP_COMBATE_H