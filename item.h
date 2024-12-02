//
// Created by tiago on 25/11/2024.
//

#ifndef TP_ITEM_H
#define TP_ITEM_H
#include <string>
#include "jogador.h"
using namespace std;

class Grelha;

class Item{
private:
    int instante_entre_item;
    string tipo; // 'P' = caixa de pandora, 'A' = arca do tesouro, 'J' = jaula, 'M' = mina, 'S' = surpresa
    int duracao;
    int max_itens;

public:
    Item();

    int getInstanteEntreItem() const { return instante_entre_item; }
    int getDuracao() const { return duracao; }
    int getMaxItens() const { return max_itens; }
    bool CaixaPandora();
    bool Arca(Jogador &jogador);
    bool Jaula();
    bool Mina();
    bool Surpresa();
    bool ItemAparecer(Grelha &grelha);

    // Método setter, para permitir modificações externas
    void setItem(int i, int d, int m) { instante_entre_item = i, duracao = d, max_itens = m; }
};

#endif //TP_ITEM_H
