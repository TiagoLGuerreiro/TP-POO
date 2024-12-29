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

Caravana::Caravana(int id, int pos, int cargaAtual, int cargaMax, int aguaMax, int aguaAtual, int tripulantes, int numDes, const string &tipo, bool cidade, int instantesSemTripulantes, bool comportamento) :
        id(id), capacidadeAgua(aguaMax), capacidadeCarga(cargaMax), tripulantes(tripulantes), cargaAtual(cargaAtual),aguaAtual(aguaAtual), pos(pos),
        destruida(false),tipo(tipo),comportamento(comportamento),numDes(numDes),cidade(false), instantesSemTripulantes(instantesSemTripulantes),
        instantesPossiveisSemTripulantes(instantesSemTripulantes){}


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
        if (caravana->getId() == id && caravana->getTipo() != "Barbara")
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
        }else if(mapa[pos].getTipo() == '!'){
            int idBarbaro = rand() % 90 + 10; // Sorteia o id da caravana barbara
            caravanasAtivas.push_back(new Barbara(idBarbaro, pos)); break;
        }
        pos++;
    } while (mapa.size() != pos);
}

void Caravana::caravanaAparecer(vector<Caravana *> &caravanasAtivas, Grelha &grelha, char tipo, int l, int c, int id) {
    vector<Posicao> &mapa = grelha.getMapa();
    srand(time(0));
    int pos = 0, check = 0, idBarbaro;
    if (tipo != '!') {
        switch (tipo) {
            case 'C':
                caravanasAtivas.push_back(new Comercio(id, l));
                break;
            case 'M':
                caravanasAtivas.push_back(new Militar(id, l));
                break;
            case 'S':
                caravanasAtivas.push_back(new Secreta(id, l));
                break;
        }
        for (const auto &caravana: caravanasAtivas) {
            if (caravana->getId() == id) {
                caravana -> cidade = true;
                break;
            }
        }
    } else if(id == 0){
        do{
            pos = rand() % mapa.size();
            do{
                idBarbaro = rand() % 90 + 10; // Sorteia o id da caravana barbara
                for (const auto &caravana: caravanasAtivas) {
                    if (caravana->getId() != idBarbaro && caravana->getTipo() == "Barbara") {
                        caravanasAtivas.push_back(new Barbara(idBarbaro, pos));
                        check = 1;
                        break;
                    }
                }
            }while(check != 1);
        }while(mapa[pos].getTipo() != '.');
        for (const auto &caravana: caravanasAtivas) {
            if (caravana->getId() == idBarbaro) {
                caravana -> cidade = true;
                break;
            }
        }
    }else if(id == 200){
        pos = l * grelha.getColunas() + c;
        if(grelha.getMapa()[pos].getTipo() == '.'){
            do{
                idBarbaro = rand() % 90 + 10; // Sorteia o id da caravana barbara
                for (const auto &caravana: caravanasAtivas) {
                    if (caravana->getId() != idBarbaro && caravana->getTipo() == "Barbara") {
                        caravanasAtivas.push_back(new Barbara(idBarbaro, pos));
                        check = 1;
                        break;
                    }
                }
            }while(check != 1);
            for (const auto &caravana: caravanasAtivas) {
                if (caravana->getId() == idBarbaro) {
                    caravana -> cidade = true;
                    break;
                }
            }
        } else
            cout << "Posicao invalida" << endl;
    }
}

void Caravana::mover(int colunas, string &direcao, Grelha &grelha, int novaPosicao, int id, vector<Item *> &item,
                     Jogador &jogador, vector<Caravana *> &caravanasAtivas) {
    if(getTripulantes() == 0 && getTipo() == "Militar"){
        direcao = getUltimoMovimento();
        cout << "Tentaste mover a caravana mas a mesma encontra-se sem tripulacao" << endl;
    }

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

    if(grelha.getMapa()[posicao].getTipo() == 'a' || grelha.getMapa()[posicao].getTipo() == 'b' ||
              grelha.getMapa()[posicao].getTipo() == 'c'){

        char tipoAtual = grelha.getMapa()[posicao].getTipo(); // Obtém o tipo atual
        grelha.getMapa()[posicao].setTipo(tipoAtual); // Marca a posição antiga como deserto
        cout << "Saiste da cidade!" << endl;
        grelha.getMapa()[novaPosicao].setTipo(id + '0');
        cidade = false;
    }else
        grelha.getMapa()[posicao].setTipo('.'); // Marca a posição antiga como deserto

    // Atualizar a posição no mapa
    setPosicao(novaPosicao);
    setUltimoMovimento(direcao);
    if(!cidade){
        if (!destruida)
             grelha.getMapa()[novaPosicao].setTipo(id + '0'); // Marca a nova posição com o identificador da caravana
        else
            grelha.getMapa()[novaPosicao].setTipo('.');
    }
    grelha.mostrarGrelha();
}

