#ifndef __CarteVictoire_hpp
#define __CarteVictoire_hpp
#include <iostream>
#include "Carte.hpp"

class CarteVictoire : public Carte
{
private:
	int points;

public:
	void affiche();
};

#endif
