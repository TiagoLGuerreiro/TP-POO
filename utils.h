//
// Created by adm on 24/12/2024.
//

#ifndef TP_UTILS_H
#define TP_UTILS_H
#include <vector>
#include "item.h"
#include "grelha.h"
#include "caravana.h"
using namespace std;

void destruirTodosItens(vector<Item*>& itensAtivos, Grelha &grelha);
void destruirCaravana(vector<Caravana*>& caravanasAtivas, int id, int pos, Grelha &grelha);
Caravana* encontrarCaravanaPorID(const vector<Caravana*>& caravanasAtivas, int id);


#endif //TP_UTILS_H
