#ifndef __Plateau_hpp
#define __Plateau_hpp
#include <iostream>
#include "Carte.hpp"
#include "CarteRoyaume.hpp"
#include <map>
#include <vector>
using namespace std;

class Plateau
{
private:
public:
    Plateau(){};
    map<Carte *, int> reserve;
    vector<Carte *> rebus;
    void affichePlateau() const;
    void removeCard(Carte *carte);
    bool isInReserve(string cardName);
};

#endif