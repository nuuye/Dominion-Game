#ifndef __CarteRoyaume_hpp
#define __CarteRoyaume_hpp
#include <iostream>
#include "Carte.hpp"

/**
 * @brief classe qui hérite de carte.
 * Les cartes royaumes sont des cartes qui permettent d'effectuer une action lors de leur mise en jeu.
 * 
 */
class CarteRoyaume : public Carte
{
private:
public:
    void affiche() override { std::cout << ""; };
    CarteRoyaume(string name, int price);
    virtual ~CarteRoyaume(){};
    //string getName() const override { return name; };
    // int getPrice() override { return price; };
    //  surcharge de l'opérateur << pour pouvoir afficher
    //  friend std::ostream &operator<<(std::ostream &os, const CarteRoyaume *cr)
    //  {
    //      os << cr->name << std::endl;
    //      return os;
    //  }
};

#endif