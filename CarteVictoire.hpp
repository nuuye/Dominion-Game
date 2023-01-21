#ifndef __CarteVictoire_hpp
#define __CarteVictoire_hpp
#include <iostream>
#include "Carte.hpp"

/**
 * @brief classe qui hérite de carte.
 * Les cartes Victoires sont des cartes qui permettent de gagner des points 
 * 
 */
class CarteVictoire : public Carte
{
private:
	int points;

public:
	void affiche() override { std::cout << ""; };
	CarteVictoire(string name, int points, int price);
	~CarteVictoire(){};
};

#endif
