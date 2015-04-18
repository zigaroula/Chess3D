#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
    public:
        virtual void computeAvailableMovements(std::vector<Piece>, std::vector<Piece>);
};

#endif // KNIGHT_H
