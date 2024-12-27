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

Caravana::Caravana(int id, int pos, int cargaAtual, int cargaMax, int aguaMax, int aguaAtual, int tripulantes, int numDes, const string &tipo, bool cidade, int instantesSemTripulantes) :
id(id), capacidadeAgua(aguaMax), capacidadeCarga(cargaMax), tripulantes(tripulantes), cargaAtual(cargaAtual),aguaAtual(aguaAtual), pos(pos),
destruida(false),tipo(tipo),comportamento(false),numDes(numDes),cidade(false), instantesSemTripulantes(instantesSemTripulantes){}


void Caravana::reabastecerAgua() {
    aguaAtual = capacidadeAgua;
}

void Caravana::reduzirAgua() {
    aguaAtual -= 1;
}

void Caravana::setTripulantes(int novoTripulantes) {
    if (novoTripulantes >= 0) {
        tripulantes = novoTripulantes;
    } else {
        cout << "O numero de tripulantes nao pode ser negativo." << endl;
    }
}

void Caravana::venderCarga() {
    cargaAtual = 0;
}

void Caravana::mostrarInfo() const {
    cout << "A caravana " << id << " e uma caravana " << tipo << endl;
    cout << "Tem um total de " << tripulantes << " tripulantes com uma carga atual de " << cargaAtual <<
         " toneladas de mercadoria e " << aguaAtual << " litros de agua." << endl;
}

bool Caravana::verificarCaravanaID(const vector<Caravana *> &caravanasAtivas, int id) {
    for (const auto &caravana: caravanasAtivas) {
        if (caravana->getId() == id)
            return true;
    }
    return false;
}

void Caravana::criar(vector<Caravana *> &caravanasAtivas, Grelha &grelha) {
    vector<Posicao> &mapa = grelha.getMapa();
    int pos = 0;
    srand(time(0));
    do {
        if (mapa[pos].getTipo() - '0' < 10 && mapa[pos].getTipo() - '0' > 0) {
            int tipo = rand() % 3; // Sorteia o tipo de caravana
            switch (tipo) {
                case 0:
                    caravanasAtivas.push_back(new Comercio(mapa[pos].getTipo() - '0', pos));
                    break;
                case 1:
                    caravanasAtivas.push_back(new Militar(mapa[pos].getTipo() - '0', pos));
                    break;
                case 2:
                    caravanasAtivas.push_back(new Secreta(mapa[pos].getTipo() - '0', pos));
                    break;
            }
        }
        pos++;
    } while (mapa.size() != pos);
}

void Caravana::mover(int colunas, const string &direcao, Grelha &grelha, int novaPosicao, int id, vector<Item *> &item,
                     Jogador &jogador, vector<Caravana *> &caravanasAtivas) {
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
                        (*it)->efeito(*this, jogador, caravanasAtivas, grelha);
                        delete *it; // Liberta a memória do item
                        it = item.erase(it); // Remove o ponteiro do vetor e atualiza o iterador
                        break;
                    case 'A':
                        (*it)->efeito(*this, jogador, caravanasAtivas, grelha);
                        delete *it;
                        it = item.erase(it);
                        break;
                    case 'J':
                        (*it)->efeito(*this, jogador, caravanasAtivas, grelha);
                        delete *it;
                        it = item.erase(it);
                        break;
                    case 'M':
                        (*it)->efeito(*this, jogador, caravanasAtivas, grelha);

                        delete *it;
                        it = item.erase(it);
                        break;
                    case 'S':
                        (*it)->efeito(*this, jogador, caravanasAtivas, grelha);
                        delete *it;
                        it = item.erase(it);
                        break;
                }
                break; // Sai do loop após processar o item
            }
        }
    } else if (grelha.getMapa()[novaPosicao].getTipo() == '+') {
        cout << "Achaste uma montanha, nao te consegues mover nessa direcao" << endl;
        return;
    } else if (grelha.getMapa()[novaPosicao].getTipo() == '!')
        cout << "Achaste uma caravana Barbara" << endl;
    else if (grelha.getMapa()[novaPosicao].getTipo() == 'a' || grelha.getMapa()[novaPosicao].getTipo() == 'b' ||
             grelha.getMapa()[novaPosicao].getTipo() == 'c') {
        cout << "Entraste numa cidade" << endl;
        cidade = true;
        reabastecerAgua();
    }
// Atualizar a posição no mapa
    grelha.getMapa()[posicao].setTipo('.'); // Marca a posição antiga como deserto
    setPosicao(novaPosicao);
    if (!destruida) {
        grelha.getMapa()[novaPosicao].setTipo(id + '0'); // Marca a nova posição com o identificador da caravana
    } else
        grelha.getMapa()[novaPosicao].setTipo('.');
    grelha.mostrarGrelha();
}

