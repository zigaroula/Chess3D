#ifndef GAME_H
#define GAME_H

/**
 * \class Game
 * \brief Classe qui implémente les règles du jeu d'échec
 */

#include <iostream>
#include "board.h"
#include "player.h"
#include "scene.h"
#include "piece.h"

class Game
{
public:
    Game();
    ///Créer une nouvelle partie normale
    virtual void initClassicGame(Scene * _scene);
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
    ///Calcule les mouvements disponibles pour toutes les pièces
    void computeAvailableMovements();
    
    int getPlayerId() { return turn; }

    ///DEBUGGING
    void testDebug();
private:
    Board board;
    Player player1, player2, none;
    int turn;
};

#endif // GAME_H
