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
    void initClassicGame(Scene * _scene);
    void loadFromFile(Scene *scene);
    void saveToFile();
    /// Vérifie si le joueur désigné est en échec.
    bool check(Player player, Player opponent, std::vector<int> KingPos);
    /// Vérifie si le joueur désigné est en échec et mat.
    bool checkMate(Player player, Player opponent);
    void changeTurn();
    void computeAvailableMovements();
    void tryMovement(int vaoId, int caseX, int caseY);
    void tryMovement(int vaoId1, int vaoId2);
    int getPlayerId() const { return turn; }
    void endGame(int winner);
    void testDebug();
    

private:
    Scene *scene;
    Board board;
    Player player1, player2, none;
    int turn;
};

#endif // GAME_H
