#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
    public:
        Pawn(int);
        virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);
    private:
        int d;
};

#endif // PAWN_H
