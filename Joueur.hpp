#ifndef __Joueur_hpp
#define __Joueur_hpp
#include <iostream>
#include "Carte.hpp"
#include <string>
#include <vector>
using namespace std;

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
	bool acheteCarte(Carte *carte, int additionalMoney);
	void afficheCartes();
	void afficheDefausse();
	void affichePioche();
	void piocheCarte();
	bool possedeCarte(string cardName);
};

#endif