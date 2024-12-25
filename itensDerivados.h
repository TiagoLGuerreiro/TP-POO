//
// Created by adm on 23/12/2024.
//

#ifndef TP_ITENSDERIVADOS_H
#define TP_ITENSDERIVADOS_H

#include "item.h"
#include "caravana.h"
#include "jogador.h"

// Caixa de Pandora
class CaixaPandora : public Item{
    public:
        CaixaPandora(int randomPos, int tempoRestante, char tipo);
        void efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) override; // override é usado para verificar que não tem erros na chamada
};

// Arca do Tesouro
class ArcaTesouro : public Item {
public:
    ArcaTesouro(int randomPos, int tempoRestante, char tipo);
    void efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) override;
};

// Jaula
class Jaula : public Item {
public:
    Jaula(int randomPos, int tempoRestante, char tipo);
    void efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) override;
};

// Mina
class Mina : public Item {
public:
    Mina(int randomPos, int tempoRestante, char tipo);
    void efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) override;
};

// Surpresa
class Surpresa : public Item {
public:
    Surpresa(int randomPos, int tempoRestante, char tipo);
    void efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) override;
};

#endif //TP_ITENSDERIVADOS_H
