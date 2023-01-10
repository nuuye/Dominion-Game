#include <iostream>
#include "Joueur.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include "CarteTresor.hpp"
#include <typeinfo>
#include <cctype>

/**
 * Constructeur.
 * Fixe l'instant à une valeur précise.
 * @param timemillis Millisecondes écoulées depuis le 1er janvier 1970
 */
Joueur::Joueur(string name)
{
    this->name = name;
    this->actions = 1;
    this->isMyTurn = false;
    this->buyPoints = 1;
}

void Joueur::setBuyPoints(int buyPoints)
{
    this->buyPoints = buyPoints;
}

void Joueur::setActions(int actions)
{
    this->actions = actions;
}

void Joueur::setMoney(int money)
{
    money = money;
}

void Joueur::setMyTurn(bool isMyTurn)
{
    this->isMyTurn = isMyTurn;
}

int Joueur::getBuyPoints()
{
    return buyPoints;
}
vector<Carte *> Joueur::getHand()
{
    return hand;
}

vector<Carte *> Joueur::getDefausse()
{
    return defausse;
}

int Joueur::getActions()
{
    return this->actions;
}

int Joueur::getMoney()
{
    return money;
}

bool Joueur::getTurn()
{
    return this->isMyTurn;
}

int Joueur::getPiocheSize()
{
    return this->pioche.size();
}

int Joueur::getHandSize()
{
    return this->hand.size();
}

int Joueur::getDefausseSize()
{
    return this->defausse.size();
}

int Joueur::getVictoryPointsAmount()
{
    int count = 0;
    std::cout << "PIOCHE SIZE : " << this->getPiocheSize() << std::endl;
    for (int i = 0; i < this->getPiocheSize(); i++)
    {
        count += pioche[i]->getPoints();
    }
    return count;
}

bool Joueur::possedeCarte(string cardName)
{
    bool contain = false;
    for (const auto &carte : hand)
    {
        if (carte->getName() == cardName)
        {
            contain = true;
        }
    }
    return contain;
}
void Joueur::supprimeCarteMain(string cardToDelete)
{
    // cardToDelete[0] = toupper(cardToDelete[0]);
    auto it = std::find_if(this->hand.begin(), this->hand.end(), [cardToDelete](const auto &carte)
                           { return dynamic_cast<Carte *>(carte) != nullptr && carte->getName() == cardToDelete; });
    if (it != this->hand.end())
    {
        this->ajouteCarteDefausse(*it);
        this->hand.erase(it);
        std::cout << "JUST AFTER" << std::endl;
        this->afficheDefausse();
    }
}

void Joueur::supprimeCartePioche(string cardToDelete)
{
    auto it = std::find_if(this->pioche.begin(), this->pioche.end(), [cardToDelete](const auto &carte)
                           { return dynamic_cast<Carte *>(carte) != nullptr && carte->getName() == cardToDelete; });
    if (it != this->pioche.end())
    {
        this->pioche.erase(it);
    }
}

bool Joueur::acheteCarte(Carte *carte, int additionalMoney)
{
    if (this->money + additionalMoney >= carte->getPrice() && this->buyPoints >= 1)
    {
        this->defausse.push_back(carte);
        this->buyPoints -= 1;
        this->money -= (carte->getPrice() - additionalMoney);
        int cardPriceCounter = carte->getPrice() - additionalMoney;
        while (cardPriceCounter != 0)
        {
            if (cardPriceCounter >= 3 && this->possedeCarte("Or (6💰)"))
            {
                this->supprimeCarteMain("Or (6💰)");
                cardPriceCounter -= 3;
            }
            else if (cardPriceCounter >= 2 && this->possedeCarte("Argent (3💰)"))
            {
                this->supprimeCarteMain("Argent (3💰)");
                cardPriceCounter -= 2;
            }
            else
            {
                this->supprimeCarteMain("Cuivre (0💰)");
                cardPriceCounter -= 1;
            }
        }
        std::cout << "Vous venez d'acheter la carte " << carte->getName() << std::endl;
        std::cout << "Elle est désormais dans votre defausse\n"
                  << std::endl;
        return true;
    }
    else if (this->money + additionalMoney < carte->getPrice())
    {
        std::cout << "Vous n'avez pas assez d'argent (💰) \n"
                  << std::endl;
        return false;
    }
    else
        std::cout << "Vous n'avez plus de point d'achat (🪙 ) \n"
                  << std::endl;
    return false;
}

void Joueur::ajouteCarteMain(Carte *carte)
{
    hand.push_back(carte);
}

void Joueur::ajouteCartePioche(Carte *carte)
{
    pioche.push_back(carte);
}

void Joueur::HandToDefausse()
{
    for (const auto &carte : this->hand)
    {
        this->defausse.push_back(carte);
    }
    this->hand.clear();
    this->money = 0;
}

void Joueur::defausseToPioche()
{
    if (pioche.size() == 0)
    {
        this->pioche = this->defausse;
        defausse.clear();
    }
    else
    {
        for (const auto &carte : pioche)
        {
            defausse.push_back(carte);
        }
        pioche.clear();
        pioche = this->defausse;
        defausse.clear();
    }
}

void Joueur::ajouteCarteDefausse(Carte *carte)
{
    defausse.push_back(carte);
}

void Joueur::afficheCartes()
{
    for (const auto &carte : hand)
    {
        std::cout << carte->getName() << " | ";
    }
    std::cout << "\n"
              << std::endl;
}

void Joueur::afficheDefausse()
{
    std::cout << "🧾 La défausse contient les cartes suivantes : " << std::endl;
    for (const auto &carte : defausse)
    {
        std::cout << carte->getName() << "| ";
    }
    std::cout << std::endl;
}

void Joueur::affichePioche()
{
    std::cout << "🧾 La pioche contient les cartes suivantes : " << std::endl;
    for (const auto &carte : pioche)
    {
        std::cout << carte->getName() << "| ";
    }
    std::cout << std::endl;
}

void Joueur::piocheCarte()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, pioche.size() - 1);
    int indice = dis(gen);
    std::cout << "🖲️  Vous avez pioché : " << pioche[indice]->getName() << std::endl;
    hand.push_back(pioche[indice]);
    if (pioche[indice]->getName() == "Cuivre (0💰)")
    {
        this->money += 1;
    }
    else if (pioche[indice]->getName() == "Argent (3💰)")
    {
        this->money += 2;
    }
    else if (pioche[indice]->getName() == "Or (6💰)")
    {
        this->money += 3;
    }
    // pioche.erase(pioche.begin() + indice);
    this->supprimeCartePioche(pioche[indice]->getName());
}
