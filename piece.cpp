#include "piece.h"
#include <string>

Piece::Piece() {

}

void Piece::init(int _posX, int _posY) {
    posX = _posX;
    posY = _posY;
}

Piece::~Piece() {

}

bool Piece::canMoveTo(int targetX, int targetY) {
    for (unsigned int i = 0 ; i < availableMovements.size() ; i++) {
        
        if (availableMovements[i][0] == targetX && availableMovements[i][1] == targetY) {
            return true;
        }
    }
    return false;
}

void Piece::moveTo(int targetX, int targetY) {
    posX = targetX;
    posY = targetY;
}

std::vector<int> Piece::getPosition() {
    std::vector<int> position;
    position.resize(2);
    position[0] = posX;
    position[1] = posY;
    return position;
}

void Piece::computeAvailableMovements(std::vector<Piece*> own, std::vector<Piece*> opp) {

}

std::string Piece::toString() const {
    std::string s = "Pièce en " ;
    s = std::to_string(posX) + " et " + std::to_string(posY) ;
    return s;
}
