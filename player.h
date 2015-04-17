#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "piece.h"

class Player
{
    public:
        Player();
        virtual ~Player();
        void init(int);
        bool check();
        bool checkMate();
        void loose();
        void win();
    private:
        int number;
        std::vector<Piece> pieces;
};

#endif // PLAYER_H
