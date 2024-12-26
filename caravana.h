//
// Created by tiago on 25/11/2024.
//

#ifndef TP_CARAVANA_H
#define TP_CARAVANA_H

#include <string>
#include <iostream>
#include "grelha.h"
#include "jogador.h"
using namespace std;

class Caravana{
private:
    int id;
    int capacidadeCarga, capacidadeAgua;
    int tripulantes, cargaAtual, aguaAtual;
    int pos;
    bool destruida;
    string tipo;
    bool comportamento; //autogestao ou pelo utilizador
    int numDes;
    bool cidade = false;

public:
    Caravana(int id, int pos, int carga, int agua, int tripulantes, int numDes,const string& tipo, bool cidade);

    virtual ~Caravana() = default;

    void setComportamento() {comportamento = !comportamento;}
    bool verificarComportamento() const { return comportamento; }

    void setDestruida(bool status) { destruida = status; }
    bool isDestruida() const { return destruida; }

    int getTripulantes() const { return tripulantes ;}
    void setTripulantes(int novoTripulantes);

    int getId() const { return id; }
    int getDes() const { return numDes; }

    int getPosicao() const { return pos; }
    void setPosicao(int novaPosicao) {pos = novaPosicao;}

    void mostrarInfo() const;

    bool getCidade(){return cidade;}

    int getCargaAtual(){return cargaAtual;}
    int getCapacidadeCarga(){return capacidadeCarga;}

    void setCarga(int novaCarga){cargaAtual = novaCarga;}

    static bool verificarCaravanaID(const vector<Caravana*>& caravanasAtivas, int id);

    static void criar(vector<Caravana*>& caravanasAtivas, Grelha &grelha);

    virtual void mover(int colunas, const string& direcao, Grelha& grelha, int novaPosicao, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*> &caravanasAtivas);
    virtual void comportamentoAutonomo(Grelha& grelha, Jogador& jogador, vector<Item*>& itensAtivos, vector<Caravana*>& caravanasAtivas);
    Caravana* encontrarCaravanaBarbaraProxima(const vector<Caravana*>& caravanasAtivas, int alcance) const;
    void moverAleatorio(Grelha& grelha, int pos, int id);
    void moverPara(int novaPosicao, Grelha& grelha);

    Caravana* encontrarCaravanaProxima(const vector<Caravana*>& caravanasAtivas, Grelha &grelha) const;
    Item* encontrarItemProximo(const vector<Item*>& itens, int alcance, Grelha &grelha) const;


    void reabastecerAgua();
    void venderCarga();
};

#endif //TP_CARAVANA_H
