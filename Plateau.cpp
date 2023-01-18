#include <iostream>
#include "Plateau.hpp"
#include "CarteRoyaume.hpp"

/**
 * @brief fonction qui permet d'afficher les cartes de la reserve ainsi que leurs quantités
 * 
 */
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

/**
 * @brief fonction qui permet de supprimer une carte de la réserve.
 * La pile de la carte en question est alors décrémentée de 1
 * 
 * @param carte 
 */
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