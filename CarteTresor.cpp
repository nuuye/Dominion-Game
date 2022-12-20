#include <iostream>
#include "CarteTresor.hpp"

CarteTresor::CarteTresor(string name, int valeur, int price) : Carte(price)
{
    this->name = name;
    this->valeur = valeur;
    this->price = price;
};

// void CarteTresor::affiche() override
// {
//     std::cout << "";
// }

int CarteTresor::getValeur()
{
    return valeur;
};
