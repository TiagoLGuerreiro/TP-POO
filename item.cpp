//
// Created by tiago on 26/11/2024.
//

#include "item.h"
#include "jogador.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Item::Item() : instante_entre_item(0), tipo(), max_itens(0), duracao(0){}

bool Item::CaixaPandora(){
    return true;
}

bool Item::Arca(Jogador &jogador){
    int totalmoedas = jogador.getMoedas() + jogador.getMoedas() * 0.1;
    jogador.setMoedas(totalmoedas);
    return true;
}

bool Item::Jaula(){
    return true;
}

bool Item::Mina(){
    return true;
}

bool Item::Surpresa(){
    return true;
}