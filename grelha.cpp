#include "grelha.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Grelha::Grelha() : linhas(0), colunas(0) {}

// Ler o ficheiro e carregar a grelha
bool Grelha::lerFicheiro(const string& nomeFicheiro) {
    ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        cerr << "Erro ao abrir o ficheiro: " << nomeFicheiro << endl;
        return false;
    }

    string linha;
    int linhasMapa = 0, colunasMapa = 0;

    // Ler a linha que diz qual o número de linhas
    if (getline(ficheiro, linha)) {
        istringstream ss(linha);
        string token;
        ss >> token; // armazena a primeira palavra do istringstream, neste caso é "linhas", o ss apontará o nº
        if (token != "linhas" || !(ss >> linhasMapa)) {
            cerr << "Erro ao ler o número de linhas no ficheiro" << endl;
            return false;
        }
    }

    // Ler a linha que diz qual o número de colunas
    // (getline é um ponteiro interno, passa para a linha de baixo automaticamente sempre que é chamado)
    if (getline(ficheiro, linha)) {
        istringstream ss(linha);
        string token;
        ss >> token; // "colunas"
        if (token != "colunas" || !(ss >> colunasMapa)) {
            cerr << "Erro ao ler o número de colunas no ficheiro" << endl;
            return false;
        }
    }

    // Redimensionar o mapa de acordo com as dimensões lidas
    linhas = linhasMapa;
    colunas = colunasMapa;
    mapa = vector<vector<Posicao>>(linhas, vector<Posicao>(colunas));

    // Ler o mapa linha por linha
    int linhaAtual = 0;
    while (getline(ficheiro, linha) && linhaAtual < linhas) {
        if ((int)linha.size() != colunas) { // verifica se o num de colunas é igual ao tamanho da mesma
            cerr << "Erro: Linha " << linhaAtual + 1 << " do ficheiro não tem " << colunas << " colunas!" << endl;
            return false;
        }
        for (int coluna = 0; coluna < colunas; ++coluna) {
            mapa[linhaAtual][coluna].setTipo(linha[coluna]);
        }
        ++linhaAtual;
    }

    if (linhaAtual != linhas) {
        cerr << "Erro: O número de linhas do mapa no ficheiro não corresponde a " << linhas << "!" << endl;
        return false;
    }

    ficheiro.close();
    return true;
}

// Função para mostrar a grelha no ecrã
void Grelha::mostrarGrelha() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << mapa[i][j].getTipo();
        }
        cout << endl;
    }
}

