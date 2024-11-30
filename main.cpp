#include "grelha.h"
#include "jogador.h"
#include "item.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    Grelha grelha;
    Jogador jogador;
    Item item;

    if (!grelha.lerFicheiro("mapa.txt", jogador, item)) {
        cout << "Erro ao carregar o mapa!" << endl;
        return 1;
    }

    grelha.mostrarGrelha();

    cout << "Jogador tem " << jogador.getMoedas() << " moedas." << endl;
    cout << "Instante entre item " << item.getInstanteEntreItem() << endl;
    cout << "Duracao item " << item.getDuracao() << endl;
    cout << "Max itens " << item.getMaxItens() << endl;

    item.Arca(jogador);

    cout << "Jogador tem " << jogador.getMoedas() << " moedas." << endl;


    return 0;
}
