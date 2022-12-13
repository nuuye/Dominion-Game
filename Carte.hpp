#ifndef __Carte_hpp
#define __Carte_hpp
#include <iostream>
#include <string>
using namespace std;
class CarteVictoire;
class CarteRoyaume;

class Carte
{
private:
	string nom;
	int prix;

public:
	virtual void affiche() = 0; /* Ne pas oublier de la redéfinir dans les ss-classes pour qu'elles ne soient pas abstraites aussi */
};

#endif
