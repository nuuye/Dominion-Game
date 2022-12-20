#include <iostream>
#include "Carte.hpp"
#include <algorithm>


Carte::Carte(string name, int price)
{
    this->name = name;
    this->price = price;
}
Carte::Carte(int price)
{
    this->price = price;
}
// int Carte::getPrice()
// {
//     return price;
// }

// string Carte::getName() const
// {
//     return name;
// }
string Carte::getLowerCuttedName() const
{
    size_t found = this->getName().find(' ');
    string card = this->getName().substr(0, found);
    std::transform(card.begin(), card.end(), card.begin(), ::tolower);
    return card;
}
