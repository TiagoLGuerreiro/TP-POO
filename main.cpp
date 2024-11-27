#include "grelha.h"
#include <iostream>
using namespace std;

int main() {
    Grelha grelha;

    if (!grelha.lerFicheiro("mapa.txt")) {
        cerr << "Erro ao carregar o mapa!" << endl;
        return 1;
    }

    cout << "Mapa carregado com sucesso!" << endl;
    grelha.mostrarGrelha();

    return 0;
}


