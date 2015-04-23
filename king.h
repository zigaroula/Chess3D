#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
public:
    virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);
    virtual void deleteAvailableMovements(std::vector<int> impossibleMovements);
    virtual std::string getModelPath() const{return "models/roi.obj";}
    virtual std::string getName() const {return "King";}
};

#endif // KING_H
