#ifndef BOARD_H
#define BOARD_H

#include <glm/glm.hpp>
#include <vector>

class Board
{
    public:
        Board();
        virtual ~Board();
        void init();
    private:
        ///Permet de maper un ensemble de 2 int en positions réelles dans l'espace
        std::vector<std::vector<glm::vec3> > squares;
};

#endif // BOARD_H
