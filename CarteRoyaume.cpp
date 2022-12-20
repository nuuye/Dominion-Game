#include <iostream>
#include "CarteRoyaume.hpp"
#include "Carte.hpp"
class Carte;
// void CarteRoyaume::affiche() override
// {
//     std::cout << "";
// }

CarteRoyaume::CarteRoyaume(string name, int price) : Carte(price)
{
    this->name = name;
    this->price = price;
}
