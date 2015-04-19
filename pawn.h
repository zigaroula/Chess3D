#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
    public:
        Pawn(int);
        virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);
        virtual std::string getModelPath() const{return "models/pion.obj";}
    private:
        int d;
};

#endif // PAWN_H
