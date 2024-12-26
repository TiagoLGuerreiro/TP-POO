#include "grelha.h"
#include "jogador.h"
#include "item.h"
#include <iostream>
#include <cstring>
#include "UI.h"
#include <string>
#include <sstream>
#include <functional>
#include "utils.h"
#include <cctype>
#include <cmath>
#include <cstdlib>

void mostraInformacoes(int moedas) {
    cout << "Jogador tem " << moedas << " moedas." << endl;
}

int fase1(Grelha &grelha, Jogador &jogador, vector<Item *> &itensAtivos, vector<Caravana *> &caravanasAtivas) {
    string opcao;

    cout << "======================================" << endl;
    cout << "Fase 1 Da Simulacao:" << endl;
    cout << "Comandos: config <nomeFicheiro>, sair." << endl;
    getline(cin, opcao);

    istringstream iss(opcao);
    string comando, nomeFicheiro;

    iss >> comando;

    if (comando == "config")
        iss >> nomeFicheiro;
    else if (comando == "sair") {
        cout << "Decidiu Sair, Ate Breve" << endl;
        return 2;
    } else {
        cerr << "Comando Invalido" << endl;
        return 1;
    }

    if (!grelha.lerFicheiro(nomeFicheiro, jogador, itensAtivos)) {
        return 1;
    }

    if (strcmp(opcao.c_str(), "config mapa.txt") == 0) {
        grelha.mostrarGrelha();
        mostraInformacoes(jogador.getMoedas());
        Item::gerarItem(grelha, itensAtivos, 5, 20);
        Caravana::criar(caravanasAtivas, grelha);
    } else {
        cerr << "Config Errada!" << endl;
        return 1;
    }
    return 0;
}

