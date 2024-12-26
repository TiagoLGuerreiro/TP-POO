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
    bool comportamento;

public:
    Caravana(int id, int pos, int carga, int agua, int tripulantes, const string& tipo);

    virtual ~Caravana() = default;

    void setComportamento() {comportamento = !comportamento; cout << comportamento;}
    void setDestruida(bool status) { destruida = status; }
    bool isDestruida() const { return destruida; }
    int getTripulantes() const { return tripulantes ;}
    void setTripulantes(int novoTripulantes);
    int getId() const { return id; }
    int getPosicao() const { return pos; }
    void setPosicao(int novaPosicao) {pos = novaPosicao;}
    void mostrarInfo() const;
    static bool verificarCaravanaID(const vector<Caravana*>& caravanasAtivas, int id);

    static void criar(vector<Caravana*>& caravanasAtivas, Grelha &grelha);

    virtual void mover(int colunas, const string& direcao, Grelha& grelha, int novaPosicao, int id, vector<Item*>& item, Jogador &jogador, vector<Caravana*> &caravanasAtivas);
    //virtual void movimentarAutonomamente() = 0;
    //virtual void movimentarSemTripulantes() = 0;
    //virtual void atualizar(int instante) = 0;

    void reabastecerAgua();
    void venderCarga();
};

#endif //TP_CARAVANA_H
