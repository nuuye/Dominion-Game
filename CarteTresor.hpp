#ifndef __CarteTresor_hpp
#define __CarteTresor_hpp
#include <iostream>
#include "Carte.hpp"

/**
 * @brief classe qui hérite de carte.
 * Les cartes tresors sont des cartes qui permettent l'achat d'autres cartes. 
 * 
 */
class CarteTresor : public Carte
{
private:
	int valeur;

public:
	void affiche() override { std::cout << ""; };
	CarteTresor(string name, int valeur, int price);
	virtual ~CarteTresor(){};
	int getValeur();
	//string getName() const  { return name; };
	//int getPrice() override { return price; };
};

#endif
