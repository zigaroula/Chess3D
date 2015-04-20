#include "piece.h"

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
        if (availableMovements[i] == std::vector<int>(targetX, targetY)) {
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

std::string Piece::toString() const{
    std::string s = "Pièce en " ;
    s = posX + " et " + posY ;
    return s;
}
