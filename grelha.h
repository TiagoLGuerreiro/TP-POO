#ifndef GRELHA_H
#define GRELHA_H

#include <vector>
#include <string>

using namespace std;

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

public:
    Grelha();

    bool lerFicheiro(const string &nomeFicheiro);

    void mostrarGrelha() const;
};

#endif // GRELHA_H