#include "grelha.h"
#include <iostream>

using namespace std;

int main() {
    Grelha grelha;

    if (!grelha.lerFicheiro("mapa.txt")) {
        cout << "Erro ao carregar o mapa!" << endl;
        return 1;
    }

    grelha.mostrarGrelha();

    return 0;
}