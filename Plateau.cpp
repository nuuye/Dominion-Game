#include <iostream>
#include "Plateau.hpp"
#include "CarteRoyaume.hpp"

void Plateau::affichePlateau() const
{
    std::cout << "➡️ Le plateau possède les cartes suivantes : " << std::endl;
    for (const auto &keyValue : reserve)
    {
        std::cout << keyValue.first->getName() << " : " << keyValue.second << " | ";
    }
    std::cout << "\n"
              << std::endl;
}

void Plateau::removeCard(Carte *carte)
{
    for (const auto &keyValue : reserve)
    {
        if (keyValue.first->getName() == carte->getName())
        {
            reserve[keyValue.first] = keyValue.second - 1;
        }
    }
}

bool Plateau::isInReserve(string cardName)
{
    bool isInReserve = false;
    for (const auto &carte : reserve)
    {
        if (cardName == carte.first->getName())
        {
            isInReserve = true;
        }
    }
    return isInReserve;
}