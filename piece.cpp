#include "piece.h"

Piece::Piece() {

}

void Piece::init(int _type, int _posX, int _posY) {
    type = _type;
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
    availableMovements = std::vector<std::vector<int> >();
    switch(type) {
        case PAWN:
            computePawn(own, opp);
            break;
        case ROOK:
            computeRook(own, opp);
            break;
        case KNIGHT:
            computeKnight(own, opp);
            break;
        case BISHOP:
            computeBishop(own, opp);
            break;
        case QUEEN:
            computeQueen(own, opp);
            break;
        case KING:
            computeKing(own, opp);
            break;

    }
}

void Piece::computePawn(std::vector<Piece> own, std::vector<Piece> opp) {

}

void Piece::computeRook(std::vector<Piece> own, std::vector<Piece> opp) {

}

void Piece::computeKnight(std::vector<Piece> own, std::vector<Piece> opp) {

}

void Piece::computeBishop(std::vector<Piece> own, std::vector<Piece> opp) {
    int x = posX+1;
    int y = posY+1;
    while(x<8 && y<8) {
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            //Si on rencontre une piece amie, on exclus la case et toutes les suivantes
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            //Si on rencontre une piece ennemie, on inclus la case et on exclus les suivantes
        }
        x++;
        y++;
    }
    x = posX-1;
    y = posY+1;
    while(x>0 && y<8) {
        for (unsigned int i = 0 ; i < own.size() ; i++) {

        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {

        }
        x--;
        y++;
    }
    x = posX+1;
    y = posY-1;
    while(x<8 && y>0) {
        for (unsigned int i = 0 ; i < own.size() ; i++) {

        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {

        }
        x++;
        y--;
    }
    x = posX-1;
    y = posY-1;
    while(x>0 && y>0) {
        for (unsigned int i = 0 ; i < own.size() ; i++) {

        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {

        }
        x--;
        y--;
    }
    //On inclus la position actuelle (permet de rendre échec et mat plus facile à implémenter). Changement possible
    availableMovements.push_back(std::vector<int>(posX,posY));
}

void Piece::computeQueen(std::vector<Piece> own, std::vector<Piece> opp) {

}

void Piece::computeKing(std::vector<Piece> own, std::vector<Piece> opp) {

}