int fase2(Grelha &grelha, Jogador &jogador, vector<Item *> &itensAtivos, vector<Caravana *> &caravanasAtivas) {

    string opcaoComando, nome, resto, resto2, resto3; //nome = nomeFicheiro
    string escolha;
    int nInstantes = 0;
    int j, k;

    do {

        cout << "\nComandos Disponiveis: " << endl;
        cout
                << "exec <nomeFicheiro>, prox <n>, comprac <C> <T>, precos, cidade <C>, caravana <C>, compra <N> <M>, vende <N>, move <N> <X>, auto <N>, stop <N>, barbaro <l> <c>, areia <l> <c> <r>, moedas <N>, tripul <N> <T>, saves <nome>, loads <nome>, lists, dels <nome>, terminar."
                << endl;
        getline(cin, escolha);


        istringstream iss(escolha);

        iss >> opcaoComando;

        iss >> resto;

        iss >> resto2;

        iss >> resto3;
        //grelha.lerFicheiro("mapa.txt", jogador, itensAtivos); // MUDAR ESTE MAPA.TXT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Ganda otário rafa, estive 1 hora a tentar descobrir porque é que o mapa voltava ao
// original e era por causa dessa linha de merda

//Desculpa Tiago <3

        if (opcaoComando == "exec") {
            if (resto == "mapa.txt")
                mostraInformacoes(jogador.getMoedas());
            else {
                cerr << "Ficheiro Invalido." << endl;
                return 1;
            }
        } else if (opcaoComando == "moedas") {
            int moedas = stoi(resto);
            jogador.setMoedas(jogador.getMoedas() + moedas);
            cout << "O Jogador Ficou Com " << jogador.getMoedas() << " Moedas" << endl;
        } else if (opcaoComando == "prox") {
            if (resto.empty())
                nInstantes = 1;
            else if (stoi(resto) > 0)
                nInstantes = stoi(resto);

            if (jogador.getInstante() % 10 == 0 || jogador.getInstante() == 0)
                j = 0;

            if (jogador.getInstante() % 20 == 0 || jogador.getInstante() == 0)
                k = 0;

            int instanteAtual = jogador.getInstante();
            jogador.setInstante(jogador.getInstante() + nInstantes);

            for (int i = 0; i < nInstantes; ++i) {      // pular 1 instante ou resto instantes.
                ++j;
                ++k;
                Item::atualizarItens(itensAtivos, jogador.getInstante());
                cout << "Instante Atual - " << instanteAtual + i << endl;
                grelha.mostrarGrelha();
                if (k == 20) {
                    destruirTodosItens(itensAtivos, grelha);
                    cout << endl;
                    k = 0;
                }
                if (j == 10) {
                    Item::gerarItem(grelha, itensAtivos, 5, 20);
                    cout << endl;
                    j = 0;
                }
            }
        } else if (opcaoComando == "move") {
            if (!Caravana::verificarCaravanaID(caravanasAtivas, stoi(resto)))
                cerr << "ID inserido nao existe" << endl;
            else {
                Caravana *caravana = nullptr; //inicializar um ponteiro do tipo caravana sem apontar para nada de inicio
                for (auto &c: caravanasAtivas) {
                    if (c->getId() == stoi(resto)) {
                        caravana = c;
                        break;
                    }
                }

                if (caravana) {
                    int colunas = grelha.getColunas();
                    int posicaoCaravana = caravana->getPosicao();
                    int id = caravana->getId();
                    caravana->mover(colunas, resto2, grelha, posicaoCaravana, id, itensAtivos, jogador,
                                    caravanasAtivas);  // Move a caravana guardada no ponteiro
                } else {
                    cerr << "Caravana nao encontrada." << endl;
                }
            }

        } else if (opcaoComando == "caravana") {
            if (resto.empty() || !Caravana::verificarCaravanaID(caravanasAtivas, stoi(resto)))
                cerr << "ID da inserido invalido!" << endl;
            else {
                int idCaravana = stoi(resto);

                Caravana *caravana = nullptr;
                for (auto &c: caravanasAtivas) {
                    if (c->getId() == idCaravana) {
                        caravana = c;
                        break;
                    }
                }
                caravana->mostrarInfo();
            }
        } else if (opcaoComando == "stop") {
            if (resto.empty() || !Caravana::verificarCaravanaID(caravanasAtivas, stoi(resto)))
                cerr << "ID da inserido invalido!" << endl;
            else {
                int idCaravana = stoi(resto);

                Caravana *caravana = nullptr;
                for (auto &c: caravanasAtivas) {
                    if (c->getId() == idCaravana) {
                        caravana = c;
                        break;
                    }
                }
                caravana->setComportamento();
            }
        } else if (opcaoComando == "terminar") {
            cout << "Escolheu Sair, Ate Uma Proxima." << endl;
            cout << "Pontuacao final - " << endl; // falta adicionar aqui a pontuacao
            UserInterface();
        } else if (opcaoComando == "areia") {
            if (empty(resto) || empty(resto2) || empty(resto3)) {
                cerr << "Comando Areia Requer 3 Numeros Apos Ele" << endl;
                goto finalWhile;
            }
            int x = stoi(resto);
            int y = stoi(resto2);
            int r = stoi(resto3);
            cout << "Uma Tempestade De Areia Comecou Nas Coordenadas " << x << " " << y << " E Raio " << r << "!"
                 << endl;

            for (int y1 = y - r; y1 <= y + r; ++y1) {
                for (int x1 = x - r; x1 <= x + r; ++x1) {

                    // posição (x1, y1) está dentro dos limites do mapa
                    if (x1 >= 1 && x1 <= grelha.getColunas() && y1 >= 1 && y1 <= grelha.getLinhas()) {
                        // Calcular o índice para acessar a célula do mapa
                        int indiceTempestade = (y1 - 1) * grelha.getColunas() + (x1 - 1);
                        Posicao &p = grelha.getMapa()[indiceTempestade];
                        if (isdigit(p.getTipo())) {
                            int idCaravana = p.getTipo() - '0'; // conversao por ASCII
                            Caravana *caravana = nullptr;
                            for (auto &c: caravanasAtivas) {
                                if (c->getId() == idCaravana) {
                                    caravana = c;
                                    break;
                                }
                            }
                            if (caravana) {
                                caravana->setTripulantes(
                                        floor(caravana->getTripulantes() - (caravana->getTripulantes() * 0.1)));
                                if(rand() % 4 == 0){ //Os tais 25% chance de destruir
                                    destruirCaravana(caravanasAtivas, idCaravana, indiceTempestade, grelha);
                                    cerr << "A Caravana " << idCaravana << " Foi Destruida! Hasta La Vista." << endl;
                                }
                            }
                        }
                    }
                }
            }

        } else {
            cerr << "Comando Invalido." << endl;
        }

        finalWhile:;
    } while (opcaoComando != "terminar");

    return 0;
}


int UserInterface() {
    Grelha grelha;
    Jogador jogador(0);
    vector<Item *> itensAtivos;
    vector<Caravana *> caravanasAtivas;

    int n = fase1(grelha, jogador, itensAtivos, caravanasAtivas);

    if (n == 1) {
        cerr << "Erro Na Fase 1." << endl;
        exit(0);
    } else if (n == 2)
        exit(0);

    int m = fase2(grelha, jogador, itensAtivos, caravanasAtivas);

    if (m == 1) {
        cerr << "Erro Na Fase 2." << endl;
        exit(0);
    }

    return 0;
}