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
#include "buffer.h"
#include <fstream>

#define MAX_DATA_SIZE 1000
char *data = new char[MAX_DATA_SIZE]();
int fase1(Grelha &grelha, Jogador &jogador, vector<Item *> &itensAtivos, vector<Caravana *> &caravanasAtivas,
          char *&bufferData) {
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
    bufferData = grelha.lerFicheiro(nomeFicheiro, jogador, itensAtivos);
    if (bufferData == nullptr) {
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

int fase2(Grelha &grelha, Jogador &jogador, vector<Item *> &itensAtivos, vector<Caravana *> &caravanasAtivas,
          char *bufferData) {
    string opcaoComando, nome, resto, resto2, resto3; //nome = nomeFicheiro
    string escolha;
    int nInstantes = 0;
    int j, k, i = 0, vezes, b;
    FILE *ficheiro;

    do {

        inicioWhile:;

        resto = "";

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

            ficheiro = fopen(resto.c_str(), "r");
            if (!ficheiro) {
                cerr << "Erro Ao Abrir O Ficheiro." << endl;
                goto finalWhile;
            }
            char linha[1024];
                while (fgets(linha, sizeof(linha), ficheiro)) {
                    // Processa a linha lida
                    istringstream linhaStream(linha);

                    // Lê os componentes da linha como se fosse um comando
                    linhaStream >> opcaoComando;
                    linhaStream >> resto;
                    linhaStream >> resto2;
                    linhaStream >> resto3;
                    cout << opcaoComando << endl;
                    cout << resto << endl;
                    cout << resto2 << endl;
                    cout << resto3 << endl;
                    if (opcaoComando == "moedas")
                        goto moedas;
                    if (opcaoComando == "prox")
                        goto prox;
                    if (opcaoComando == "move")
                        goto move;
                    if (opcaoComando == "caravana")
                        goto caravana;
                    if (opcaoComando == "stop")
                        goto stop;
                    if (opcaoComando == "terminar")
                        goto terminar;
                    if (opcaoComando == "areia")
                        goto areia;
                    if (opcaoComando == "auto")
                        goto automatico;
                    if (opcaoComando == "preco")
                        goto precos;
                    if (opcaoComando == "vende")
                        goto vende;
                    if (opcaoComando == "compra")
                        goto compra;
                    if (opcaoComando == "cidade")
                        goto cidade;
                    if (opcaoComando == "saves")
                        goto saves;
                    if (opcaoComando == "lists")
                        goto lists;
                    if (opcaoComando == "dels")
                        goto dels;
                    if (opcaoComando == "loads")
                        goto loadar;
                    if (opcaoComando == "tripul")
                        goto tripul;
                    if (opcaoComando == "comprac")
                        goto comprac;

                    fclose(ficheiro);
                }


        } else if (opcaoComando == "moedas") {
            moedas:
            int moedas = stoi(resto);
            jogador.setMoedas(jogador.getMoedas() + moedas);
            cout << "O Jogador Ficou Com " << jogador.getMoedas() << " Moedas" << endl;
        } else if (opcaoComando == "prox") {
            prox:
            if (resto.empty())
                nInstantes = 1;
            else if (stoi(resto) > 0)
                nInstantes = stoi(resto);

            if (jogador.getInstante() % 10 == 0 || jogador.getInstante() == 0)
                j = 0;

            if (jogador.getInstante() % 20 == 0 || jogador.getInstante() == 0)
                k = 0;

            if (jogador.getInstante() % 40 == 0 || jogador.getInstante() == 0)
                b = 0;

            int instanteAtual = jogador.getInstante();
            jogador.setInstante(jogador.getInstante() + nInstantes);

            for (int i = 0; i < nInstantes; ++i) {      // pular 1 instante ou resto instantes.
                ++j;
                ++k;
                ++b;
                Item::atualizarItens(itensAtivos, jogador.getInstante());
                cout << "Instante Atual - " << instanteAtual + i << endl;
                grelha.mostrarGrelha();
                if (k == 20) {
                    destruirTodosItens(itensAtivos, grelha);
                    k = 0;
                }
                if (j == 10) {
                    Item::gerarItem(grelha, itensAtivos, 5, 20);
                    j = 0;
                }
                if (b == 40) {
                    Caravana::caravanaAparecer(caravanasAtivas, grelha, '!');
                    b = 0;
                }
                for (Caravana *caravana: caravanasAtivas) {
                    if (caravana->getTipo() != "Barbara") {
                        if (caravana->getTripulantes() <= 0) {
                            if (!caravana->verificarComportamento() && caravana->getTipo() == "Comercio")
                                caravana->setComportamento();
                            if (caravana->getTipo() == "Militar")
                                caravana->setUltimoMovimento(caravana->getUltimoMovimento());
                            caravana->setinstantesSemTripulantes();
                            if (caravana->getinstantesSemTripulantes() <= 0)
                                destruirCaravana(caravanasAtivas, caravana->getId(), caravana->getPosicao(), grelha);
                        } else if (caravana->getTripulantes() > 0)
                            caravana->setinstantesComTripulantes();

                        if (caravana->getTipo() == "Secreta")
                            vezes = 2;
                        else if (caravana->getTipo() == "Comercio") {
                            if (caravana->getTripulantes() < 10)
                                vezes = 1;
                            else if (caravana->getTripulantes() == 0)
                                vezes = 0;
                            else
                                vezes = 2;
                        } else if (caravana->getTipo() == "Militar") {
                            if (caravana->getTripulantes() < 20)
                                vezes = 1;
                            else
                                vezes = 3;
                        }
                        for (int t = 0; t < vezes; t++)
                            caravana->reduzirAgua();
                        if (caravana->verificarComportamento()) {
                            for (int l = 0; l < caravana->getDes(); l++)
                                caravana->comportamentoAutonomo(grelha, jogador, itensAtivos, caravanasAtivas);
                        }

                        if (caravana->getAguaAtual() <= 0)
                            caravana->setTripulantes(caravana->getTripulantes() - 1);
                    } else {
                        caravana->setinstantesSemTripulantes();
                        if (caravana->getinstantesSemTripulantes() == 0)
                            destruirCaravana(caravanasAtivas, caravana->getId(), caravana->getPosicao(), grelha);
                        caravana->comportamentoAutonomo(grelha, jogador, itensAtivos, caravanasAtivas);
                    }
                }
                grelha.mostrarGrelha();
                // Atualizar o estado do jogo (água, mercadoria, etc.)
                //atualizarEstado();
            }
        } else if (opcaoComando == "move") {
            move:
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
                        else {
                            i = 0;
                            resto = "";
                        }

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
            caravana:
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
            stop:
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
            terminar:
            cout << "Escolheu Sair, Ate Uma Proxima." << endl;
            cout << "Pontuacao final - " << endl; // falta adicionar aqui a pontuacao
            UserInterface();

        } else if (opcaoComando == "areia") {
            areia:
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
                                //Comercio, se tiver mais de 50% da carga tem 50% de chance de ser destuida, de outra forma
                                //se tiver menos de 50% tem 25% de chance de ser destruida.
                                //caso nao seja destruida perde 25% da carga
                                if (caravana->getTipo() == "Comercio") {
                                    if (caravana->getCargaAtual() > (caravana->getCapacidadeCarga() / 2)) {
                                        if (rand() % 2 == 0) {
                                            destruirCaravana(caravanasAtivas, idCaravana, indiceTempestade, grelha);
                                            cerr << "A Caravana " << idCaravana << " Foi Destruida! Hasta La Vista."
                                                 << endl;
                                        } else {
                                            caravana->setCarga(floor((caravana->getCargaAtual() -
                                                                      (caravana->getCargaAtual() / 4))));
                                        }
                                    } else {
                                        if (rand() % 4 == 0) {
                                            destruirCaravana(caravanasAtivas, idCaravana, indiceTempestade, grelha);
                                            cerr << "A Caravana " << idCaravana << " Foi Destruida! Hasta La Vista."
                                                 << endl;
                                        } else {
                                            caravana->setCarga(floor((caravana->getCargaAtual() -
                                                                      (caravana->getCargaAtual() / 4))));

                                        }
                                    }
                                    //MILITAR perde 10% da Tripulacao e 33% de chance de ser destruida
                                } else if (caravana->getTipo() == "Militar") {
                                    caravana->setTripulantes(
                                            floor(caravana->getTripulantes() -
                                                  (caravana->getTripulantes() * 0.1)));

                                    if (rand() % 3 == 0) {
                                        destruirCaravana(caravanasAtivas, idCaravana, indiceTempestade, grelha);
                                        cerr << "A Caravana " << idCaravana << " Foi Destruida! Hasta La Vista."
                                             << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (opcaoComando == "auto") {
            automatico:
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
            precos:
            cout << "Comprar Tripulantes 1 Moedas Cada" << endl;
            cout << "Vender Mercadoria " << grelha.getVendaM() << " Moedas Cada Tonelada" << endl;
            cout << "Comprar Mercadoria " << grelha.getCompraM() << " Moedas Cada Tonelada" << endl;
            cout << "Comprar Caravana " << grelha.getPrecoC() << " Moedas Cada" << endl;
            cout << jogador.getMoedas() << endl;

        } else if (opcaoComando == "vende") {
            vende:
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
                    if (caravana->getCargaAtual() > 0) {
                        jogador.setMoedas(jogador.getMoedas() + (caravana->getCargaAtual() * grelha.getVendaM()));
                        cout << "O Jogador Ficou Com " << jogador.getMoedas() << " Moedas." << endl;
                        caravana->setCarga(0);
                        cout << "A Caravana Ficou Com " << caravana->getCargaAtual() << " Toneladas De Mercadoria."
                             << endl;
                    } else
                        cout << "A Caravana Encontra-se Sem Mercadoria.";
                } else
                    cout << "A Caravana Nao Se Encontra Numa Cidade." << endl;
            } else
                cout << "Caravana nao encontrada." << endl;

        } else if (opcaoComando == "compra") {
            compra:
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


        } else if (opcaoComando == "cidade") {
            cidade:
            if (empty(resto)) {
                cerr << "Comando Necessita 1 Parametro." << endl;
                goto finalWhile;
            }

            char cidade = resto[0];

            const vector<Posicao> &mapa = grelha.getMapa(); // Obter referência ao mapa
            bool encontrado = false;
            int indiceCidade = 0;

            for (size_t i = 0; i < mapa.size(); ++i) {
                if (mapa[i].getTipo() == cidade) {
                    encontrado = true;
                    indiceCidade = i;
                    break;
                }
            }

            int contaCaravanasNaCidade = 0;
            Caravana *caravana = nullptr;
            for (auto &c: caravanasAtivas) {
                if (c->getPosicao() == indiceCidade) {
                    caravana = c;
                    if (caravana->getPosicao() == indiceCidade && caravana->getCidade()) {
                        cout << "A Caravana " << caravana->getId() << " encontra-se Na Cidade " << resto[0] << "."
                             << endl;
                        contaCaravanasNaCidade++;
                    }
                }
            }
            if (contaCaravanasNaCidade == 0)
                cout << "Nao Se Encontram Caravanas Na Cidade." << endl;


        } else if (opcaoComando == "saves") {
            saves:
            if (empty(resto))
                cerr << "Comando Saves necessita de 1 parametro." << endl;
            else
                save(resto, bufferData);


        } else if (opcaoComando == "lists") {
            lists:
            lists();


        } else if (opcaoComando == "loads") {
            loadar:
            if (empty(resto))
                cerr << "Comando Loads necessita de 1 parametro." << endl;
            else
                loads(resto);


        } else if (opcaoComando == "dels") {
            dels:
            if (empty(resto))
                cerr << "Comando Dels necessita de 1 parametro." << endl;
            else
                limparBuffer(resto);


        } else if (opcaoComando == "tripul") {
            tripul:
            if (empty(resto) || empty(resto2)) {
                cerr << "O Comando Necessita De 2 Parametros" << endl;
                goto finalWhile;
            }
            int ntripulantes = stoi(resto2);

            if (ntripulantes < 0) {
                cout << "Nao Pode Comprar Tripulantes Negativos." << endl;
                goto finalWhile;
            }
            if (ntripulantes == 0) {
                cout << "Nao Pode Comprar Zero Tripulantes." << endl;
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
            //comercio 20m tripulantes, militar 40 tripulantes, secreta 15

            if (caravana) {
                if(caravana->getCidade()) {
                    if (jogador.getMoedas() >= ntripulantes) {
                        if (caravana->getTipo() == "Comercio") {
                            if (caravana->getTripulantes() + ntripulantes <= 20) {
                                caravana->setTripulantes(caravana->getTripulantes() + ntripulantes);
                                jogador.setMoedas(jogador.getMoedas() - ntripulantes);
                                cout << "A Caravana Passou A Ter " << caravana->getTripulantes() << " Tripulantes."
                                     << endl;
                                cout << "O Jogador Ficou Com " << jogador.getMoedas() << " Moedas." << endl;

                            } else
                                cout << "A Caravana Nao Tem Capacidade Para "
                                     << caravana->getTripulantes() + ntripulantes
                                     << ", Mas Sim 20 Tripulantes." << endl;


                        } else if (caravana->getTipo() == "Militar") {
                            if (caravana->getTripulantes() + ntripulantes <= 40) {
                                caravana->setTripulantes(caravana->getTripulantes() + ntripulantes);
                                jogador.setMoedas(jogador.getMoedas() - ntripulantes);
                                cout << "A Caravana Passou A Ter " << caravana->getTripulantes() << " Tripulantes."
                                     << endl;
                                cout << "O Jogador Ficou Com " << jogador.getMoedas() << " Moedas." << endl;

                            } else
                                cout << "A Caravana Nao Tem Capacidade Para "
                                     << caravana->getTripulantes() + ntripulantes
                                     << ", Mas Sim 40 Tripulantes." << endl;


                        } else if (caravana->getTipo() == "Secreta") {
                            if (caravana->getTripulantes() + ntripulantes <= 15) {
                                caravana->setTripulantes(caravana->getTripulantes() + ntripulantes);
                                jogador.setMoedas(jogador.getMoedas() - ntripulantes);
                                cout << "A Caravana Passou A Ter " << caravana->getTripulantes() << " Tripulantes."
                                     << endl;
                                cout << "O Jogador Ficou Com " << jogador.getMoedas() << " Moedas." << endl;

                            } else
                                cout << "A Caravana Nao Tem Capacidade Para "
                                     << caravana->getTripulantes() + ntripulantes
                                     << ", Mas Sim 15 Tripulantes." << endl;
                        }
                    } else
                        cout << "O Jogador Nao Tem Moedas Necessarias Para A Compra." << endl;
                }else
                    cout << "A Caravana Nao Esta Numa Cidade Para Conseguir Comprar Tripulantes" << endl;
            }


        } else if (opcaoComando == "comprac") {
            comprac:
            if (empty(resto) || empty(resto2)) {
                cerr << "O Comando Necessita De 2 Parametros." << endl;
                goto finalWhile;
            }

            const vector<Posicao> &mapa = grelha.getMapa(); // Obter referência ao mapa
            bool encontrado = false;
            int indiceCidade = 0;
            char cidade = resto[0];
            char tipo = resto2[0];

            for (size_t i = 0; i < mapa.size(); ++i) {
                if (mapa[i].getTipo() == cidade) {
                    encontrado = true;
                    indiceCidade = i;
                    break;
                }
            }

            if (!encontrado) {
                cout << "Cidade " << cidade << " não encontrada no mapa." << endl;
                goto finalWhile;
            }

            if (tipo == 'C' || tipo == 'M' || tipo == 'S') {

                if (jogador.getMoedas() >= grelha.getPrecoC()) {

                    //Verifica Qual O Proximo ID A Utilizar
                    int maiorId = 0;
                    for (const auto &c: caravanasAtivas) {
                        if (c->getId() > maiorId && c->getId() < 10) {
                            maiorId = c->getId();
                        }
                    }
                    maiorId++;

                    if (maiorId > 9) {
                        cout << "Atingiu O Numero Maximo De Caravanas ( " << maiorId << " )" << endl;
                        goto finalWhile;
                    }

                    //nao sei como adicionar uma caravana, de resto a logica esta criada.

                    Caravana::criar(caravanasAtivas, grelha);
                    Caravana::caravanaAparecer(caravanasAtivas, grelha, tipo);

                    cout << "Caravana com ID " << maiorId << " criada e atribuída à cidade " << cidade << "." << endl;

                } else
                    cout << "O Jogador Nao Possui Dinherio Para Comprar A Caravana. Preco: " << grelha.getPrecoC()
                         << "." << endl;
            } else
                cout << "Tipo De Caravana Invalido." << endl;

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
    char *bufferData = nullptr;
    int n = fase1(grelha, jogador, itensAtivos, caravanasAtivas, bufferData);

    if (n == 1) {
        cerr << "Erro Na Fase 1." << endl;
        exit(0);
    } else if (n == 2)
        exit(0);

    int m = fase2(grelha, jogador, itensAtivos, caravanasAtivas, bufferData);

    if (m == 1) {
        cerr << "Erro Na Fase 2." << endl;
        exit(0);
    }

    return 0;
}