#include "grelha.h"
#include "jogador.h"
#include "item.h"
#include "caravana.h"
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
        cout << "O Jogador Tem " << jogador.getMoedas() << " Moedas" << endl;
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
    int j, k, i = 0, vezes, c;

    do {

        inicioWhile:;

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
        repetir:;
        if (opcaoComando == "exec") {
            if (resto == "mapa.txt")
                cout << "O Jogador Tem " << jogador.getMoedas() << " Moedas" << endl;
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
                ++c;
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
                for (Caravana* caravana : caravanasAtivas) {
                    if (caravana->getTripulantes() <= 0) {
                        if(!caravana->verificarComportamento())
                            caravana->setComportamento();
                        caravana->setinstantesSemTripulantes();
                        if(caravana->getinstantesSemTripulantes() <= 0)
                            destruirCaravana(caravanasAtivas, caravana->getId(), caravana->getPosicao(), grelha);
                    }
                    if (caravana->verificarComportamento()) {
                        caravana->comportamentoAutonomo(grelha, jogador, itensAtivos, caravanasAtivas);
                    }
                    caravana->getTipo();
                    if(caravana->getTipo() == "Secreta")
                        vezes = 2;
                    else if(caravana->getTipo() == "Comercio"){
                        if(caravana->getTripulantes() < 10)
                            vezes = 1;
                        else if(caravana->getTripulantes() == 0)
                            vezes = 0;
                        else
                            vezes = 2;
                    } else if(caravana->getTipo() == "Militar"){
                        if(caravana->getTripulantes() < 20)
                            vezes = 1;
                        else
                            vezes = 3;
                    }
                    for (int t = 0; t < vezes; t++)
                        caravana->reduzirAgua();
                    if(caravana->verificarComportamento()){
                        for (int l = 0; l < caravana->getDes(); l++)
                            caravana->comportamentoAutonomo(grelha, jogador, itensAtivos, caravanasAtivas);
                    }
                }
                // Atualizar o estado do jogo (água, mercadoria, etc.)
                //atualizarEstado();
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
                    if (i < caravana->getDes()) {
                        int colunas = grelha.getColunas();
                        int posicaoCaravana = caravana->getPosicao();
                        int id = caravana->getId();
                        caravana->mover(colunas, resto2, grelha, posicaoCaravana, id, itensAtivos, jogador,
                                        caravanasAtivas);  // Move a caravana guardada no ponteiro

                        cout << "Instante atual: " << jogador.getInstante() + i << endl;
                        string restoantigo = resto;
                        cout << "\nComandos Disponiveis: prox <n>, move <N> <X>, terminar." << endl;
                        getline(cin, escolha);

                        istringstream iss(escolha);
                        iss >> opcaoComando;
                        iss >> resto;
                        iss >> resto2;
                        if (resto != restoantigo) {
                            cout << "So pode movimentar 1 caravana por turno" << endl;
                            goto inicioWhile;
                        }
                        if (opcaoComando == "move") i++;
                        else i = 0;

                        goto repetir;
                    } else {
                        cout << "A caravana selecionada so pode andar " << caravana->getDes() << " vezes por instante"
                             << endl;
                        i = 0;
                    }
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
                cout << "Caravana deixou de estar em autogestao" << endl;
            }
        } else if (opcaoComando == "terminar") {
            cout << "Escolheu Sair, Ate Uma Proxima." << endl;
            cout << "Pontuacao final - " << endl; // falta adicionar aqui a pontuacao
            UserInterface();

        } else if (opcaoComando == "areia") {
            if (empty(resto) || empty(resto2) || empty(resto3)) {
                cerr << "Comando Areia requer 3 valores apos o mesmo" << endl;
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
                        // Calcular o índice para aceder a célula do mapa
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
                                if (rand() % 4 == 0) { //Os tais 25% chance de destruir
                                    destruirCaravana(caravanasAtivas, idCaravana, indiceTempestade, grelha);
                                    cerr << "A Caravana " << idCaravana << " Foi Destruida! Hasta La Vista." << endl;
                                }
                            }
                        }
                    }
                }
            }
        } else if (opcaoComando == "auto") {
            if (empty(resto))
                cerr << "Adicione o id da caravana que pretende colocar em auto gestao" << endl;
            else {
                Caravana *caravana = encontrarCaravanaPorID(caravanasAtivas, stoi(resto));
                if (caravana && !caravana->verificarComportamento()) {
                    caravana->setComportamento();
                    cout << "A caravana " << caravana->getId() << " esta agora em modo de autogestao." << endl;
                } else
                    cout << "Caravana ja se encontra em autogestao" << endl;
            }

        } else if (opcaoComando == "precos") {
            cout << "Comprar Tripulantes 1 Moedas Cada" << endl;
            cout << "Vender Mercadoria " << grelha.getVendaM() << " Moedas Cada Tonelada" << endl;
            cout << "Comprar Mercadoria " << grelha.getCompraM() << " Moedas Cada Tonelada" << endl;
            cout << "Comprar Caravana " << grelha.getPrecoC() << " Moedas Cada" << endl;
            cout << jogador.getMoedas() << endl;

        } else if (opcaoComando == "vende") {
            if (empty(resto)) {
                cerr << "Comando vende Necessita Um Parametro." << endl;
                goto finalWhile;
            }
            int idCaravana = stoi(resto);
            Caravana *caravana = nullptr;

            for (auto &c: caravanasAtivas) {
                if (c->getId() == idCaravana) {
                    caravana = c;
                    break;
                }
            }
            if (caravana) {
                if (caravana->getCidade()) {
                    if(caravana->getCargaAtual() > 0) {
                        jogador.setMoedas(jogador.getMoedas() + (caravana->getCargaAtual() * grelha.getVendaM()));
                        cout << "O Jogador Ficou Com " << jogador.getMoedas() << " Moedas." << endl;
                        caravana->setCarga(0);
                        cout << "A Caravana Ficou Com " << caravana->getCargaAtual() << " Toneladas De Mercadoria."
                             << endl;
                    }else
                        cout << "A Caravana Encontra-se Sem Mercadoria.";
                } else
                    cout << "A Caravana Nao Se Encontra Numa Cidade." << endl;
            } else
                cout << "Caravana nao encontrada." << endl;

        } else if (opcaoComando == "compra") {
            if (empty(resto) || empty(resto2)) {
                cerr << "Comando Compra Necessita Dois Parametros." << endl;
                goto finalWhile;
            }


            int idCaravana = stoi(resto);
            Caravana *caravana = nullptr;
            int quantidade = stoi(resto2);

            for (auto &c: caravanasAtivas) {
                if (c->getId() == idCaravana) {
                    caravana = c;
                    break;
                }
            }
            if (caravana) {
                if (caravana->getCidade()) {
                    if (quantidade <= (caravana->getCapacidadeCarga() - caravana->getCargaAtual())) {
                        if (jogador.getMoedas() >= (quantidade * grelha.getCompraM())) {
                            caravana->setCarga(caravana->getCargaAtual() + quantidade);
                            jogador.setMoedas(jogador.getMoedas() - quantidade * grelha.getCompraM());
                            cout << "Sobrou " << jogador.getMoedas() << " Moedas Depois Da Compra." << endl;
                            cout << "A Carga Atual Da Caravana " << idCaravana << " Ficou A "
                                 << caravana->getCargaAtual() << " Toneladas." << endl;
                        } else
                            cout << "Nao Possui Moedas Suficientes." << endl;
                    } else
                        cout << "A Caravana Nao Tem A Capacidade Necessaria Para Tal." << endl;
                } else
                    cout << "A Caravana Nao Se Encontra Numa Cidade" << endl;
            } else
                cout << "Caravana nao encontrada." << endl;


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