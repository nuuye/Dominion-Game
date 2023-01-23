#include <iostream>
#include "Carte.hpp"
#include "CarteRoyaume.hpp"
#include "CarteVictoire.hpp"
#include "CarteTresor.hpp"
#include "Plateau.hpp"
#include "Joueur.hpp"
#include <random>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <typeinfo>

/**
 * @brief fonction qui permet de demander au joueur quelle action effectuer
 *
 * @param joueur
 */
void choice(Joueur *joueur)
{
        std::cout << "➡️ Que voulez vous faire ? (" << joueur->getBuyPoints() << "🪙 |" << joueur->getActions() << "💠|" << joueur->getMoney() << "💰)" << std::endl;
        std::cout << "💠 - Jouer une carte action : 1 | 🪙  - Faire un achat : 2 | 📜 - Ajustement, Fin de tour : 3" << std::endl;
}
int main()
{
        static int nombreTour = 1;
        CarteRoyaume *cave = new CarteRoyaume("Cave (2💰)", 2);
        CarteRoyaume *renovation = new CarteRoyaume("Rénovation (4💰)", 4);
        CarteRoyaume *sorciere = new CarteRoyaume("Sorcière (5💰)", 5);
        CarteRoyaume *marche = new CarteRoyaume("Marché (5💰)", 5);
        CarteRoyaume *forgeron = new CarteRoyaume("Forgeron (4💰)", 4);
        CarteRoyaume *bucheron = new CarteRoyaume("Bûcheron (3💰)", 3);
        CarteRoyaume *mine = new CarteRoyaume("Mine (5💰)", 1);
        CarteRoyaume *village = new CarteRoyaume("Village (3💰)", 3);
        CarteRoyaume *chapelle = new CarteRoyaume("Chapelle (2💰)", 2);
        CarteRoyaume *atelier = new CarteRoyaume("Atelier (3💰)", 3);

        CarteVictoire *domaine = new CarteVictoire("Domaine (2💰)", 1, 2);
        CarteVictoire *duche = new CarteVictoire("Duché (5💰)", 3, 5);
        CarteVictoire *province = new CarteVictoire("Province (8💰)", 6, 8);
        CarteVictoire *malediction = new CarteVictoire("Malédiction (0💰)", -1, 0);

        CarteTresor *cuivre = new CarteTresor("Cuivre (0💰)", 1, 0);
        CarteTresor *argent = new CarteTresor("Argent (3💰)", 2, 3);
        CarteTresor *gold = new CarteTresor("Or (6💰)", 3, 6);

        Joueur *joueur_1 = new Joueur("Joueur 1");
        Joueur *joueur_2 = new Joueur("Joueur 2");

        Plateau *plateau = new Plateau();
        plateau->reserve[cave] = 1;
        plateau->reserve[renovation] = 5;
        plateau->reserve[sorciere] = 5;
        plateau->reserve[marche] = 5;
        plateau->reserve[forgeron] = 5;
        plateau->reserve[bucheron] = 1;
        plateau->reserve[mine] = 5;
        plateau->reserve[village] = 5;
        plateau->reserve[chapelle] = 1;
        plateau->reserve[atelier] = 5;

        plateau->reserve[domaine] = 8;
        plateau->reserve[duche] = 8;
        plateau->reserve[province] = 8;

        plateau->reserve[malediction] = 10;

        plateau->reserve[cuivre] = 10;
        plateau->reserve[argent] = 10;
        plateau->reserve[gold] = 10;

        joueur_1->ajouteCartePioche(cuivre);
        joueur_1->ajouteCartePioche(cuivre);
        joueur_1->ajouteCartePioche(cuivre);
        joueur_1->ajouteCartePioche(cuivre);
        joueur_1->ajouteCartePioche(cuivre);
        joueur_1->ajouteCartePioche(cuivre);
        joueur_1->ajouteCartePioche(cuivre);
        joueur_1->ajouteCartePioche(domaine);
        joueur_1->ajouteCartePioche(domaine);
        joueur_1->ajouteCartePioche(domaine);

        joueur_2->ajouteCartePioche(cuivre);
        joueur_2->ajouteCartePioche(cuivre);
        joueur_2->ajouteCartePioche(cuivre);
        joueur_2->ajouteCartePioche(cuivre);
        joueur_2->ajouteCartePioche(cuivre);
        joueur_2->ajouteCartePioche(cuivre);
        joueur_2->ajouteCartePioche(cuivre);
        joueur_2->ajouteCartePioche(domaine);
        joueur_2->ajouteCartePioche(domaine);
        joueur_2->ajouteCartePioche(domaine);

        int count = 0;
        // On génère un nombre aléatoire pour savoir qui commence
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 2);
        static int joueurQuiCommence = dis(gen);

        if (joueurQuiCommence == 1)
        {
                joueur_1->setMyTurn(true);
        }
        else
        {
                joueur_2->setMyTurn(true);
        }
        // on stock le tour dans une variable pour éviter les répétitions
        static bool joueur_1_Turn = joueur_1->getTurn();
        static bool joueur_2_Turn = joueur_2->getTurn();

        static string choix_J1;
        static string choix_J2;

        // boucle de jeu
        while (count < 3 && plateau->reserve[province] > 0)
        {
                // condition d'arrêt
                for (const auto &keyValue : plateau->reserve)
                {
                        if (keyValue.second == 0)
                        {
                                count += 1;
                                std::cout << "COUNT : " << count << std::endl;
                        }
                }
                // début de la partie
                if (nombreTour == 1)
                {
                        std::cout << "                                                🕯️  La partie commence 🕯️ " << std::endl;
                        std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
                        plateau->affichePlateau();

                        std::cout << "Un nombre aléatoire est généré pour connaître le joueur qui commence :" << std::endl;
                        std::cout << "Le nombre généré est : " << joueurQuiCommence << std::endl;
                        if (joueur_1_Turn)
                        {
                                std::cout << "Le joueur 1 commence la partie"
                                          << "\n"
                                          << std::endl;
                        }
                        else
                        {
                                std::cout << "Le joueur 2 commence la partie"
                                          << "\n"
                                          << std::endl;
                        }
                }

                // Pioche 5 cartes aléatoire
                if (joueur_1_Turn)
                {
                        for (int i = 0; i < 5; i++)
                        {
                                joueur_1->piocheCarte();
                        }
                        std::cout << "➡️ (J1 🤴 ) Vous avez : " << std::endl;
                        joueur_1->afficheCartes();
                        joueur_1->afficheDefausse();
                        joueur_1->affichePioche();
                        choice(joueur_1);
                        std::cin >> choix_J1;
                        do
                        {
                                if (choix_J1 == "1")
                                {
                                        if (joueur_1->getActions() >= 1)
                                        {
                                                std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                joueur_1->afficheCartes();
                                                string cardToPlay;
                                                std::cout << "➡️ Quelle carte action voulez vous jouer ?" << std::endl;
                                                std::cin >> cardToPlay;
                                                std::transform(cardToPlay.begin(), cardToPlay.end(), cardToPlay.begin(), ::tolower);

                                                if (cardToPlay == cave->getLowerCuttedName() && joueur_1->possedeCarte(cave->getName()))
                                                {
                                                        // +1 Action et défausse autant de cartes / +1pioche par defausse
                                                        std::cout << "➡️ Vous gagnez +1 Action et vous pouvez défausser autant de carte que vous voulez. Piochez une carte par carte défaussée" << std::endl;
                                                        int numberToThrow = 0;
                                                        int i = 0;
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_1->supprimeCarteMain(cave->getName(), false);
                                                        joueur_1->afficheCartes();
                                                        std::cout << "➡️ Combien de cartes voulez vous défausser? " << std::endl;
                                                        std::cin >> numberToThrow;
                                                        while (numberToThrow > joueur_1->getHandSize())
                                                        {
                                                                std::cout << "Vous ne possedez pas assez de cartes, veuillez rentrez un nouveau nombre" << std::endl;
                                                                std::cin >> numberToThrow;
                                                        }
                                                        while (i < numberToThrow)
                                                        {
                                                                string cardToMove;
                                                                bool cardFound = false;
                                                                std::cout << "➡️ Quel est le nom de la carte que vous voulez défausser ?" << std::endl;
                                                                std::cin >> cardToMove;
                                                                cardToMove[0] = tolower(cardToMove[0]);
                                                                for (const auto &carte : joueur_1->getHand())
                                                                {
                                                                        if (cardToMove == carte->getLowerCuttedName())
                                                                        {

                                                                                cardToMove = cardToMove + " (" + to_string(carte->getPrice()) + "💰)";
                                                                                cardToMove[0] = toupper(cardToMove[0]);
                                                                                joueur_1->supprimeCarteMain(cardToMove, false);
                                                                                cardFound = true;
                                                                        }
                                                                }
                                                                if (!cardFound)
                                                                {
                                                                        std::cout << "❌ La carte n'est pas dans votre main ou est mal orthographiée. Veuillez réessayer" << std::endl;
                                                                        i -= 1;
                                                                }
                                                                else
                                                                {
                                                                        std::cout << "➡️ La carte " << cardToMove << " a été mise dans la défausse et n'est plus dans votre main \n"
                                                                                  << std::endl;
                                                                }
                                                                i += 1;
                                                        }
                                                        for (int j = 0; j < numberToThrow; j++)
                                                        {
                                                                joueur_1->piocheCarte();
                                                        }

                                                        std::cout << "➡️ Vous avez pioché " << numberToThrow << " carte(s)\n"
                                                                  << std::endl;

                                                        std::cout << "➡️ Vous possédez désormais les cartes : " << std::endl;
                                                        joueur_1->afficheCartes();
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                                else if (cardToPlay == renovation->getLowerCuttedName() && joueur_1->possedeCarte(renovation->getName()))
                                                {
                                                        if (joueur_1->getHandSize() >= 1)
                                                        {
                                                                joueur_1->supprimeCarteMain(renovation->getName(), false);
                                                                int numberToDelete = 1;
                                                                int i = 0;
                                                                // écarte une carte de la main, reçoit une carte jusqu'à +2 que la carte écartée
                                                                std::cout << "➡️ Ecartez une carte de votre main et recevez une carte coûtant jusqu'à +2💰 que le coût de votre carte" << std::endl;
                                                                std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                                joueur_1->afficheCartes();
                                                                int cardPrice = 0;
                                                                while (i < numberToDelete)
                                                                {
                                                                        string cardToDelete;
                                                                        bool cardFound = false;
                                                                        std::cout << "➡️ Quel est le nom de la carte que vous voulez écarter ?" << std::endl;
                                                                        std::cin >> cardToDelete;
                                                                        cardToDelete[0] = tolower(cardToDelete[0]);

                                                                        for (const auto &carte : joueur_1->getHand())
                                                                        {
                                                                                if (cardToDelete == carte->getLowerCuttedName())
                                                                                {
                                                                                        plateau->rebus.push_back(carte);
                                                                                        cardToDelete = cardToDelete + " (" + to_string(carte->getPrice()) + "💰)";
                                                                                        cardToDelete[0] = toupper(cardToDelete[0]);
                                                                                        joueur_1->supprimeCarteMain(cardToDelete, true);
                                                                                        cardFound = true;
                                                                                        cardPrice += carte->getPrice();
                                                                                }
                                                                        }
                                                                        if (!cardFound)
                                                                        {
                                                                                std::cout << "❌ La carte n'est pas dans votre main ou est mal orthographiée. Veuillez réessayer" << std::endl;
                                                                                i -= 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                std::cout << "➡️ La carte " << cardToDelete << " a été mise dans le rebus et n'est plus dans votre main \n"
                                                                                          << std::endl;
                                                                        }
                                                                        i += 1;
                                                                }

                                                                plateau->affichePlateau();

                                                                int numberToGet = 1;
                                                                int j = 0;
                                                                while (j < numberToGet)
                                                                {
                                                                        string cardToGet;
                                                                        bool cardFound = false;
                                                                        std::cout << "➡️ Quelle carte voulez vous acquérir ? (0 à " << cardPrice + 2 << "💰)" << std::endl;
                                                                        std::cin >> cardToGet;
                                                                        cardToGet[0] = tolower(cardToGet[0]);
                                                                        for (const auto &carte : plateau->reserve)
                                                                        {
                                                                                if (cardToGet == carte.first->getLowerCuttedName() && carte.first->getPrice() <= cardPrice + 2)
                                                                                {

                                                                                        joueur_1->ajouteCarteDefausse(carte.first);
                                                                                        plateau->removeCard(carte.first);
                                                                                        cardFound = true;
                                                                                }
                                                                        }
                                                                        if (!cardFound)
                                                                        {
                                                                                std::cout << "❌ La carte n'est pas dans la reserve, est mal orthographiée ou coûte trop cher. Veuillez réessayer" << std::endl;
                                                                                j -= 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                std::cout << "➡️ La carte " << cardToGet << " a été mise dans votre défausse" << std::endl;
                                                                        }
                                                                        j += 1;
                                                                }
                                                                joueur_1->setActions(joueur_1->getActions() - 1);
                                                                choice(joueur_1);
                                                                std::cin >> choix_J1;
                                                        }
                                                        else
                                                        {
                                                                std::cout << "❌ Vous n'avez plus de carte pour pouvoir jouer la carte rénovation \n"
                                                                          << std::endl;
                                                                choice(joueur_1);
                                                                std::cin >> choix_J1;
                                                        }
                                                }
                                                else if (cardToPlay == sorciere->getLowerCuttedName() && joueur_1->possedeCarte(sorciere->getName()))
                                                {
                                                        // Ajoute une carte malédiction dans la défausse de l'adversaire
                                                        joueur_1->supprimeCarteMain(sorciere->getName(), false);
                                                        if (plateau->reserve[malediction] > 0)
                                                        {
                                                                plateau->reserve[malediction]--;
                                                                // ajoute la carte malédiction dans la défausse de l'ennemi
                                                                joueur_2->ajouteCarteDefausse(malediction);
                                                                std::cout << "➡️ Une carte malédiction a été placé dans la défausse de votre/vos adversaire(s)" << std::endl;
                                                        }
                                                        else
                                                        {
                                                                std::cout << "➡️ Il n'y a plus de carte malédiction dans la réserve, vous piochez 2 cartes" << std::endl;
                                                                joueur_1->piocheCarte();
                                                                joueur_1->piocheCarte();
                                                        }
                                                        joueur_1->setActions(joueur_1->getActions() - 1);
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                                else if (cardToPlay == marche->getLowerCuttedName() && joueur_1->possedeCarte(marche->getName()))
                                                {
                                                        // Octroie 1 point d'action, 1 carte, 1 pièce de cuivre et 1 achat
                                                        joueur_1->supprimeCarteMain(marche->getName(), false);

                                                        joueur_1->setBuyPoints(joueur_1->getBuyPoints() + 1);
                                                        joueur_1->piocheCarte();
                                                        joueur_1->setMoney(joueur_1->getMoney() + 1);
                                                        std::cout << "➡️ Vous gagnez +1 Carte, +1💠 Action, +1💰 Pièce et +1🪙  Achat" << std::endl;
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_1->afficheCartes();
                                                        std::cout << "Vous avez : " << joueur_1->getMoney() << "💰 |" << joueur_1->getBuyPoints() << "🪙 |" << joueur_1->getActions() << "💠" << std::endl;
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                                else if (cardToPlay == forgeron->getLowerCuttedName() && joueur_1->possedeCarte(forgeron->getName()))
                                                {
                                                        // Pioche 3 cartes
                                                        joueur_1->supprimeCarteMain(forgeron->getName(), false);

                                                        if (joueur_1->getPiocheSize() < 3)
                                                        {
                                                                joueur_1->defausseToPioche();
                                                        }

                                                        for (int i; i <= 2; i++)
                                                        {
                                                                joueur_1->piocheCarte();
                                                        }

                                                        joueur_1->setActions(joueur_1->getActions() - 1);
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_1->afficheCartes();
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                                else if (cardToPlay == bucheron->getLowerCuttedName() && joueur_1->possedeCarte(bucheron->getName()))
                                                {
                                                        // +1 Achat et 2 pièces pour le tour
                                                        joueur_1->supprimeCarteMain(bucheron->getName(), false);

                                                        joueur_1->setBuyPoints(joueur_1->getBuyPoints() + 1);
                                                        joueur_1->setMoney(joueur_1->getMoney() + 2);
                                                        joueur_1->setActions(joueur_1->getActions() - 1);
                                                        std::cout << "➡️ Vous gagnez +1 Achat et 2 pièces \n"
                                                                  << std::endl;
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_1->afficheCartes();
                                                        std::cout << "Vous avez : " << joueur_1->getMoney() << "💰 |" << joueur_1->getBuyPoints() << "🪙 |" << joueur_1->getActions() << "💠" << std::endl;
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                                else if (cardToPlay == mine->getLowerCuttedName() && joueur_1->possedeCarte(mine->getName()))
                                                {
                                                        if (joueur_1->hasTresorCard(joueur_1->getHand()))
                                                        {
                                                                // écarte une carte trésor de la main, reçoit une carte trésor valant jusqu'à +3. Ajoute cette carte à notre main
                                                                joueur_1->supprimeCarteMain(mine->getName(), false);
                                                                int numberToDelete = 1;
                                                                int i = 0;
                                                                int cardPrice = 0;
                                                                std::cout << "➡️ Ecartez une carte trésor de votre main pour en recevoir une coûtant 3💰 de plus" << std::endl;
                                                                std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                                joueur_1->afficheCartes();
                                                                while (i < numberToDelete)
                                                                {
                                                                        string cardToDelete;
                                                                        bool cardFound = false;
                                                                        std::cout << "➡️ Quel est le nom de la carte trésor que vous voulez écarter ?" << std::endl;
                                                                        std::cin >> cardToDelete;
                                                                        cardToDelete[0] = tolower(cardToDelete[0]);
                                                                        int handValue = joueur_1->getMoney();
                                                                        for (const auto &carte : joueur_1->getHand())
                                                                        {
                                                                                if (cardToDelete == carte->getLowerCuttedName() && (carte->getName() == "Cuivre (0💰)" || carte->getName() == "Argent (3💰)" || carte->getName() == "Or (6💰)"))
                                                                                {
                                                                                        // on utilise le static cast pour pouvoir utiliser la méthode getValeur de carteTresor, on a vérifié auparavant qu'il s'agissait bien d'une carte trésor.
                                                                                        handValue -= static_cast<CarteTresor *>(carte)->getValeur();
                                                                                        plateau->rebus.push_back(carte);
                                                                                        cardPrice = carte->getPrice();
                                                                                        cardToDelete = cardToDelete + " (" + to_string(carte->getPrice()) + "💰)";
                                                                                        cardToDelete[0] = toupper(cardToDelete[0]);
                                                                                        joueur_1->supprimeCarteMain(cardToDelete, true);
                                                                                        cardFound = true;
                                                                                }
                                                                        }
                                                                        if (!cardFound)
                                                                        {
                                                                                std::cout << "❌ La carte n'est pas dans votre main ou est mal orthographiée ou n'est pas une carte trésor. Veuillez réessayer" << std::endl;
                                                                                i -= 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                std::cout << "➡️ La carte " << cardToDelete << " a été mise dans le rebus et n'est plus dans votre main \n"
                                                                                          << std::endl;
                                                                                joueur_2->setMoney(handValue);
                                                                                std::cout << "Vous avez : " << joueur_1->getMoney() << "💰 |" << joueur_1->getBuyPoints() << "🪙 |" << joueur_1->getActions() << "💠" << std::endl;
                                                                        }
                                                                        i += 1;
                                                                }
                                                                std::cout << "➡️ Vous pouvez désormais acquérir une carte trésor valant jusqu'à : " << cardPrice + 3 << "💰" << std::endl;
                                                                plateau->affichePlateau();
                                                                int finalCardPrice = cardPrice + 3;
                                                                int it = 1;
                                                                int j = 0;
                                                                while (j < it)
                                                                {
                                                                        string cardToGet;
                                                                        bool cardFound = false;
                                                                        std::cout << "➡️ Quelle carte voulez vous acquérir ? ( jusqu'à " << finalCardPrice << "💰)" << std::endl;
                                                                        std::cin >> cardToGet;

                                                                        for (const auto &carte : plateau->reserve)
                                                                        {
                                                                                if (cardToGet == carte.first->getLowerCuttedName() && carte.first->getPrice() <= finalCardPrice && (carte.first->getName() == "Cuivre (0💰)" || carte.first->getName() == "Argent (3💰)" || carte.first->getName() == "Or (6💰)"))
                                                                                {

                                                                                        joueur_1->ajouteCarteMain(carte.first);
                                                                                        // on utilise le static cast pour pouvoir utiliser la méthode getValeur de carteTresor, on a vérifié auparavant qu'il s'agissait bien d'une carte trésor.
                                                                                        joueur_1->setMoney(joueur_1->getMoney() + static_cast<CarteTresor *>(carte.first)->getValeur());
                                                                                        plateau->removeCard(carte.first);
                                                                                        cardFound = true;
                                                                                }
                                                                        }
                                                                        if (!cardFound)
                                                                        {
                                                                                std::cout << "❌ La carte n'est pas dans la reserve, est mal orthographiée, est trop coûteuse ou n'est pas une carte trésor. Veuillez réessayer" << std::endl;
                                                                                j -= 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                std::cout << "➡️ La carte " << cardToGet << " a été mise dans votre main" << std::endl;
                                                                        }
                                                                        j += 1;
                                                                }
                                                                joueur_1->setActions(joueur_1->getActions() - 1);
                                                                std::cout << "Vous avez : " << joueur_1->getMoney() << "💰 |" << joueur_1->getBuyPoints() << "🪙 |" << joueur_1->getActions() << "💠" << std::endl;
                                                                choice(joueur_1);
                                                                std::cin >> choix_J1;
                                                        }

                                                        else
                                                        {
                                                                std::cout << "Vous n'avez pas de carte trésor pour jouer la carte mine. \n"
                                                                          << std::endl;
                                                                std::cout << "Vous avez : " << joueur_1->getMoney() << "💰 |" << joueur_1->getBuyPoints() << "🪙 |" << joueur_1->getActions() << "💠" << std::endl;
                                                                choice(joueur_1);
                                                                std::cin >> choix_J1;
                                                        }
                                                }
                                                else if (cardToPlay == village->getLowerCuttedName() && joueur_1->possedeCarte(village->getName()))
                                                {
                                                        // Octroie 2 points d'action et 1 carte
                                                        joueur_1->supprimeCarteMain(village->getName(), false);

                                                        joueur_1->setActions(joueur_1->getActions() + 1);
                                                        std::cout << "➡️ Vous gagnez +1 Carte et +2💠 Actions" << std::endl;
                                                        joueur_1->piocheCarte();
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_1->afficheCartes();
                                                        std::cout << "Vous avez : " << joueur_1->getMoney() << "💰 |" << joueur_1->getBuyPoints() << "🪙 |" << joueur_1->getActions() << "💠" << std::endl;
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                                else if (cardToPlay == chapelle->getLowerCuttedName() && joueur_1->possedeCarte(chapelle->getName()))
                                                {
                                                        // Place jusqu'à 4 cartes dans le rebus
                                                        joueur_1->supprimeCarteMain(chapelle->getName(), false);

                                                        int numberToDelete;
                                                        int i = 0;
                                                        std::cout << "➡️ Vous pouvez écarter jusqu'à 4 cartes de votre main" << std::endl;
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_1->afficheCartes();
                                                        std::cout << "➡️ Combien de carte voulez vous écarter ? ";
                                                        std::cin >> numberToDelete;
                                                        while (numberToDelete > 4 && numberToDelete > joueur_1->getHandSize())
                                                        {
                                                                std::cout << "❌ Vous ne pouvez pas écarter plus de 4 cartes ou vous n'avez pas assez de cartes" << std::endl;
                                                                std::cin >> numberToDelete;
                                                        }
                                                        while (i < numberToDelete)
                                                        {
                                                                string cardToDelete;
                                                                bool cardFound = false;
                                                                std::cout << "➡️ Quel est le nom de la carte que vous voulez écarter ?" << std::endl;
                                                                std::cin >> cardToDelete;
                                                                cardToDelete[0] = tolower(cardToDelete[0]);

                                                                for (const auto &carte : joueur_1->getHand())
                                                                {
                                                                        if (cardToDelete == carte->getLowerCuttedName())
                                                                        {
                                                                                plateau->rebus.push_back(carte);
                                                                                cardToDelete = cardToDelete + " (" + to_string(carte->getPrice()) + "💰)";
                                                                                cardToDelete[0] = toupper(cardToDelete[0]);
                                                                                joueur_1->supprimeCarteMain(cardToDelete, true);
                                                                                cardFound = true;
                                                                        }
                                                                }
                                                                if (!cardFound)
                                                                {
                                                                        std::cout << "❌ La carte n'est pas dans votre main ou est mal orthographiée. Veuillez réessayer" << std::endl;
                                                                        i -= 1;
                                                                }
                                                                else
                                                                {
                                                                        std::cout << "➡️ La carte " << cardToDelete << " a été mise dans le rebus et n'est plus dans votre main \n"
                                                                                  << std::endl;
                                                                }
                                                                i += 1;
                                                        }
                                                        joueur_1->setActions(joueur_1->getActions() - 1);
                                                        std::cout << "➡️ Vous possédez désormais les cartes : " << std::endl;
                                                        joueur_1->afficheCartes();
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                                else if (cardToPlay == atelier->getLowerCuttedName() && joueur_1->possedeCarte(atelier->getName()))
                                                {
                                                        // Recoit une carte allant jusqu'a 4
                                                        joueur_1->supprimeCarteMain(atelier->getName(), false);

                                                        std::cout << "➡️ Vous pouvez acheter gratuitement une carte allant jusqu'à 4💰 \n"
                                                                  << std::endl;
                                                        plateau->affichePlateau();

                                                        int numberToGet = 1;
                                                        int i = 0;
                                                        while (i < numberToGet)
                                                        {
                                                                string cardToGet;
                                                                bool cardFound = false;
                                                                std::cout << "➡️ Quelle carte voulez vous acquérir ? (0 à 4💰)" << std::endl;
                                                                std::cin >> cardToGet;
                                                                cardToGet[0] = tolower(cardToGet[0]);
                                                                for (const auto &carte : plateau->reserve)
                                                                {
                                                                        if (cardToGet == carte.first->getLowerCuttedName() && carte.first->getPrice() <= 4)
                                                                        {

                                                                                joueur_1->ajouteCarteDefausse(carte.first);
                                                                                plateau->removeCard(carte.first);
                                                                                cardFound = true;
                                                                        }
                                                                }
                                                                if (!cardFound)
                                                                {
                                                                        std::cout << "❌ La carte n'est pas dans la reserve, est mal orthographiée ou coûte trop cher. Veuillez réessayer" << std::endl;
                                                                        i -= 1;
                                                                }
                                                                else
                                                                {
                                                                        std::cout << "➡️ La carte " << cardToGet << " a été mise dans votre défausse" << std::endl;
                                                                }
                                                                i += 1;
                                                        }
                                                        joueur_1->setActions(joueur_1->getActions() - 1);
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                                else
                                                {
                                                        std::cout << "❌ Vous avez mal orthographié votre carte ou vous ne la possédez pas, veuillez réessayer." << std::endl;
                                                        choice(joueur_1);
                                                        std::cin >> choix_J1;
                                                }
                                        }
                                        else
                                        {
                                                std::cout << "Vous n'avez pas assez de point d'action (💠)" << std::endl;
                                                choice(joueur_1);
                                                std::cin >> choix_J1;
                                        }
                                }
                                else if (choix_J1 == "2")
                                {
                                        if (joueur_1->getBuyPoints() >= 1)
                                        {
                                                plateau->affichePlateau();
                                                std::cout << "Vous avez : " << joueur_1->getMoney() << "💰 |" << joueur_1->getBuyPoints() << "🪙 |" << joueur_1->getActions() << "💠" << std::endl;
                                                string cardInput;
                                                bool cardFound = false;
                                                std::cout << "➡️ Quelle carte voulez vous acheter ? " << std::endl;
                                                std::cout.flush();
                                                std::cin >> cardInput;

                                                for (const auto &keyValue : plateau->reserve)
                                                {
                                                        size_t found = keyValue.first->getName().find(' ');
                                                        // On enlève le prix en string de la carte " (x💰)"
                                                        string card = keyValue.first->getName().substr(0, found);
                                                        std::transform(card.begin(), card.end(), card.begin(), ::tolower);
                                                        std::transform(cardInput.begin(), cardInput.end(), cardInput.begin(), ::tolower);

                                                        if (cardInput.compare(card) == 0)
                                                        {
                                                                if (keyValue.second > 0)
                                                                {
                                                                        if (joueur_1->acheteCarte(keyValue.first))
                                                                        {
                                                                                plateau->removeCard(keyValue.first);
                                                                        }
                                                                        joueur_1->afficheDefausse();
                                                                        joueur_1->affichePioche();
                                                                        cardFound = true;
                                                                }
                                                        }
                                                }
                                                if (!cardFound)
                                                {
                                                        std::cout << "❌ La carte n'est pas dans le plateau ou vous avez mal orthographié la carte" << std::endl;
                                                }
                                                else
                                                {
                                                        // on affiche  les pts d'actions
                                                        std::cout << "➡️ Vous possédez désormais les cartes : " << std::endl;
                                                        joueur_1->afficheCartes();
                                                        std::cout << "Il vous reste " << joueur_1->getMoney() << "💰|" << joueur_1->getBuyPoints() << "🪙 |" << joueur_1->getActions() << "💠" << std::endl;
                                                }
                                                choice(joueur_1);
                                                std::cin >> choix_J1;
                                        }
                                        else
                                        {
                                                std::cout << "❌ Vous n'avez pas assez d'achat 🪙" << std::endl;
                                                choice(joueur_1);
                                                std::cin >> choix_J1;
                                        }
                                }
                                else if (choix_J1 != "1" && choix_J1 != "2" && choix_J1 != "3")
                                {
                                        std::cout << "❌ Choix invalide veuillez réessayer." << std::endl;
                                        std::cin >> choix_J1;
                                }
                        } while (choix_J1 != "3");
                        // code pour choix 3
                        if (choix_J1 == "3")
                        {
                                std::cout << "➡️ Vos cartes ont été placées dans la défausse, Fin de votre tour. " << std::endl;
                                std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
                                joueur_1->HandToDefausse();
                        }
                }
                else
                {
                        for (int i = 0; i < 5; i++)
                        {
                                joueur_2->piocheCarte();
                        }
                        std::cout << "➡️ (J2 🧙‍♂️ ) Vous avez : " << std::endl;
                        joueur_2->afficheCartes();
                        joueur_2->afficheDefausse();
                        joueur_2->affichePioche();
                        choice(joueur_2);
                        std::cin >> choix_J2;
                        do
                        {
                                if (choix_J2 == "1")
                                {
                                        if (joueur_2->getActions() >= 1)
                                        {
                                                std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                joueur_2->afficheCartes();
                                                string cardToPlay;
                                                std::cout << "➡️ Quelle carte action voulez vous jouer ?" << std::endl;
                                                std::cin >> cardToPlay;
                                                std::transform(cardToPlay.begin(), cardToPlay.end(), cardToPlay.begin(), ::tolower);

                                                if (cardToPlay == cave->getLowerCuttedName() && joueur_2->possedeCarte(cave->getName()))
                                                {
                                                        joueur_2->supprimeCarteMain(cave->getName(), false);
                                                        std::cout << "➡️ Vous gagnez +1 Action et vous pouvez défausser autant de carte que vous voulez. Piochez une carte par carte défaussée" << std::endl;
                                                        int numberToThrow = 0;
                                                        int i = 0;
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        std::cout << "➡️ Combien de cartes voulez vous défausser? " << std::endl;
                                                        std::cin >> numberToThrow;
                                                        while (numberToThrow > joueur_2->getHandSize())
                                                        {
                                                                std::cout << "Vous ne possedez pas assez de cartes, veuillez rentrez un nouveau nombre" << std::endl;
                                                                std::cin >> numberToThrow;
                                                        }
                                                        while (i < numberToThrow)
                                                        {
                                                                string cardToMove;
                                                                bool cardFound = false;
                                                                std::cout << "➡️ Quel est le nom de la carte que vous voulez défausser ?" << std::endl;
                                                                std::cin >> cardToMove;
                                                                cardToMove[0] = tolower(cardToMove[0]);

                                                                for (const auto &carte : joueur_2->getHand())
                                                                {
                                                                        if (cardToMove == carte->getLowerCuttedName())
                                                                        {
                                                                                cardToMove = cardToMove + " (" + to_string(carte->getPrice()) + "💰)";
                                                                                cardToMove[0] = toupper(cardToMove[0]);
                                                                                joueur_2->supprimeCarteMain(cardToMove, false);
                                                                                cardFound = true;
                                                                        }
                                                                }
                                                                if (!cardFound)
                                                                {
                                                                        std::cout << "❌ La carte n'est pas dans votre main ou est mal orthographiée. Veuillez réessayer" << std::endl;
                                                                        i -= 1;
                                                                }
                                                                else
                                                                {
                                                                        std::cout << "➡️ La carte " << cardToMove << " a été mise dans la défausse et n'est plus dans votre main \n"
                                                                                  << std::endl;
                                                                }
                                                                i += 1;
                                                        }
                                                        for (int j = 0; j < numberToThrow; j++)
                                                        {
                                                                joueur_2->piocheCarte();
                                                        }

                                                        std::cout << "➡️ Vous avez pioché " << numberToThrow << " carte(s)\n"
                                                                  << std::endl;

                                                        std::cout << "➡️ Vous possédez désormais les cartes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                                else if (cardToPlay == renovation->getLowerCuttedName() && joueur_2->possedeCarte(renovation->getName()))
                                                {
                                                        if (joueur_2->getHandSize() >= 1)
                                                        {
                                                                // écarte une carte de la main, reçoit une carte jusqu'à +2 que la carte écartée
                                                                joueur_2->supprimeCarteMain(renovation->getName(), false);
                                                                int numberToDelete = 1;
                                                                int i = 0;
                                                                std::cout << "➡️ Ecartez une carte de votre main et recevez une carte coûtant jusqu'à +2💰 que le coût de votre carte" << std::endl;
                                                                std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                                joueur_2->afficheCartes();
                                                                int cardPrice = 0;
                                                                while (i < numberToDelete)
                                                                {
                                                                        string cardToDelete;
                                                                        bool cardFound = false;
                                                                        std::cout << "➡️ Quel est le nom de la carte que vous voulez écarter ?" << std::endl;
                                                                        std::cin >> cardToDelete;
                                                                        cardToDelete[0] = tolower(cardToDelete[0]);

                                                                        for (const auto &carte : joueur_2->getHand())
                                                                        {
                                                                                if (cardToDelete == carte->getLowerCuttedName())
                                                                                {
                                                                                        plateau->rebus.push_back(carte);
                                                                                        cardToDelete = cardToDelete + " (" + to_string(carte->getPrice()) + "💰)";
                                                                                        cardToDelete[0] = toupper(cardToDelete[0]);
                                                                                        joueur_2->supprimeCarteMain(cardToDelete, true);
                                                                                        cardFound = true;
                                                                                        cardPrice += carte->getPrice();
                                                                                }
                                                                        }
                                                                        if (!cardFound)
                                                                        {
                                                                                std::cout << "❌ La carte n'est pas dans votre main ou est mal orthographiée. Veuillez réessayer" << std::endl;
                                                                                i -= 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                std::cout << "➡️ La carte " << cardToDelete << " a été mise dans le rebus et n'est plus dans votre main \n"
                                                                                          << std::endl;
                                                                        }
                                                                        i += 1;
                                                                }

                                                                plateau->affichePlateau();

                                                                int numberToGet = 1;
                                                                int j = 0;
                                                                while (j < numberToGet)
                                                                {
                                                                        string cardToGet;
                                                                        bool cardFound = false;
                                                                        std::cout << "➡️ Quelle carte voulez vous acquérir ? (0 à " << cardPrice + 2 << "💰)" << std::endl;
                                                                        std::cin >> cardToGet;
                                                                        cardToGet[0] = tolower(cardToGet[0]);
                                                                        for (const auto &carte : plateau->reserve)
                                                                        {
                                                                                if (cardToGet == carte.first->getLowerCuttedName() && carte.first->getPrice() <= cardPrice + 2)
                                                                                {

                                                                                        joueur_2->ajouteCarteDefausse(carte.first);
                                                                                        plateau->removeCard(carte.first);
                                                                                        cardFound = true;
                                                                                }
                                                                        }
                                                                        if (!cardFound)
                                                                        {
                                                                                std::cout << "❌ La carte n'est pas dans la reserve, est mal orthographiée ou coûte trop cher. Veuillez réessayer" << std::endl;
                                                                                j -= 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                std::cout << "➡️ La carte " << cardToGet << " a été mise dans votre défausse" << std::endl;
                                                                        }
                                                                        j += 1;
                                                                }
                                                                joueur_1->setActions(joueur_2->getActions() - 1);
                                                                choice(joueur_2);
                                                                std::cin >> choix_J2;
                                                        }
                                                        else
                                                        {
                                                                std::cout << "❌ Vous n'avez plus de carte pour pouvoir jouer la carte rénovation \n"
                                                                          << std::endl;
                                                                choice(joueur_2);
                                                                std::cin >> choix_J2;
                                                        }
                                                }
                                                else if (cardToPlay == sorciere->getLowerCuttedName() && joueur_2->possedeCarte(sorciere->getName()))
                                                {
                                                        // Ajoute une carte malédiction dans la défausse de l'adversaire
                                                        joueur_2->supprimeCarteMain(sorciere->getName(), false);
                                                        if (plateau->reserve[malediction] > 0)
                                                        {
                                                                plateau->reserve[malediction]--;
                                                                // ajoute la carte malédiction dans la défausse de l'ennemi
                                                                joueur_1->ajouteCarteDefausse(malediction);
                                                                std::cout << "➡️ Une carte malédiction a été placé dans la défausse de votre/vos adversaire(s)" << std::endl;
                                                        }
                                                        else
                                                        {
                                                                std::cout << "➡️ Il n'y a plus de carte malédiction dans la réserve, vous piochez 2 cartes" << std::endl;
                                                                joueur_2->piocheCarte();
                                                                joueur_2->piocheCarte();
                                                        }
                                                        joueur_2->setActions(joueur_2->getActions() - 1);
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                                else if (cardToPlay == marche->getLowerCuttedName() && joueur_2->possedeCarte(marche->getName()))
                                                {
                                                        // Octroie 1 point d'action, 1 carte, 1 pièce de cuivre et 1 achat
                                                        joueur_2->supprimeCarteMain(marche->getName(), false);
                                                        joueur_2->setBuyPoints(joueur_2->getBuyPoints() + 1);
                                                        joueur_2->piocheCarte();
                                                        joueur_2->setMoney(joueur_2->getMoney() + 1);
                                                        std::cout << "➡️ Vous gagnez +1 Carte, +1💠 Action, +1💰 Pièce et +1🪙  Achat" << std::endl;
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        std::cout << "Vous avez : " << joueur_2->getMoney() << "💰| " << joueur_2->getBuyPoints() << "🪙 |" << joueur_2->getActions() << "💠" << std::endl;
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                                else if (cardToPlay == forgeron->getLowerCuttedName() && joueur_2->possedeCarte(forgeron->getName()))
                                                {
                                                        // Pioche 3 cartes
                                                        joueur_2->affichePioche();
                                                        joueur_2->afficheDefausse();
                                                        joueur_2->supprimeCarteMain(forgeron->getName(), false);

                                                        if (joueur_1->getPiocheSize() < 3)
                                                        {
                                                                joueur_1->defausseToPioche();
                                                        }

                                                        for (int i = 0; i <= 2; i++)
                                                        {
                                                                joueur_2->piocheCarte();
                                                        }
                                                        joueur_2->setActions(joueur_2->getActions() - 1);
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                                else if (cardToPlay == bucheron->getLowerCuttedName() && joueur_2->possedeCarte(bucheron->getName()))
                                                {
                                                        // +1 Achat et 2 pièces pour le tour
                                                        joueur_2->supprimeCarteMain(bucheron->getName(), false);
                                                        joueur_2->setBuyPoints(joueur_2->getBuyPoints() + 1);
                                                        joueur_2->setMoney(joueur_2->getMoney() + 2);
                                                        joueur_2->setActions(joueur_2->getActions() - 1);
                                                        std::cout << "➡️ Vous gagnez +1 Achat et 2 pièces \n"
                                                                  << std::endl;
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        std::cout << "Vous avez : " << joueur_2->getMoney() << "💰| " << joueur_2->getBuyPoints() << "🪙 |" << joueur_2->getActions() << "💠" << std::endl;
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                                else if (cardToPlay == mine->getLowerCuttedName() && joueur_2->possedeCarte(mine->getName()))
                                                {
                                                        if (joueur_2->hasTresorCard(joueur_2->getHand()))
                                                        {
                                                                // écarte une carte trésor de la main, reçoit une carte trésor valant jusqu'à +3. Ajoute cette carte à notre main
                                                                joueur_2->supprimeCarteMain(mine->getName(), false);
                                                                int numberToDelete = 1;
                                                                int i = 0;
                                                                int cardPrice = 0;
                                                                std::cout << "➡️ Ecartez une carte trésor de votre main pour en recevoir une coûtant 3💰 de plus" << std::endl;
                                                                std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                                joueur_2->afficheCartes();
                                                                while (i < numberToDelete)
                                                                {
                                                                        string cardToDelete;
                                                                        bool cardFound = false;
                                                                        std::cout << "➡️ Quel est le nom de la carte trésor que vous voulez écarter ?" << std::endl;
                                                                        std::cin >> cardToDelete;
                                                                        cardToDelete[0] = tolower(cardToDelete[0]);
                                                                        int handValue = joueur_2->getMoney();
                                                                        for (const auto &carte : joueur_2->getHand())
                                                                        {
                                                                                if (cardToDelete == carte->getLowerCuttedName() && (carte->getName() == "Cuivre (0💰)" || carte->getName() == "Argent (3💰)" || carte->getName() == "Or (6💰)"))
                                                                                {
                                                                                        // on utilise le static cast pour pouvoir utiliser la méthode getValeur de carteTresor, on a vérifié auparavant qu'il s'agissait bien d'une carte trésor.
                                                                                        handValue -= static_cast<CarteTresor *>(carte)->getValeur();
                                                                                        plateau->rebus.push_back(carte);
                                                                                        cardPrice = carte->getPrice();
                                                                                        cardToDelete = cardToDelete + " (" + to_string(carte->getPrice()) + "💰)";
                                                                                        cardToDelete[0] = toupper(cardToDelete[0]);
                                                                                        joueur_2->supprimeCarteMain(cardToDelete, true);
                                                                                        cardFound = true;
                                                                                }
                                                                        }
                                                                        if (!cardFound)
                                                                        {
                                                                                std::cout << "❌ La carte n'est pas dans votre main ou est mal orthographiée ou n'est pas une carte trésor. Veuillez réessayer" << std::endl;
                                                                                i -= 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                std::cout << "➡️ La carte " << cardToDelete << " a été mise dans le rebus et n'est plus dans votre main \n"
                                                                                          << std::endl;
                                                                                joueur_2->setMoney(handValue);
                                                                                std::cout << "Vous avez : " << joueur_2->getMoney() << "💰 |" << joueur_2->getBuyPoints() << "🪙 |" << joueur_2->getActions() << "💠" << std::endl;
                                                                        }
                                                                        i += 1;
                                                                }
                                                                std::cout << "➡️ Vous pouvez désormais acquérir une carte trésor valant jusqu'à : " << cardPrice + 3 << "💰" << std::endl;
                                                                plateau->affichePlateau();
                                                                int finalCardPrice = cardPrice + 3;
                                                                int it = 1;
                                                                int j = 0;
                                                                while (j < it)
                                                                {
                                                                        string cardToGet;
                                                                        bool cardFound = false;
                                                                        std::cout << "➡️ Quelle carte voulez vous acquérir ? ( jusqu'à " << finalCardPrice << "💰)" << std::endl;
                                                                        std::cin >> cardToGet;

                                                                        for (const auto &carte : plateau->reserve)
                                                                        {
                                                                                if (cardToGet == carte.first->getLowerCuttedName() && carte.first->getPrice() <= finalCardPrice && (carte.first->getName() == "Cuivre (0💰)" || carte.first->getName() == "Argent (3💰)" || carte.first->getName() == "Or (6💰)"))
                                                                                {

                                                                                        joueur_2->ajouteCarteMain(carte.first);
                                                                                        // on utilise le static cast pour pouvoir utiliser la méthode getValeur de carteTresor, on a vérifié auparavant qu'il s'agissait bien d'une carte trésor.
                                                                                        joueur_2->setMoney(joueur_2->getMoney() + static_cast<CarteTresor *>(carte.first)->getValeur());
                                                                                        plateau->removeCard(carte.first);
                                                                                        cardFound = true;
                                                                                }
                                                                        }
                                                                        if (!cardFound)
                                                                        {
                                                                                std::cout << "❌ La carte n'est pas dans la reserve, est mal orthographiée, est trop coûteuse ou n'est pas une carte trésor. Veuillez réessayer" << std::endl;
                                                                                j -= 1;
                                                                        }
                                                                        else
                                                                        {
                                                                                std::cout << "➡️ La carte " << cardToGet << " a été mise dans votre main" << std::endl;
                                                                        }
                                                                        j += 1;
                                                                }
                                                                joueur_2->setActions(joueur_2->getActions() - 1);
                                                                std::cout << "Vous avez : " << joueur_2->getMoney() << "💰 |" << joueur_2->getBuyPoints() << "🪙 |" << joueur_2->getActions() << "💠" << std::endl;
                                                                choice(joueur_2);
                                                                std::cin >> choix_J2;
                                                        }
                                                        else
                                                        {

                                                                std::cout << "Vous n'avez pas de carte trésor pour jouer la carte mine. \n"
                                                                          << std::endl;
                                                                std::cout << "Vous avez : " << joueur_2->getMoney() << "💰 |" << joueur_2->getBuyPoints() << "🪙 |" << joueur_2->getActions() << "💠" << std::endl;
                                                                choice(joueur_2);
                                                                std::cin >> choix_J2;
                                                        }
                                                }
                                                else if (cardToPlay == village->getLowerCuttedName() && joueur_2->possedeCarte(village->getName()))
                                                {
                                                        // Octroie 2 points d'action et 1 pioche une carte
                                                        joueur_2->supprimeCarteMain(village->getName(), false);
                                                        joueur_2->setActions(joueur_2->getActions() + 1);
                                                        std::cout << "➡️ Vous gagnez +1 Carte et +2💠 Actions" << std::endl;
                                                        joueur_2->piocheCarte();
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        std::cout << "Vous avez : " << joueur_2->getMoney() << "💰 | " << joueur_2->getBuyPoints() << "🪙 |" << joueur_2->getActions() << "💠" << std::endl;
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                                else if (cardToPlay == chapelle->getLowerCuttedName() && joueur_2->possedeCarte(chapelle->getName()))
                                                {
                                                        // Place jusqu'à 4 cartes dans le rebus
                                                        joueur_2->supprimeCarteMain(chapelle->getName(), false);
                                                        int numberToDelete;
                                                        int i = 0;
                                                        std::cout << "➡️ Vous pouvez écarter jusqu'à 4 cartes de votre main" << std::endl;
                                                        std::cout << "➡️ Vous possédez les cartes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        std::cout << "➡️ Combien de carte voulez vous écarter ? ";
                                                        std::cin >> numberToDelete;
                                                        while (numberToDelete > 4 && numberToDelete > joueur_2->getHandSize())
                                                        {
                                                                std::cout << "❌ Vous ne pouvez pas écarter plus de 4 cartes" << std::endl;
                                                                std::cin >> numberToDelete;
                                                        }
                                                        while (i < numberToDelete)
                                                        {
                                                                string cardToDelete;
                                                                bool cardFound = false;
                                                                std::cout << "➡️ Quel est le nom de la carte que vous voulez écarter ?" << std::endl;
                                                                std::cin >> cardToDelete;
                                                                cardToDelete[0] = tolower(cardToDelete[0]);

                                                                for (const auto &carte : joueur_2->getHand())
                                                                {
                                                                        if (cardToDelete == carte->getLowerCuttedName())
                                                                        {
                                                                                cardToDelete = cardToDelete + " (" + to_string(carte->getPrice()) + "💰)";
                                                                                cardToDelete[0] = toupper(cardToDelete[0]);
                                                                                joueur_2->supprimeCarteMain(cardToDelete, true);
                                                                                plateau->rebus.push_back(carte);
                                                                                cardFound = true;
                                                                        }
                                                                }
                                                                if (!cardFound)
                                                                {
                                                                        std::cout << "❌ La carte n'est pas dans votre main ou est mal orthographiée. Veuillez réessayer" << std::endl;
                                                                        i -= 1;
                                                                }
                                                                else
                                                                {
                                                                        std::cout << "➡️ La carte " << cardToDelete << " a été mise dans le rebus et n'est plus dans votre main \n"
                                                                                  << std::endl;
                                                                }
                                                                i += 1;
                                                        }
                                                        joueur_2->setActions(joueur_2->getActions() - 1);
                                                        std::cout << "➡️ Vous possédez désormais les cartes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                                else if (cardToPlay == atelier->getLowerCuttedName() && joueur_2->possedeCarte(atelier->getName()))
                                                {
                                                        // Recoit une carte allant jusqu'a 4
                                                        joueur_2->supprimeCarteMain(atelier->getName(), false);

                                                        std::cout << "➡️ Vous pouvez acheter gratuitement une carte allant jusqu'à 4💰 \n"
                                                                  << std::endl;
                                                        plateau->affichePlateau();

                                                        int numberToGet = 1;
                                                        int i = 0;
                                                        while (i < numberToGet)
                                                        {
                                                                string cardToGet;
                                                                bool cardFound = false;
                                                                std::cout << "➡️ Quelle carte voulez vous acquérir ? (0 à 4💰)" << std::endl;
                                                                std::cin >> cardToGet;
                                                                cardToGet[0] = tolower(cardToGet[0]);
                                                                for (const auto &carte : plateau->reserve)
                                                                {
                                                                        if (cardToGet == carte.first->getLowerCuttedName() && carte.first->getPrice() <= 4)
                                                                        {

                                                                                joueur_2->ajouteCarteDefausse(carte.first);
                                                                                plateau->removeCard(carte.first);
                                                                                cardFound = true;
                                                                        }
                                                                }
                                                                if (!cardFound)
                                                                {
                                                                        std::cout << "❌ La carte n'est pas dans la reserve, est mal orthographiée ou coûte trop cher. Veuillez réessayer" << std::endl;
                                                                        i -= 1;
                                                                }
                                                                else
                                                                {
                                                                        std::cout << "➡️ La carte " << cardToGet << " a été mise dans votre défausse" << std::endl;
                                                                }
                                                                i += 1;
                                                        }
                                                        joueur_2->setActions(joueur_2->getActions() - 1);
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                                else
                                                {
                                                        std::cout << "❌ Vous avez mal orthographié votre carte ou vous ne la possédez pas, veuillez réessayer." << std::endl;
                                                        choice(joueur_2);
                                                        std::cin >> choix_J2;
                                                }
                                        }
                                        else
                                        {
                                                std::cout << "Vous n'avez pas assez de point d'action (💠)" << std::endl;
                                                choice(joueur_2);
                                                std::cin >> choix_J2;
                                        }
                                }

                                else if (choix_J2 == "2")
                                {
                                        if (joueur_2->getBuyPoints() >= 1)
                                        {
                                                plateau->affichePlateau();
                                                std::cout << "Vous avez : " << joueur_2->getMoney() << "💰| " << joueur_2->getBuyPoints() << "🪙 |" << joueur_2->getActions() << "💠" << std::endl;
                                                string cardInput;
                                                bool cardFound = false;
                                                std::cout << "➡️ Quelle carte voulez vous acheter ? " << std::endl;
                                                std::cout.flush();
                                                std::cin >> cardInput;

                                                for (const auto &keyValue : plateau->reserve)
                                                {
                                                        size_t found = keyValue.first->getName().find(' ');
                                                        string card = keyValue.first->getName().substr(0, found);
                                                        std::transform(card.begin(), card.end(), card.begin(), ::tolower);
                                                        std::transform(cardInput.begin(), cardInput.end(), cardInput.begin(), ::tolower);

                                                        if (cardInput.compare(card) == 0)
                                                        {
                                                                if (keyValue.second > 0)
                                                                {
                                                                        if (joueur_2->acheteCarte(keyValue.first))
                                                                        {
                                                                                plateau->removeCard(keyValue.first);
                                                                        }
                                                                        cardFound = true;
                                                                }
                                                        }
                                                }
                                                if (!cardFound)
                                                {
                                                        std::cout << "❌ La carte n'est pas dans le plateau ou vous l'avez mal orthographié" << std::endl;
                                                }
                                                else
                                                {
                                                        // on affiche  les pts d'actions
                                                        std::cout << "➡️ Vous possédez désormais les cartes suivantes : " << std::endl;
                                                        joueur_2->afficheCartes();
                                                        std::cout << "Il vous reste " << joueur_2->getMoney() << "💰|" << joueur_2->getBuyPoints() << "🪙 |" << joueur_2->getActions() << "💠" << std::endl;
                                                }
                                                choice(joueur_2);
                                                std::cin >> choix_J2;
                                        }
                                        else
                                        {
                                                std::cout << "❌ Vous n'avez pas assez d'achat 🪙" << std::endl;
                                                choice(joueur_2);
                                                std::cin >> choix_J2;
                                        }
                                }
                                else if (choix_J2 != "1" && choix_J2 != "2" && choix_J2 != "3")
                                {
                                        std::cout << "❌ Choix invalide veuillez réessayer." << std::endl;
                                        std::cin >> choix_J2;
                                }
                        } while (choix_J2 != "3");
                        // code pour choix 3
                        if (choix_J2 == "3")
                        {
                                std::cout << "➡️ Vos cartes ont été placées dans la défausse, Fin de votre tour. " << std::endl;
                                std::cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
                                joueur_2->HandToDefausse();
                        }
                }

                nombreTour += 1;
                count = 0;
                joueur_1_Turn = !joueur_1_Turn;
                joueur_2_Turn = !joueur_2_Turn;
                joueur_1->setActions(1);
                joueur_2->setActions(1);
                joueur_1->setBuyPoints(1);
                joueur_2->setBuyPoints(1);
        }

        std::cout << "                                                🕯️  La partie est terminée 🕯️ \n"
                  << std::endl;
        if (count > 2 || plateau->reserve[province] <= 0)
        {
                joueur_1->HandToDefausse();
                joueur_2->HandToDefausse();
                joueur_1->defausseToPioche();
                joueur_2->defausseToPioche();
                std::cout << "TEST POINTS " << joueur_1->getVictoryPointsAmount() << std::endl;
                std::cout << "🥁" << std::endl;
                std::cout << "🥁" << std::endl;
                std::cout << "🥁\n"
                          << std::endl;

                std::cout << "Le joueur 1 🤴 possède : " << joueur_1->getVictoryPointsAmount() << "⚔️  point(s) de victoire(s).\n"
                          << std::endl;
                std::cout << "Le joueur 2 🧙‍♂️ possède : " << joueur_2->getVictoryPointsAmount() << "⚔️  point(s) de victoire(s)." << std::endl;

                if (joueur_1->getVictoryPointsAmount() > joueur_2->getVictoryPointsAmount())
                {
                        std::cout << "Le joueur 1 🤴 gagne la partie" << std::endl;
                }
                else if (joueur_1->getVictoryPointsAmount() < joueur_2->getVictoryPointsAmount())
                {
                        std::cout << "Le joueur 2 🧙‍♂️ gagne la partie" << std::endl;
                }
                else
                {
                        std::cout << "Il y a égalité 🎌" << std::endl;
                }
        }

        // delete all variables
        delete cave;
        delete renovation;
        delete sorciere;
        delete marche;
        delete forgeron;
        delete bucheron;
        delete mine;
        delete village;
        delete chapelle;
        delete atelier;
        delete domaine;
        delete duche;
        delete province;
        delete malediction;
        delete cuivre;
        delete argent;
        delete gold;
        delete joueur_1;
        delete joueur_2;
        delete plateau;
}
