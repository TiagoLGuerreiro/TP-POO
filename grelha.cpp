
#include "grelha.h"
#include "jogador.h"
#include "item.h"
#include <fstream>
#include <iostream>
#include <sstream>
#define MAX_DATA_SIZE 1000

using namespace std;

// Construtor padrão
Grelha::Grelha() : linhas(0), colunas(0){}

// Ler o ficheiro e carregar a grelha
bool Grelha::lerFicheiro(const string &nomeFicheiro, Jogador &jogador, vector<Item*> &item) {
    ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        cerr << "Erro ao abrir o ficheiro: " << nomeFicheiro << endl;
        return false;
    }

    string linha;
    string token;
    int linhasMapa = 0, colunasMapa = 0, moedas = 0, instante_entre_item = 0, duracao_item = 0, max_itens = 0;

    // Ler a linha que diz qual o número de linhas
    if (getline(ficheiro, linha)) {
        istringstream ss(linha);
        ss >> token; // armazena a primeira palavra do istringstream, neste caso é "linhas"
        if (token != "linhas" || !(ss >> linhasMapa)) {
            cout << "Erro ao ler o numero de linhas no ficheiro" << endl;
            return false;
        }
    }

    // Ler a linha que diz qual o número de colunas
    if (getline(ficheiro, linha)) {
        istringstream ss(linha);
        ss >> token; //  linha 27 para as colunas
        if (token != "colunas" || !(ss >> colunasMapa)) {
            cout << "Erro ao ler o numero de colunas no ficheiro" << endl;
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
            cout << "Erro: Linha " << linhaAtual + 1 << " do ficheiro nao tem " << colunas << " colunas!" << endl;
            return false;
        }
        for (int coluna = 0; coluna < colunas; ++coluna) {
            mapa[linhaAtual * colunas + coluna].setTipo(linha[coluna]);  // Preenche o mapa
        }
        ++linhaAtual;
    }

    while (getline(ficheiro, linha)) {
        istringstream ss(linha);
        ss >> token;
        if (token == "moedas") {
            if (!(ss >> moedas)) {
                cout << "Erro ao ler o numero de moedas no ficheiro!" << endl;
                return false;
            }
            jogador.setMoedas(moedas);  // Utiliza um setter para definir o nº de moedas
        }
        if (token == "instantes_entre_novos_itens") {
            if (!(ss >> instante_entre_item)) {
                cout << "Erro ao ler o numero de instantes entre novos itens no ficheiro!" << endl;
                return false;
            }
        }
        if (token == "duração_item") {
            if (!(ss >> duracao_item)) {
                cout << "Erro ao ler o numero de instantes entre novos itens no ficheiro!" << endl;
                return false;
            }
        }
        if (token == "max_itens") {
            if (!(ss >> max_itens)) {
                cout << "Erro ao ler o numero máximo de itens no ficheiro!" << endl;
                return false;
            }
        }
    }

    for (Item* i : item) {
        if (i != nullptr) {
            i->setItem(instante_entre_item, duracao_item, max_itens); // Utiliza um setter para definir valores
        }
    }

    ficheiro.close();
    //fazer verificação para fecho do ficheiro (?)

    return true;
}

// Função para mostrar a grelha no ecrã
void Grelha::mostrarGrelha() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << mapa[i * colunas + j].getTipo();  // Acede ao tipo de cada posição no mapa
        }
        cout << endl;
    }
}
int pointer = 0;
void copyData(char* data, char* buffer) {
    int i = 0;
    while (buffer[i]) {
        if (MAX_DATA_SIZE < pointer) {
            data[pointer++] = buffer[i];
        } else {
            return;
        }
    }
}

int Grelha::guardarbuffer(){
    FILE* fileopen = fopen("mapa.txt", "r");
    char data[MAX_DATA_SIZE] = "";
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), fileopen)){
        copyData(data, buffer);
    }
    return 1;
}