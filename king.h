#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>); // NON OPTIMAL
    virtual std::string getModelPath() const{return "models/roi.obj";}
};

#endif // KING_H