#ifndef __Joueur_hpp
#define __Joueur_hpp
#include <iostream>
#include "Carte.hpp"
#include "CarteTresor.hpp"
#include <string>
#include <vector>
using namespace std;

/**
 * @brief La classe Joueur représente un joueur dans la partie
 * Ce dernier possède plusieurs pile de carte comme sa pioche, main ou sa défausse
 *
 */
class Joueur
{
private:
	string name;
	int actions;
	int buyPoints;
	int money;
	bool isMyTurn;
	vector<Carte *> pioche;
	vector<Carte *> hand;
	vector<Carte *> defausse;

public:
	Joueur(string name);
	~Joueur(){delete this};
	void setBuyPoints(int buyPoints);
	void setActions(int actions);
	void setMoney(int money);
	void setMyTurn(bool isMyTurn);

	int getBuyPoints();
	int getActions();
	int getMoney();
	bool getTurn();
	int getPiocheSize();
	int getHandSize();
	int getDefausseSize();
	vector<Carte *> getHand();
	vector<CarteTresor *> getHandTresor();
	vector<Carte *> getDefausse();
	int getVictoryPointsAmount();

	void supprimeCarteMain(string CardToDelete);
	void supprimeCarteJeu(string CardToDeleteInHand);
	void supprimeCartePioche(string cardToDelete);
	void defausseToPioche();
	void HandToDefausse();
	void ajouteCarteMain(Carte *carte);
	void ajouteCartePioche(Carte *carte);
	void ajouteCarteDefausse(Carte *carte);
	bool acheteCarte(Carte *carte);
	void afficheCartes();
	void afficheDefausse();
	void affichePioche();
	void piocheCarte();
	bool possedeCarte(string cardName);
	bool hasTresorCard(vector<Carte *>); // a rajouter UML
};

#endif