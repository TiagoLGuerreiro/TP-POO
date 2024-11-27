#ifndef GRELHA_H
#define GRELHA_H

#include <vector>
#include <string>
using namespace std;
// classe de cada posicao do mapa
class Posicao {
private:
    char tipo; // 'D' = Deserto, 'M' = Montanha, 'C' = Cidade, 'a'-'z' = Cidades nomeadas, '1'-'9' = caravanas, '!' = bárbara

public:
    Posicao() : tipo('D') {}
    void setTipo(char novoTipo) { tipo = novoTipo; }
    char getTipo() const { return tipo; }
};

// Classe que representa a grelha do deserto
class Grelha {
private:
    int linhas; // Número de linhas do mapa
    int colunas; // Número de colunas do mapa
    vector<vector<Posicao>> mapa; // Mapa bidimensional de posições
    // (usamos vetores para formar matrizes porque é mais fácil redimensionar que arrays)

public:
    Grelha();
    bool lerFicheiro(const string& nomeFicheiro);
    void mostrarGrelha() const;
};

#endif // GRELHA_H


