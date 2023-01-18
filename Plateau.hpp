#ifndef __Plateau_hpp
#define __Plateau_hpp
#include <iostream>
#include "Carte.hpp"
#include "CarteRoyaume.hpp"
#include <map>
#include <vector>
using namespace std;
/**
 * @brief La classe plateau représente le jeu posé sur une table par exemple.
 * Le plateau contient la réserve ainsi que le rébus.
 *
 */
class Plateau
{
private:
public:
    Plateau(){};
    map<Carte *, int> reserve;
    vector<Carte *> rebus;
    void affichePlateau() const;
    void removeCard(Carte *carte);
};

#endif