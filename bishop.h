#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece
{
    public:
        virtual void computeAvailableMovements(std::vector<Piece>, std::vector<Piece>);
};

#endif // BISHOP_H
