#ifndef BOARD_H
#define BOARD_H

#include <glm/glm.hpp>
#include <vector>
#include "scene.h"

class Board
{
public:
    Board();
    virtual ~Board();
    void initClassic(Scene * _scene);

    inline glm::vec3 getPosAt(int i, int j){return squares[i][j];}
    ///calcule et stocke la position dans squares
    void computeAllSquares();

private:
    //##DEBUG :
    void placerPion(int i, int j);
    Scene * scene;
    ///retourne la position réelle d'une case sur le plateau
    glm::vec3 computeRealPosition(int i, int j);
    ///Permet de maper un ensemble de 2 int en positions réelles dans l'espace
    std::vector<std::vector<glm::vec3> > squares;
    const glm::vec3 centerToSquare0 = glm::vec3(-265.0f, 0.0f, -265.0f);
    const float squareOffset = 76.0f;
};

#endif // BOARD_H
