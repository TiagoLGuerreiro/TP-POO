#include "grelha.h"
#include "jogador.h"
#include "item.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    Grelha grelha;
    Jogador jogador;
    Item item;
    string opcao;

    char instante;
    if (!grelha.lerFicheiro("mapa.txt", jogador, item)) {
        cout << "Erro ao carregar o mapa!" << endl;
        return 1;
    }

    cout << "======================================" << endl;
    cout << "Fase 1 Da Simulacao:" << endl;
    cout << "Comandos: config <nomeFicheiro>, sair." << endl;
    getline(cin, opcao);

    if (strcmp(opcao.c_str(), "config mapa.txt") == 0) {

        do {
            grelha.mostrarGrelha();

            cout << "Jogador tem " << jogador.getMoedas() << " moedas." << endl;
            cout << "Instante entre item " << item.getInstanteEntreItem() << endl;
            cout << "Duracao item " << item.getDuracao() << endl;
            cout << "Max itens " << item.getMaxItens() << endl;

            item.Arca(jogador);

            cout << "Jogador tem " << jogador.getMoedas() << " moedas." << endl;

            // cout << item.ItemAparecer(grelha);

            cout << "Avancar instante? S/N - " << endl;
            cin >> instante;
            jogador.setInstante(jogador.getInstante() + 1);
        } while (instante == 'S' || instante == 's');
    } else{
        cout << "Decidiu Sair, Ate A Proxima" << endl;
        return 0;
    }

    cout << "Fim De Jogo" << endl;
    cout << "Percorreu: " << jogador.getInstante() << " Instantes.";

    return 0;
}
