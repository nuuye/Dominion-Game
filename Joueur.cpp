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
 * Permet de créer un joueur en initialisant les attributs actions, isMyTurn et buyPoints automatiquement.
 * @param name nom du joueur à créer
 */
Joueur::Joueur(string name)
{
    this->name = name;
    this->actions = 1;
    this->isMyTurn = false;
    this->buyPoints = 1;
}

/**
 * @brief Setter - set le nombre d'achat par tour
 *
 * @param buyPoints
 */
void Joueur::setBuyPoints(int buyPoints)
{
    this->buyPoints = buyPoints;
}

/**
 * @brief Setter - set le nombre d'action par tour
 *
 * @param actions
 */
void Joueur::setActions(int actions)
{
    this->actions = actions;
}
/**
 * @brief Setter - set le nombre d'argent du joueur
 *
 * @param money
 */
void Joueur::setMoney(int money)
{
    this->money = money;
}

/**
 * @brief Setter - permet de set le tour du jeu du joueur
 *
 * @param isMyTurn
 */
void Joueur::setMyTurn(bool isMyTurn)
{
    this->isMyTurn = isMyTurn;
}

/**
 * @brief getter - Permer de récupérer le nombre de points d'achats d'un joueur
 *
 * @return int
 */
int Joueur::getBuyPoints()
{
    return buyPoints;
}

/**
 * @brief getter - permet de récupérer la main d'un joueur
 *
 * @return vector<Carte *>
 */
vector<Carte *> Joueur::getHand()
{
    return hand;
}

vector<CarteTresor *> Joueur::getHandTresor()
{
    vector<CarteTresor *> tresorList;
    for (const auto &carte : hand)
    {
        if (carte->getName() == "Cuivre (0💰)" || carte->getName() == "Argent (3💰)" || carte->getName() == "Or (6💰)")
        {
            tresorList.push_back(static_cast<CarteTresor *>(carte));
        }
    }
    return tresorList;
}

/**
 * @brief getter - permet de récupérer la défausse d'un joueur
 *
 * @return vector<Carte *>
 */
vector<Carte *> Joueur::getDefausse()
{
    return defausse;
}

/**
 * @brief getter - permet de récupérér le nombre d'action d'un joueur
 *
 * @return int
 */
int Joueur::getActions()
{
    return this->actions;
}

/**
 * @brief getter - permet de récupérer l'argent d'un joueur
 *
 * @return int
 */
int Joueur::getMoney()
{
    return this->money;
}

/**
 * @brief permet de savoir si cette instance de joueur à le droit de jouer. Détermine le tour du joueur
 *
 * @return true
 * @return false
 */
bool Joueur::getTurn()
{
    return this->isMyTurn;
}

/**
 * @brief getter - permet de récupérer la taille de la pioche
 *
 * @return int
 */
int Joueur::getPiocheSize()
{
    return this->pioche.size();
}

/**
 * @brief getter - permet de récupérer la taille de la main
 *
 * @return int
 */
int Joueur::getHandSize()
{
    return this->hand.size();
}

/**
 * @brief getter - permet de récupérere la taille de la défausse
 *
 * @return int
 */
int Joueur::getDefausseSize()
{
    return this->defausse.size();
}

/**
 * @brief getter - permet de récupérer le nombre total de points de victoire contenu dans la pioche
 * La fonction est utilisé en fin de partie lorsque le joueur met toute ses cartes dans sa pioche pour faire le compte
 *
 * @return int
 */
int Joueur::getVictoryPointsAmount()
{
    int count = 0;
    for (int i = 0; i < this->getPiocheSize(); i++)
    {
        count += pioche[i]->getPoints();
    }
    return count;
}

/**
 * @brief fonction qui permet de vérifier si un joueur possède une carte donnée
 *
 * @param cardName
 * @return true
 * @return false
 */
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

/**
 * @brief fonction qui permet de supprimer une carte de la main, la carte est placée dans la défausse
 *
 * @param cardToDelete
 */
void Joueur::supprimeCarteMain(string cardToDelete, bool deleteCompletly)
{
    auto it = std::find_if(this->hand.begin(), this->hand.end(), [cardToDelete](const auto &carte)
                           { return dynamic_cast<Carte *>(carte) != nullptr && carte->getName() == cardToDelete; });
    if (it != this->hand.end())
    {
        if (!deleteCompletly)
        {
            this->ajouteCarteDefausse(*it);
        }
        this->hand.erase(it);
    }
}

/**
 * @brief fonction qui permet de supprimer une carte de la pioche
 *
 * @param cardToDelete
 */
void Joueur::supprimeCartePioche(string cardToDelete)
{
    auto it = std::find_if(this->pioche.begin(), this->pioche.end(), [cardToDelete](const auto &carte)
                           { return dynamic_cast<Carte *>(carte) != nullptr && carte->getName() == cardToDelete; });
    if (it != this->pioche.end())
    {
        this->pioche.erase(it);
    }
}

