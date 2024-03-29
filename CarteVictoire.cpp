#include <iostream>
#include "CarteVictoire.hpp"
#include <string>
using namespace std;

/**
 * @brief Constructeur d'une carte victoire
 *
 * @param name
 * @param points
 * @param price
 */
CarteVictoire::CarteVictoire(string name, int points, int price) : Carte(price)
{
	this->name = name;
	this->points = points;
}