#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
    public:
        virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);
};

#endif // PAWN_H
