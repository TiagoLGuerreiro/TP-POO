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
        void efeito(Caravana& caravana, Jogador &jogador) override; // override é usado para verificar que não tem erros na chamada
};

// Arca do Tesouro
class ArcaTesouro : public Item {
public:
    ArcaTesouro(int randomPos, int tempoRestante, char tipo);
    void efeito(Caravana& caravana, Jogador &jogador) override;
};

// Jaula
class Jaula : public Item {
public:
    Jaula(int randomPos, int tempoRestante, char tipo);
    void efeito(Caravana& caravana, Jogador &jogador) override;
};

// Mina
class Mina : public Item {
public:
    Mina(int randomPos, int tempoRestante, char tipo);
    void efeito(Caravana& caravana,Jogador &jogador) override;
};

// Surpresa
class Surpresa : public Item {
public:
    Surpresa(int randomPos, int tempoRestante, char tipo);
    void efeito(Caravana& caravana, Jogador &jogador) override;
};

#endif //TP_ITENSDERIVADOS_H
