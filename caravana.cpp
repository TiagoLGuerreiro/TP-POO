//
// Created by tiago on 26/11/2024.
//

#include "caravana.h"
#include "caravanasTipos.h"
#include "itensDerivados.h"
#include "item.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

Caravana::Caravana(int id, int pos, int carga, int agua, int tripulantes) : id(id), capacidadeAgua(agua),
capacidadeCarga(carga),tripulantes(tripulantes), cargaAtual(0),aguaAtual(agua), pos(pos), destruida(false) {}

void Caravana::reabastecerAgua() {
    aguaAtual = capacidadeAgua;
}

void Caravana::venderCarga() {
    cargaAtual = 0;
}

bool Caravana::verificarCaravanaID(const vector<Caravana*>& caravanasAtivas, int id) {
    for (const auto& caravana : caravanasAtivas) {
        if (caravana->getId() == id)
            return true;
    }
    return false;
}

void Caravana::criar(vector<Caravana*>& caravanasAtivas, Grelha &grelha){
    vector<Posicao>&mapa = grelha.getMapa();
    int pos = 0;
    srand(time(0));
    do{
        if(mapa[pos].getTipo() - '0' < 10 && mapa[pos].getTipo() - '0' > 0 ){
            int tipo = rand() % 3; // Sorteia o tipo de caravana
            switch (tipo) {
                case 0: caravanasAtivas.push_back(new Comercio(mapa[pos].getTipo() - '0', pos)); break;
                case 1: caravanasAtivas.push_back(new Militar(mapa[pos].getTipo() - '0', pos)); break;
                case 2: caravanasAtivas.push_back(new Secreta(mapa[pos].getTipo() - '0', pos)); break;
            }
        }
        pos++;
    }while(mapa.size() != pos);
}

void Caravana::mover(int colunas, const string &direcao, Grelha &grelha,int novaPosicao, int id, vector<Item*>& item, Jogador &jogador) {
    int posicao = novaPosicao;
    int tamanho = grelha.getMapa().size();

    if (direcao == "D")        // Direita
        novaPosicao = (posicao + 1) % tamanho;
    else if (direcao == "E")
        novaPosicao = (posicao - 1 + tamanho) % tamanho; // Esquerda
    else if (direcao == "C")
        novaPosicao = (posicao - colunas + tamanho) % tamanho; // Cima
    else if (direcao == "B")
        novaPosicao = (posicao + colunas) % tamanho; // Baixo
    else if (direcao == "CE")
        novaPosicao = (posicao - colunas - 1 + tamanho) % tamanho; // Cima-esquerda
    else if (direcao == "CD")
        novaPosicao = (posicao - colunas + 1 + tamanho) % tamanho; // Cima-direita
    else if (direcao == "BE")
        novaPosicao = (posicao + colunas - 1 + tamanho) % tamanho; // Baixo-esquerda
    else if (direcao == "BD")
        novaPosicao = (posicao + colunas + 1) % tamanho; // Baixo-direita
    else {
        cerr << "Direcao invalida";
        return;
    }

    if (grelha.getMapa()[novaPosicao].getTipo() == '?') {
        cout << "Achaste um item!" << endl;

        for (auto it = item.begin(); it != item.end(); ++it) { // Iterador
            if ((*it)->getPos() == novaPosicao) {
                char tipo = (*it)->getTipo();

                switch (tipo) {
                    case 'C':
                        (*it) ->efeito(*this, jogador);
                        delete *it; // Liberta a memória do item
                        it = item.erase(it); // Remove o ponteiro do vetor e atualiza o iterador
                        break;
                    case 'A':
                        (*it) ->efeito(*this, jogador);
                        delete *it;
                        it = item.erase(it);
                        break;
                    case 'J':
                        (*it) ->efeito(*this, jogador);
                        delete *it;
                        it = item.erase(it);
                        break;
                    case 'M':
                        (*it) ->efeito(*this, jogador);
                        delete *it;
                        it = item.erase(it);
                        break;
                    case 'S':
                        (*it) ->efeito(*this, jogador);
                        delete *it;
                        it = item.erase(it);
                        break;
                }
                break; // Sai do loop após processar o item
            }
        }
    }else if(grelha.getMapa()[novaPosicao].getTipo() == '+'){
        cout << "Achaste uma montanha, nao te consegues mover nessa direcao" << endl;
        return;
    } else if(grelha.getMapa()[novaPosicao].getTipo() == '!')
        cout << "Achaste uma caravana Barbara" << endl;
    else if(grelha.getMapa()[novaPosicao].getTipo() == 'a' || grelha.getMapa()[novaPosicao].getTipo() == 'b' || grelha.getMapa()[novaPosicao].getTipo() == 'c')
        cout << "Entraste numa cidade" << endl;

// Atualizar a posição no mapa
    grelha.getMapa()[posicao].setTipo('.'); // Marca a posição antiga como deserto
    setPosicao(novaPosicao);
    grelha.getMapa()[novaPosicao].setTipo(id + '0'); // Marca a nova posição com o identificador da caravana
    grelha.mostrarGrelha();
}