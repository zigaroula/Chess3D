#ifndef GAME_H
#define GAME_H

/**
 * \class Game
 * \brief Classe qui implémente les règles du jeu d'échec
 */

#include "board.h"
#include "player.h"

class Game
{
public:
    Game();
    ///Créer une nouvelle partie normale
    virtual void initClassicGame();
    ///Recharge une partie précédente
    virtual void loadFromFile();
    ///Sauvegarde la partie en cours
    virtual void saveToFile();
    ///Regarde si un joueur est en échec et renvoie le joueur associé
    Player check();
    ///Regarde si un joueur est en échec et mat et renvoie le joueur associé
    Player checkMate();
    ///Change le joueur en cours
    void changeTurn();
private:
    Board board;
    Player player1, player2, none;
    int turn;
};

#endif // GAME_H
