#include <iostream>
#include "Carte.hpp"
#include <algorithm>

/**
 * @brief Constructeur d'une carte
 *
 * @param name
 * @param price
 */
Carte::Carte(string name, int price)
{
    this->name = name;
    this->price = price;
}
/**
 * @brief Constructeur d'une carte avec comme seul paramètre price.
 * Permet aux constructeurs des enfants de carte de pouvoir définir price dans leur propre constructeur.
 *
 * @param price
 */
Carte::Carte(int price)
{
    this->price = price;
}
/**
 * @brief fonction qui permet de récupérer le nom d'une carte sans le prix contenu dans le nom et l'emoji;
 * Supprime également la majuscule.
 *
 * @return string
 */
string Carte::getLowerCuttedName() const
{
    size_t found = this->getName().find(' ');
    string card = this->getName().substr(0, found);
    std::transform(card.begin(), card.end(), card.begin(), ::tolower);
    return card;
}