void Caravana::moverAleatorio(Grelha &grelha, int novaPosicao, int id, vector<Item *> &item, Jogador &jogador, vector<Caravana *> &caravanasAtivas) {
    vector<Posicao> &mapa = grelha.getMapa();
    srand(time(0));
    int posicao = novaPosicao;
    int tamanho = grelha.getMapa().size();
    int colunas = grelha.getColunas();
    int direcao;
    string direcao2;
    do {
        direcao = rand() % 8; // Sorteia para onde se vai movimentar
        switch (direcao) {
            case 0:
                novaPosicao = (posicao + 1) % tamanho;
                setUltimoMovimento("D");
                direcao2 = "D";
                break; // Direita
            case 1:
                novaPosicao = (posicao - 1 + tamanho) % tamanho;
                setUltimoMovimento("E");
                direcao2 = "E";
                break; // Esquerda
            case 2:
                novaPosicao = (posicao - colunas + tamanho) % tamanho;
                setUltimoMovimento("C");
                direcao2 = "C";
                break; // Cima
            case 3:
                novaPosicao = (posicao + colunas) % tamanho;
                setUltimoMovimento("B");
                direcao2 = "B";
                break; // Baixo
            case 4:
                novaPosicao = (posicao - colunas - 1 + tamanho) % tamanho;
                setUltimoMovimento("CE");
                direcao2 = "CE";
                break; // Cima-esquerda
            case 5:
                novaPosicao = (posicao - colunas + 1 + tamanho) % tamanho;
                setUltimoMovimento("CD");
                direcao2 = "CD";
                break; // Cima-direita
            case 6:
                novaPosicao = (posicao + colunas - 1 + tamanho) % tamanho;
                setUltimoMovimento("BE");
                direcao2 = "BE";
                break; // Baixo-esquerda
            case 7:
                novaPosicao = (posicao + colunas + 1) % tamanho;
                setUltimoMovimento("BD");
                direcao2 = "BD";
                break; // Baixo-direita
        }
    } while (mapa[novaPosicao].getTipo() == '+');

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
    } else if (grelha.getMapa()[novaPosicao].getTipo() == '+' && getTipo() != "Barbara") {
        cout << "Achaste uma montanha, nao te consegues mover nessa direcao" << endl;
        return;
    } else if (grelha.getMapa()[novaPosicao].getTipo() == '+' && getTipo() == "Barbara") {
        return;
    } else if (grelha.getMapa()[novaPosicao].getTipo() == '!' && getTipo() != "Barbara")
        cout << "Achaste uma caravana Barbara" << endl;
    else if (grelha.getMapa()[novaPosicao].getTipo() == 'a' || grelha.getMapa()[novaPosicao].getTipo() == 'b' ||
             grelha.getMapa()[novaPosicao].getTipo() == 'c') {
        if(getTipo() != "Barbara")
            cout << "Entraste numa cidade" << endl;
        cidade = true;
        reabastecerAgua();
    }

    if(grelha.getMapa()[posicao].getTipo() == 'a' || grelha.getMapa()[posicao].getTipo() == 'b' ||
       grelha.getMapa()[posicao].getTipo() == 'c'){

        char tipoAtual = grelha.getMapa()[posicao].getTipo(); // Obtém o tipo atual
        grelha.getMapa()[posicao].setTipo(tipoAtual); // Marca a posição antiga como deserto
        if(getTipo() != "Barbara"){
            cout << "Saiste da cidade!" << endl;
            grelha.getMapa()[novaPosicao].setTipo(id + '0');
        } else
            grelha.getMapa()[novaPosicao].setTipo('!');
        cidade = false;
    }else
        grelha.getMapa()[posicao].setTipo('.'); // Marca a posição antiga como deserto

    setPosicao(novaPosicao);
    setUltimoMovimento(direcao2);

    if(!cidade){
        if (!destruida && getTipo() != "Barbara")
            grelha.getMapa()[novaPosicao].setTipo(id + '0'); // Marca a nova posição com o identificador da caravana
        else if (!destruida && getTipo() != "Barbara")
            grelha.getMapa()[novaPosicao].setTipo('!');
        else
            grelha.getMapa()[novaPosicao].setTipo('.');
    }
}

void Caravana::comportamentoAutonomo(Grelha &grelha, Jogador &jogador, vector<Item *> &itens,
                                     vector<Caravana *> &caravanasAtivas) {
    // Comportamento padrão ou vazio
}

