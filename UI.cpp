#include "grelha.h"
#include "jogador.h"
#include "item.h"
#include <iostream>
#include <cstring>
#include "UI.h"
#include <string>
#include <sstream>

void mostraInformacoes(int moedas){
    cout << "Jogador tem " << moedas<< " moedas." << endl;
}

int fase1(){
    Grelha grelha;
    Jogador jogador;
    Item item;
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

    else if(comando == "sair"){
        cout << "Decidiu Sair, Ate Breve" << endl;
        return 0;
    }

    else{
        cerr << "Comando Invalido" << endl;
        return 0;
    }

    if (!grelha.lerFicheiro(nomeFicheiro, jogador, item)) {
        return 0;
    }

    if (strcmp(opcao.c_str(), "config mapa.txt") == 0){
        grelha.mostrarGrelha();
        mostraInformacoes(jogador.getMoedas());
    }
    else {
        cerr << "Config Errada!" << endl;
        return 1;
    }
    return 0;
}

int fase2(){

    string escolha;
    cout << "\nComandos Disponoveis: " << endl;
    cout << "config <nomeFicheiro>, prox <n>, comprac <C> <T>, precos, cidade <C>, caravana <C>, compra <N> <M>, vende <N>, move <N> <X>, auto <N>, stop <N>, barbaro <l> <c>, areia <l> <c> <r>, moedas <N>, tripul <N> <T>, saves <nome>, loads <nome>, lists, dels <nome>, terminar" << endl;
    getline(cin, escolha);

    switch (escolha) {
        case c:
    }
    return 0;
}



int UserInterface(){
    fase1();
    fase2();

    return 0;
}