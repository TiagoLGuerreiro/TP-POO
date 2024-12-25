//
// Created by adm on 23/12/2024.
//


#include "itensDerivados.h"
#include "jogador.h"
#include "utils.h"
#include <iostream>
#include <ctime>

using namespace std;

CaixaPandora::CaixaPandora(int randomPos, int tempoRestante, char tipo) : Item(randomPos, tempoRestante, tipo){}

void CaixaPandora::efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) {
    cout << "Caixa de Pandora encontrada! 20% da tripulacao morreu \n";
    //caravana.reduzirTripulacao(caravana.getTripulacao() * 0.2);
}

ArcaTesouro::ArcaTesouro(int randomPos, int tempoRestante, char tipo) : Item(randomPos, tempoRestante, tipo){}

void ArcaTesouro::efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) {
    cout << "Arca do Tesouro encontrada! 10% mais moedas.\n";
    jogador.setMoedas(jogador.getMoedas() + jogador.getMoedas() * 0.1);
}

Jaula::Jaula(int randomPos, int tempoRestante, char tipo) : Item(randomPos, tempoRestante, tipo) {}

void Jaula::efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) {
    cout << "Jaula encontrada! Prisioneiros foram libertos e dicionados a tripulacao.\n";
    //caravana.adicionarTripulacao(5);
}

Mina::Mina(int randomPos, int tempoRestante, char tipo) : Item(randomPos, tempoRestante, tipo) {}

void Mina::efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) {
    cout << "BOOM! Mina encontrada! Caravana destruida.\n";
    destruirCaravana(caravanasAtivas, caravana.getId(), caravana.getPosicao(), grelha);
}

Surpresa::Surpresa(int randomPos, int tempoRestante, char tipo) : Item(randomPos, tempoRestante, tipo) {}

void Surpresa::efeito(Caravana& caravana, Jogador& jogador, vector<Caravana*>& caravanasAtivas, Grelha &grelha) {
    srand(time(0));
    int quantidadeGalinhas = (rand() + 1) % 11;
    cout << "Surpresa! Achaste o Deus Ares. Ele deu-te " << quantidadeGalinhas << " galinhas" << endl;
    // Implementação criativa
}