/**
 * @brief fonction qui permet d'acheter une carte, cette dernière est ensuite placée automatiquement dans la défausse.
 * Le nombre d'achat durant le tour est décrémenté et l'argent du joueur également.
 *
 * @param carte
 * @return true
 * @return false
 */
bool Joueur::acheteCarte(Carte *carte)
{
    if (this->money >= carte->getPrice() && this->buyPoints >= 1)
    {
        this->defausse.push_back(carte);
        this->buyPoints -= 1;
        this->money -= carte->getPrice();
        int cardPriceCounter = carte->getPrice();
        while (cardPriceCounter != 0)
        {
            if (cardPriceCounter >= 3 && this->possedeCarte("Or (6💰)"))
            {
                this->supprimeCarteMain("Or (6💰)", false);
                cardPriceCounter -= 3;
            }
            else if (cardPriceCounter >= 2 && this->possedeCarte("Argent (3💰)"), false)
            {
                this->supprimeCarteMain("Argent (3💰)", false);
                cardPriceCounter -= 2;
            }
            else
            {
                this->supprimeCarteMain("Cuivre (0💰)", false);
                cardPriceCounter -= 1;
            }
        }
        std::cout << "Vous venez d'acheter la carte " << carte->getName() << std::endl;
        std::cout << "Elle est désormais dans votre defausse\n"
                  << std::endl;
        return true;
    }
    else if (this->money < carte->getPrice())
    {
        std::cout << "❌ Vous n'avez pas assez d'argent (💰) \n"
                  << std::endl;
        return false;
    }
    else
        std::cout << "❌ Vous n'avez plus de point d'achat (🪙 ) \n"
                  << std::endl;
    return false;
}

/**
 * @brief fonction qui permet d'ajouter une carte dans la main du joueur
 *
 * @param carte
 */
void Joueur::ajouteCarteMain(Carte *carte)
{
    hand.push_back(carte);
}

/**
 * @brief fonction qui permet d'ajouter une carte dans la pioche
 *
 * @param carte
 */
void Joueur::ajouteCartePioche(Carte *carte)
{
    pioche.push_back(carte);
}

/**
 * @brief fonction qui permet de transférer les cartes de la main vers la défausse
 *
 */
void Joueur::HandToDefausse()
{
    for (const auto &carte : this->hand)
    {
        this->defausse.push_back(carte);
    }
    this->hand.clear();
    this->money = 0;
}

/**
 * @brief fonction qui permet de transferer les cartes de la défausse vers la pioche
 *
 */
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

/**
 * @brief fonction qui permet d'ajouter une carte dans la défausse
 *
 * @param carte
 */
void Joueur::ajouteCarteDefausse(Carte *carte)
{
    defausse.push_back(carte);
}

/**
 * @brief fonction qui permet d'afficher les cartes du joueur
 *
 */
void Joueur::afficheCartes()
{
    for (const auto &carte : hand)
    {
        std::cout << carte->getName() << " | ";
    }
    std::cout << "\n"
              << std::endl;
}

/**
 * @brief fonction qui permet d'afficher les cartes de la défausse du joueur
 *
 */
void Joueur::afficheDefausse()
{
    std::cout << "🧾 La défausse contient les cartes suivantes : " << std::endl;
    for (const auto &carte : defausse)
    {
        std::cout << carte->getName() << "| ";
    }
    std::cout << std::endl;
}

/**
 * @brief fonction qui permet d'afficher les cartes de la pioche du joueur
 *
 */
void Joueur::affichePioche()
{
    std::cout << "🧾 La pioche contient les cartes suivantes : " << std::endl;
    for (const auto &carte : pioche)
    {
        std::cout << carte->getName() << "| ";
    }
    std::cout << std::endl;
}

/**
 * @brief fonction qui permet de piocher une carte de facon aléatoire
 *
 */
void Joueur::piocheCarte()
{
    if (this->pioche.size() == 0)
    {
        this->defausseToPioche();
    }
    if (this->pioche.size() == 0)
    {
        std::cout << "❌ Vous n'avez plus de carte dans la pioche ni dans la défausse" << std::endl;
    }
    else
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
        this->supprimeCartePioche(pioche[indice]->getName());
    }
}
/**
 * @brief fonction qui vérifie si le joueur possède une carte trésor dans sa main
 *
 * @return true
 * @return false
 */
bool Joueur::hasTresorCard(vector<Carte *>)
{
    bool hasTresorCard = false;
    for (const auto &carte : hand)
    {
        if (carte->getName() == "Cuivre (0💰)" || carte->getName() == "Argent (3💰)" || carte->getName() == "Or (6💰)")
        {
            hasTresorCard = true;
        }
    }
    return hasTresorCard;
}
