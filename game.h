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

private:
    Board board;
    Player player1, player2;

};

#endif // GAME_H
