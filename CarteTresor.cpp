#include <iostream>
#include "CarteTresor.hpp"

/**
 * @brief Constructeur d'une carte tresor.
 *
 * @param name
 * @param valeur
 * @param price
 */
CarteTresor::CarteTresor(string name, int valeur, int price) : Carte(price)
{
    this->name = name;
    this->valeur = valeur;
    this->points = 0;
};

/**
 * @brief getter qui permet de récupérer la valeur d'une carte tresor
 *
 * @return int
 */
int CarteTresor::getValeur()
{
    return valeur;
};
