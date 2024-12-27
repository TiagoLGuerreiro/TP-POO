//
// Created by adm on 24/12/2024.
//

#ifndef TP_CARAVANASTIPOS_H
#define TP_CARAVANASTIPOS_H

#include "caravana.h"

using namespace std;

// override é usado para o compilador gerar erros em caso do método estar a ser mal chamado
class Comercio : public Caravana {
public:
    Comercio(int id, int pos);
    void mover(int colunas, string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) override;
    void comportamentoAutonomo(Grelha& grelha, Jogador& jogador, vector<Item*>& itens, vector<Caravana*>& caravanasAtivas) override;
};

class Militar : public Caravana {
public:
    Militar(int id, int pos);
    void mover(int colunas, string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) override;
    void comportamentoAutonomo(Grelha& grelha, Jogador& jogador, vector<Item*>& itens, vector<Caravana*>& caravanasAtivas) override;
};

class Secreta : public Caravana {
public:
    Secreta(int id, int pos);
    void mover(int colunas, string& direcao, Grelha& grelha, int pos, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*>& caravanasAtivas) override;
};

class Barbara : public Caravana {
public:
    Barbara(int id, int pos);
    void comportamentoAutonomo(Grelha& grelha, Jogador& jogador, vector<Item*>& itens, vector<Caravana*>& caravanasAtivas) override;
};


#endif //TP_CARAVANASTIPOS_H