void Caravana::moverAleatorio(Grelha &grelha, int novaPosicao, int id) {
    vector<Posicao> &mapa = grelha.getMapa();
    srand(time(0));
    int posicao = novaPosicao;
    int tamanho = grelha.getMapa().size();
    int colunas = grelha.getColunas();
    int direcao;
    do {
        direcao = rand() % 8; // Sorteia para onde se vai movimentar
        switch (direcao) {
            case 0:
                novaPosicao = (posicao + 1) % tamanho;
                break; // Direita
            case 1:
                novaPosicao = (posicao - 1 + tamanho) % tamanho;
                break; // Esquerda
            case 2:
                novaPosicao = (posicao - colunas + tamanho) % tamanho;
                break; // Cima
            case 3:
                novaPosicao = (posicao + colunas) % tamanho;
                break; // Baixo
            case 4:
                novaPosicao = (posicao - colunas - 1 + tamanho) % tamanho;
                break; // Cima-esquerda
            case 5:
                novaPosicao = (posicao - colunas + 1 + tamanho) % tamanho;
                break; // Cima-direita
            case 6:
                novaPosicao = (posicao + colunas - 1 + tamanho) % tamanho;
                break; // Baixo-esquerda
            case 7:
                novaPosicao = (posicao + colunas + 1) % tamanho;
                break; // Baixo-direita
        }
    } while (mapa[novaPosicao].getTipo() == '+');
    grelha.getMapa()[posicao].setTipo('.'); // Marca a posição antiga como deserto
    setPosicao(novaPosicao);
    grelha.getMapa()[novaPosicao].setTipo(id + '0');
    grelha.mostrarGrelha();
}

void Caravana::comportamentoAutonomo(Grelha &grelha, Jogador &jogador, vector<Item *> &itens,
                                     vector<Caravana *> &caravanasAtivas) {
    // Comportamento padrão ou vazio
}

Caravana *Caravana::encontrarCaravanaProxima(const vector<Caravana *> &caravanasAtivas, Grelha &grelha) const {
    Caravana *caravanaMaisProxima = nullptr;
    int menorDistancia = INT_MAX; // Inicializar com a maior distância possível

    for (Caravana *outraCaravana: caravanasAtivas) {
        if (outraCaravana == this || outraCaravana->verificarComportamento()) {
            continue; // Ignora se a si mesma ou caravanas em autogestão, continue itera o loop
        }

        int distancia =
                abs(outraCaravana->getPosicao() / grelha.getColunas() - this->getPosicao() / grelha.getColunas()) +
                abs(outraCaravana->getPosicao() % grelha.getColunas() - this->getPosicao() % grelha.getColunas());

        if (distancia < menorDistancia) { //verificar qual tem uma menor distancia
            menorDistancia = distancia;
            caravanaMaisProxima = outraCaravana;
        }
    }

    return caravanaMaisProxima;
}

Item *Caravana::encontrarItemProximo(const vector<Item *> &itens, int alcance, Grelha &grelha) const {
    Item *itemMaisProximo = nullptr;
    int menorDistancia = alcance + 1; // Inicializar com um valor maior que o alcance permitido

    for (Item *item: itens) {
        int distancia = abs(item->getPos() / grelha.getColunas() - this->getPosicao() / grelha.getColunas()) +
                        abs(item->getPos() % grelha.getColunas() - this->getPosicao() % grelha.getColunas());

        if (distancia <= alcance && distancia < menorDistancia) {
            menorDistancia = distancia;
            itemMaisProximo = item;
        }
    }
    return itemMaisProximo;
}

void Caravana::moverPara(int novaPosicao, Grelha &grelha) {
    vector<Posicao> &mapa = grelha.getMapa();
    int colunas = grelha.getColunas();

    // Posições iniciais e finais
    int posicaoAtual = getPosicao();
    int linhaAtual = posicaoAtual / colunas;
    int colunaAtual = posicaoAtual % colunas;

    int linhaDestino = novaPosicao / colunas;
    int colunaDestino = novaPosicao % colunas;

    // Caminho passo a passo
    if (abs(linhaAtual - linhaDestino) > 1 || abs(colunaAtual - colunaDestino) > 1) {
        int novaLinha = linhaAtual;
        int novaColuna = colunaAtual;

        // Movimentos horizontais e verticais
        if (linhaAtual < linhaDestino) novaLinha++;
        else if (linhaAtual > linhaDestino) novaLinha--;

        if (colunaAtual < colunaDestino) novaColuna++;
        else if (colunaAtual > colunaDestino) novaColuna--;

        // Verifica se o próximo passo é válido
        novaPosicao = novaLinha * colunas + novaColuna;
        if (mapa[novaPosicao].getTipo() == '+') {
            cout << "Caminho bloqueado por montanhas. Movimento interrompido." << endl;
            return;
        }

        // Atualiza a grelha
        mapa[posicaoAtual].setTipo('.'); // Marca a posição antiga como deserto
        setPosicao(novaPosicao);
        mapa[novaPosicao].setTipo(getId() + '0'); // Atualiza o simbolo da caravana na nova posição

        // Atualiza as variáveis para a próxima iteração
        linhaAtual = novaLinha;
        colunaAtual = novaColuna;
        posicaoAtual = novaPosicao;

        grelha.mostrarGrelha();
    }
}