
#include "grelha.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Construtor padrão
Grelha::Grelha() : linhas(0), colunas(0){}

// Ler o ficheiro e carregar a grelha
bool Grelha::lerFicheiro(const string &nomeFicheiro) {
    ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        cout << "Erro ao abrir o ficheiro: " << nomeFicheiro << endl;
        return false;
    }

    string linha;
    int linhasMapa = 0, colunasMapa = 0;

    // Ler a linha que diz qual o número de linhas
    if (getline(ficheiro, linha)) {
        istringstream ss(linha);
        string token;
        ss >> token; // armazena a primeira palavra do istringstream, neste caso é "linhas"
        if (token != "linhas" || !(ss >> linhasMapa)) {
            cout << "Erro ao ler o número de linhas no ficheiro" << endl;
            return false;
        }
    }

    // Ler a linha que diz qual o número de colunas
    if (getline(ficheiro, linha)) {
        istringstream ss(linha);
        string token;
        ss >> token; //  linha 27 para as colunas
        if (token != "colunas" || !(ss >> colunasMapa)) {
            cout << "Erro ao ler o número de colunas no ficheiro" << endl;
            return false;
        }
    }

    // Inicializar a grelha com as dimensões lidas
    linhas = linhasMapa;
    colunas = colunasMapa;
    mapa.resize(linhas * colunas);

    // Ler o mapa linha por linha
    int linhaAtual = 0;
    while (getline(ficheiro, linha) && linhaAtual < linhas) {
        if ((int) linha.size() != colunas) {  // Verifica se o número de colunas está correto
            cout << "Erro: Linha " << linhaAtual + 1 << " do ficheiro não tem " << colunas << " colunas!" << endl;
            return false;
        }
        for (int coluna = 0; coluna < colunas; ++coluna) {
            mapa[linhaAtual * colunas + coluna].setTipo(linha[coluna]);  // Preenche o mapa
        }
        ++linhaAtual;
    }

    ficheiro.close();
    //fazer verificação para fecho do ficheiro (?)

    return true;
}

// Função para mostrar a grelha no ecrã
void Grelha::mostrarGrelha() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << mapa[i * colunas + j].getTipo();  // Acessa o tipo de cada posição no mapa
        }
        cout << endl;
    }
}