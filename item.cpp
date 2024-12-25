//
// Created by tiago on 26/11/2024.
//

#include "item.h"
#include "grelha.h"
#include "itensDerivados.h"
#include <ctime>

using namespace std;

Item::Item(int randomPos, int tempoRestante, char tipo) : randomPos(randomPos), tempoRestante(tempoRestante), tipo(tipo){}

Item::~Item(){}

void Item::reduzirTempo() {
    if(tempoRestante > 0)
        --tempoRestante;
}

bool Item::isAtivo() const {
    return tempoRestante > 0;
}

int Item::getPos() const {
    return randomPos;
}

char Item::getTipo() const {
    return tipo;
}


void Item::gerarItem(Grelha &grelha, vector<Item*>& itensAtivos, int maxItens, int tempoRestante) {
    vector<Posicao>&mapa = grelha.getMapa();
    int randomPos;

    static bool isSeeded = false; // Para garantir que a semente seja inicializada apenas uma vez
    if (!isSeeded) {
        srand(time(0));
        isSeeded = true;
    }

    if (itensAtivos.size() >= maxItens || tempoRestante <= 0)
        return; // Limite de itens atingido ou intervalo ainda não foi atingido

    do{
        randomPos = rand() % (mapa.size() + 1);

        if(mapa[randomPos].getTipo() == '.'){
            mapa[randomPos].setTipo('?');

            int tipo = rand() % 5; // Sorteia o tipo do item

            switch (tipo) {
                case 0: itensAtivos.push_back(new CaixaPandora(randomPos, tempoRestante, 'C')); break;
                case 1: itensAtivos.push_back(new ArcaTesouro(randomPos, tempoRestante, 'A')); break;
                case 2: itensAtivos.push_back(new Jaula(randomPos, tempoRestante, 'J')); break;
                case 3: itensAtivos.push_back(new Mina(randomPos, tempoRestante, 'M')); break;
                case 4: itensAtivos.push_back(new Surpresa(randomPos, tempoRestante, 'S')); break;
            }
        }
    }while(mapa[randomPos].getTipo() != '?' || itensAtivos.size() < maxItens);
}

void Item::atualizarItens(vector<Item*>& itensAtivos, int instanteAtual) {

    // for percorre a lista de itens ativos
    // não usamos it++ porque precisamos de ajustar o iterador manualmente.
    for (auto it = itensAtivos.begin(); it != itensAtivos.end();) {
        (*it)->reduzirTempo(); // Reduz o tempo de vida do item

        // Verifica se o item já expirou o tempo
        if (!(*it)->isAtivo()) {
            delete *it;              // Liberta a memória
            it = itensAtivos.erase(it); // Remove o item expirado
        } else
            ++it;
    }
}