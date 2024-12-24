#include "grelha.h"
#include "jogador.h"
#include "item.h"
#include <iostream>
#include <cstring>
#include "UI.h"
#include <string>
#include <sstream>
#include <functional>

void mostraInformacoes(int moedas) {
    cout << "Jogador tem " << moedas << " moedas." << endl;
}

int fase1(Grelha &grelha, Jogador jogador, vector<Item*> &itensAtivos) {
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
        grelha.mostrarGrelha();
    } else {
        cerr << "Config Errada!" << endl;
        return 1;
    }
    return 0;
}

int fase2(Grelha &grelha, Jogador jogador, vector<Item*> &itensAtivos) {

    string opcaoComando, nome, resto; //nome = nomeFicheiro
    string escolha;
    int nInstantes = 0;
    int j;

    do {

        cout << "\nComandos Disponiveis: " << endl;
        cout
                << "exec <nomeFicheiro>, prox <n>, comprac <C> <T>, precos, cidade <C>, caravana <C>, compra <N> <M>, vende <N>, move <N> <X>, auto <N>, stop <N>, barbaro <l> <c>, areia <l> <c> <r>, moedas <N>, tripul <N> <T>, saves <nome>, loads <nome>, lists, dels <nome>, terminar."
                << endl;
        getline(cin, escolha);


        istringstream iss(escolha);

        iss >> opcaoComando;

        iss >> resto;
        //grelha.lerFicheiro("mapa.txt", jogador, itensAtivos); // MUDAR ESTE MAPA.TXT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Ganda otário rafa, estive 1 hora a tentar descobrir porque é que o mapa voltava ao
// original e era por causa dessa linha de merda
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
            else if(stoi(resto) > 0)
                nInstantes = stoi(resto);

            if(jogador.getInstante() % 10 == 0 || jogador.getInstante() == 0)
                j = 0;

            jogador.setInstante(jogador.getInstante() + nInstantes);
            cout << "Instante Atual - " << jogador.getInstante() << endl;

            for (int i = 0; i < nInstantes; ++i) {      // pular 1 instante ou resto instantes.
                ++j;
                Item::atualizarItens(itensAtivos, jogador.getInstante());
                if(j % 10 == 0){
                    Item::gerarItem(grelha, itensAtivos, 5, 20);
                    grelha.mostrarGrelha();
                    j=0;
                }
            }

        } else if(opcaoComando == "terminar"){
            cout << "Escolheu Sair, Ate Uma Proxima." << endl;
            cout << "Pontuacao final - " << endl; // falta adicionar aqui a pontuacao
            UserInterface();
        } else {
            cerr << "Comando Invalido." << endl;
        }

    }while(opcaoComando != "terminar");

    return 0;
}


int UserInterface() {
    Grelha grelha;
    Jogador jogador;
    vector<Item*> itensAtivos;

    int n = fase1(grelha, jogador, itensAtivos);

    if (n == 1) {
        cerr << "Erro Na Fase 1." << endl;
        exit(0);
    } else if (n == 2)
        exit(0);

    int m = fase2(grelha, jogador, itensAtivos);

    if (m == 1) {
        cerr << "Erro Na Fase 2." << endl;
        exit(0);
    }

    return 0;
}