#ifndef __Carte_hpp
#define __Carte_hpp
#include <iostream>
#include <string>
using namespace std;
class CarteVictoire;
class CarteRoyaume;

/**
 * @brief La classe carte est une classe abstraite.
 * Ses enfants sont carteRoyaume, carteTresor ainsi que carteVictoire
 * La classe carte représente une carte dans le jeu.
 *
 */
class Carte
{
private:
protected:
	string name;
	int price;
	int points = 0; // pour les cartes victoires

public:
	virtual void affiche() = 0; /* Ne pas oublier de la redéfinir dans les ss-classes pour qu'elles ne soient pas abstraites aussi */
	Carte(string name, int price);
	Carte(int price);
	virtual ~Carte(){};
	virtual int getPrice() { return price; };
	virtual string getName() const { return name; };
	virtual string getLowerCuttedName() const;
	virtual int getPoints() { return points; };
};

#endif
