//
// Created by tiago on 25/11/2024.
//

#ifndef TP_ITEM_H
#define TP_ITEM_H
#include <string>
#include <vector>
#include "jogador.h"
#include "caravana.h"
using namespace std;

class Grelha;

class Item{
private:
    int tempoRestante;
    int instante_entre_item;
    int randomPos;
    int max_itens;
    char tipo;

public:
    Item(int randomPos, int tempoRestante, char tipo);
    virtual ~Item();

    virtual void efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) = 0;
    void reduzirTempo(); // reduz tempo restante
    bool isAtivo() const; // verifica se está ativo

    int getPos() const;
    char getTipo() const;

    static void gerarItem(Grelha &grelha, vector<Item*>& itensAtivos, int max_itens, int tempoRestante);
    static void atualizarItens(vector<Item*>& itensAtivos, int instanteAtual);

    // Método setter, para permitir modificações externas
    void setItem(int i, int t, int m) { instante_entre_item = i, tempoRestante = t, max_itens = m; }
};

#endif //TP_ITEM_H