Caravana *Caravana::encontrarCaravanaProxima(const vector<Caravana *> &caravanasAtivas, Grelha &grelha) const {
    Caravana *caravanaMaisProxima = nullptr;
    int menorDistancia = INT_MAX; // Inicializar com a maior distância possível

    for (Caravana *outraCaravana: caravanasAtivas) {
        if (outraCaravana == this || outraCaravana->verificarComportamento() || outraCaravana->getTipo() == "Barbara") {
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

Caravana *Caravana::encontrarCaravanaBarbaraProxima(const vector<Caravana *> &caravanasAtivas, Grelha &grelha, int alcance) const {
    Caravana *caravanaBarbaraMaisProxima = nullptr;
    int menorDistancia = INT_MAX; // Inicializar com a maior distancia possível

    for (Caravana *outraCaravana : caravanasAtivas) {
        if(this->getTipo() == "Barbara"){
            if (outraCaravana == this || outraCaravana->getTipo() == "Barbara")
                continue; // Ignora se a si mesma ou caravanas que são bárbaras
        } else {
            if (outraCaravana == this || outraCaravana->getTipo() != "Barbara")
                continue; // Ignora se a si mesma ou caravanas que não são bárbaras
        }


        int linhaAtual = this->getPosicao() / grelha.getColunas();
        int colunaAtual = this->getPosicao() % grelha.getColunas();

        int linhaOutra = outraCaravana->getPosicao() / grelha.getColunas();
        int colunaOutra = outraCaravana->getPosicao() % grelha.getColunas();

        int distanciaLinha = abs(linhaAtual - linhaOutra);
        int distanciaColuna = abs(colunaAtual - colunaOutra);

        if (distanciaLinha <= alcance && distanciaColuna <= alcance) {
            int distanciaTotal = distanciaLinha + distanciaColuna;

            if (distanciaTotal < menorDistancia) { // Verifica se é a mais próxima
                menorDistancia = distanciaTotal;
                caravanaBarbaraMaisProxima = outraCaravana;
            }
        }
    }

    return caravanaBarbaraMaisProxima;
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

void Caravana::moverPara(int novaPosicao, Grelha &grelha, vector<Item *> &item, Jogador &jogador, vector<Caravana *> &caravanasAtivas) {
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
    string direcao;
        // Movimentos horizontais e verticais
        if (linhaAtual < linhaDestino) { novaLinha++; direcao = "C";}
        else if (linhaAtual > linhaDestino) { novaLinha--; direcao = "B";}

        if (colunaAtual < colunaDestino) { novaColuna++; direcao = "D";}
        else if (colunaAtual > colunaDestino) { novaColuna--; direcao = "E";}

        // Verifica se o próximo passo é válido
        novaPosicao = novaLinha * colunas + novaColuna;
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
        } else if (grelha.getMapa()[novaPosicao].getTipo() == '+' && getTipo() != "Barbara") {
            cout << "Achaste uma montanha, nao te consegues mover nessa direcao" << endl;
            return;
        } else if (grelha.getMapa()[novaPosicao].getTipo() == '+' && getTipo() == "Barbara") {
            return;
        } else if (grelha.getMapa()[novaPosicao].getTipo() == '!' && getTipo() != "Barbara")
            cout << "Achaste uma caravana Barbara" << endl;
        else if (grelha.getMapa()[novaPosicao].getTipo() == 'a' || grelha.getMapa()[novaPosicao].getTipo() == 'b' ||
                 grelha.getMapa()[novaPosicao].getTipo() == 'c') {
            if(getTipo() != "Barbara")
                cout << "Entraste numa cidade" << endl;
            cidade = true;
            reabastecerAgua();
        }

        if(grelha.getMapa()[posicaoAtual].getTipo() == 'a' || grelha.getMapa()[posicaoAtual].getTipo() == 'b' ||
           grelha.getMapa()[posicaoAtual].getTipo() == 'c'){

            char tipoAtual = grelha.getMapa()[posicaoAtual].getTipo(); // Obtém o tipo atual
            grelha.getMapa()[posicaoAtual].setTipo(tipoAtual); // Marca a posição antiga como deserto
            if(getTipo() != "Barbara"){
                cout << "Saiste da cidade!" << endl;
                grelha.getMapa()[novaPosicao].setTipo(id + '0');
            } else
                grelha.getMapa()[novaPosicao].setTipo('!');
            cidade = false;
        }else
            grelha.getMapa()[posicaoAtual].setTipo('.'); // Marca a posição antiga como deserto

        setPosicao(novaPosicao);
        setUltimoMovimento(direcao);

        if(!cidade){
            if (!destruida && getTipo() != "Barbara")
                grelha.getMapa()[novaPosicao].setTipo(id + '0'); // Marca a nova posição com o identificador da caravana
            else if (!destruida && getTipo() == "Barbara")
                grelha.getMapa()[novaPosicao].setTipo('!');
            else
                grelha.getMapa()[novaPosicao].setTipo('.');
        }
        cout << endl;
    }
}