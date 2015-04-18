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

void Piece::computeAvailableMovements(std::vector<Piece> own, std::vector<Piece> opp) {

}
