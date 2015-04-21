#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
public:
    virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);
    virtual std::string getModelPath() const{return "models/cavalier.obj";}
    virtual std::string getName() const{return "Knight";}
};

#endif // KNIGHT_H
