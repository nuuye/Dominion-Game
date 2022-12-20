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
protected:
	string name;
	int price;

public:
	virtual void affiche() = 0; /* Ne pas oublier de la redéfinir dans les ss-classes pour qu'elles ne soient pas abstraites aussi */
	Carte(string name, int price);
	Carte(int price);
	virtual ~Carte() { delete this; };
	virtual int getPrice() { return price; };
	virtual string getName() const { return name; };
	virtual string getLowerCuttedName() const;
};

#endif
