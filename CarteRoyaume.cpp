#include <iostream>
#include "CarteRoyaume.hpp"
#include "Carte.hpp"
class Carte;

/**
 * @brief Constructeur d'une carte royaume
 *
 * @param name
 * @param price
 */
CarteRoyaume::CarteRoyaume(string name, int price) : Carte(price)
{
    this->name = name;
    this->price = price;
    this->points = 0;
}
