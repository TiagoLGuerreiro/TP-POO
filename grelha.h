#ifndef GRELHA_H
#define GRELHA_H

#include <vector>
#include <string>
#include "jogador.h"

using namespace std;

class Item;

// classe de cada posição do mapa
class Posicao {
private:
    char tipo; // 'D' = Deserto, 'M' = Montanha, 'C' = Cidade, 'a'-'z' = Cidades nomeadas, '1'-'9' = caravanas, '!' = bárbara

public:
    Posicao() : tipo('D') {}

    //setter
    void setTipo(char novoTipo) { tipo = novoTipo; }

    //getter
    char getTipo() const { return tipo; }
};

class Grelha {
private:
    int linhas;
    int colunas;
    vector<Posicao> mapa; // Vetor unidimensional para o mapa
    int compraM = 0, vendaM = 0, precoC = 0;

public:
    Grelha();

    //getters
    int getColunas() {return colunas;}
    int getLinhas() {return linhas;}
    int getCompraM() {return compraM;}
    int getVendaM() {return vendaM;}
    int getPrecoC() {return precoC;}

    //setters
    void setCompraM(int valor);
    void setVendaM(int valor);
    void setPrecoC(int valor);

    bool lerFicheiro(const string &nomeFicheiro, Jogador &jogador, vector<Item*> &item);

    void mostrarGrelha() const;

    int guardarbuffer();
    vector<Posicao>& getMapa() { return mapa; }
};

#endif // GRELHA_H