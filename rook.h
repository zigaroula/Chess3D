#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece
{
public:
    virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);
    virtual std::string getModelPath() const{return "models/tour.obj";}
    virtual std::string getName() const{return "Rook";}
};

#endif // ROOK_H
