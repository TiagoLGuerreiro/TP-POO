//
// Created by tiago on 25/11/2024.
//

#ifndef TP_JOGADOR_H
#define TP_JOGADOR_H

class Jogador{
private:
    int moedas = 0;
    int quantidadesCaravanas = 0;
    int vida = 0;

public:
    Jogador();

    int getMoedas() const { return moedas; }

    // Método setter, para permitir modificações externas
    void setMoedas(int m) { moedas = m; }
};
#endif //TP_JOGADOR_H
