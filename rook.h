#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece
{
    public:
        virtual void computeAvailableMovements(std::vector<Piece>, std::vector<Piece>);
};

#endif // ROOK_H
