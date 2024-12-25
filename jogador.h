//
// Created by tiago on 25/11/2024.
//

#ifndef TP_JOGADOR_H
#define TP_JOGADOR_H

class Jogador{
private:
    int moedas;
    int quantidadesCaravanas;
    int vida;
    int instanteAtual;

public:
    Jogador(int moedas);

    int getMoedas() const { return moedas; }
    int getInstante() const { return instanteAtual; }

    // Método setter, para permitir modificações externas
    void setMoedas(int m) { moedas = m; }
    void setInstante(int i) { instanteAtual = i; }
};
#endif //TP_JOGADOR_H
