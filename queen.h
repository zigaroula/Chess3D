#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece
{
public:
    virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);
    virtual std::string getModelPath() const{return "models/dame.obj";}
};

#endif // QUEEN_H
