
#include "grelha.h"
#include "jogador.h"
#include "buffer.h"
#include "item.h"
#include <iostream>
#include <sstream>
#include <string.h>
#define MAX_DATA_SIZE 1000

using namespace std;

// Construtor padrão
Grelha::Grelha() : linhas(0), colunas(0){}


void Grelha::setCompraM(int valor) {
    compraM = valor;
}

void Grelha::setVendaM(int valor) {
    vendaM = valor;
}

void Grelha::setPrecoC(int valor) {
    precoC = valor;
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
void copyData(char* data, const char* buffer, int& pointer, int maxSize) {
    int i = 0;
    while (buffer[i]) {
        if (pointer < maxSize) {
            data[pointer++] = buffer[i];
        } else {
            return;
        }
        i++;
    }
}

char* Grelha::lerFicheiro(const string &nomeFicheiro, Jogador &jogador, vector<Item *> &item) {
    FILE* fileopen = fopen(nomeFicheiro.c_str(), "r");
    if(!fileopen) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return nullptr;
    }

    char* data = new char[MAX_DATA_SIZE]();
    char buffer[100];
    memset(data, 0, MAX_DATA_SIZE);
    //lê o conteuido do arquivo e guarda no buffer 'data'
    pointer = 0;
    while (fgets(buffer, sizeof(buffer), fileopen)){
        copyData(data, buffer, pointer, MAX_DATA_SIZE);
    }

    if (fclose(fileopen) != 0) {
        cerr << "Erro ao fechar o arquivo!" << endl;
        return nullptr;
    }

    istringstream ss(data);
    string linha, token;

    int linhasMapa = 0, colunasMapa = 0, moedas, instante_entre_item = 0, duracao_item = 0, max_itens = 0,
            valorVendaM = 0, valorCompraC = 0;

    // Ler a linha que diz qual o número de linhas
    if (getline(ss, linha)) {
        istringstream lineStream(linha);
        lineStream >> token; // armazena a primeira palavra do istringstream, neste caso é "linhas"
        if (token != "linhas" || !(lineStream >> linhasMapa)) {
            cerr << "Erro ao ler o numero de linhas no ficheiro" << endl;
            return nullptr;
        }
    }

    // Ler a linha que diz qual o número de colunas
    if (getline(ss, linha)) {
        istringstream lineStream(linha);
        lineStream >> token; // armazena a primeira palavra do istringstream, neste caso é "colunas"
        if (token != "colunas" || !(lineStream >> colunasMapa)) {
            cerr << "Erro ao ler o numero de colunas no ficheiro" << endl;
            return nullptr;
        }
    }

    // Inicializar a grelha com as dimensões lidas
    linhas = linhasMapa;
    colunas = colunasMapa;
    mapa.resize(linhas * colunas);

    // Ler o mapa linha por linha
    int linhaAtual = 0;
    while (getline(ss, linha) && linhaAtual < linhas) {
        if ((int) linha.size() != colunas) {  // Verifica se o número de colunas está correto
            cerr << "Erro: Linha " << linhaAtual + 1 << " do ficheiro nao tem " << colunas << " colunas!" << endl;
            return nullptr;
        }
        for (int coluna = 0; coluna < colunas; ++coluna) {
            mapa[linhaAtual * colunas + coluna].setTipo(linha[coluna]);  // Preenche o mapa
        }
        ++linhaAtual;
    }

    while (getline(ss, linha)) {
        istringstream lineStream(linha);
        lineStream >> token;
        if (token == "moedas") {
            if (!(lineStream >> moedas)) {
                cerr << "Erro ao ler o numero de moedas no ficheiro!" << endl;
                return nullptr;
            }
            jogador.setMoedas(moedas);  // Utiliza um setter para definir o nº de moedas
        }
        if (token == "instantes_entre_novos_itens") {
            if (!(lineStream >> instante_entre_item)) {
                cerr << "Erro ao ler o numero de instantes entre novos itens no ficheiro!" << endl;
                return nullptr;
            }
        }
        if (token == "duração_item") {
            if (!(lineStream >> duracao_item)) {
                cerr << "Erro ao ler o numero de instantes entre novos itens no ficheiro!" << endl;
                return nullptr;
            }
        }
        if (token == "max_itens") {
            if (!(lineStream >> max_itens)) {
                cerr << "Erro ao ler o numero máximo de itens no ficheiro!" << endl;
                return nullptr;
            }
        }
        if (token == "preço_venda_mercadoria") {
            if (!(lineStream >> valorVendaM)) {
                cerr << "Erro ao ler o numero de moedas no ficheiro!" << endl;
                return nullptr;
            }
            setVendaM(valorVendaM);
        }
        if (token == "preço_compra_mercadoria") {
            if (!(lineStream >> valorCompraC)) {
                cerr << "Erro ao ler o numero de moedas no ficheiro!" << endl;
                return nullptr;
            }
            setCompraM(valorCompraC);
        }
        if (token == "preço_caravana") {
            if (!(lineStream >> valorCompraC)) {
                cerr << "Erro ao ler o numero de moedas no ficheiro!" << endl;
                return nullptr;
            }
            setPrecoC(valorCompraC);
        }
    }

    for (Item* i : item) {
        if (i != nullptr) {
            i->setItem(instante_entre_item, duracao_item, max_itens); // Utiliza um setter para definir valores
        }
    }

    return data;
}