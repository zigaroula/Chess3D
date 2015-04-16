#ifndef GAME_H
#define GAME_H

/**
 * \class Game
 * \brief Classe qui implémente les règles du jeu d'échec
 */

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


};

#endif // GAME_H
