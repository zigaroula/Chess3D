#include "player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::init(int side) {
    Piece pawn1, pawn2, pawn3, pawn4, pawn5, pawn6, pawn7, pawn8,
    rook1, rook2, knight1, knight2, bishop1, bishop2, queen, king;
    if (side == 1) {
        pawn1.init(PAWN, 6, 0);
        pawn2.init(PAWN, 6, 1);
        pawn3.init(PAWN, 6, 2);
        pawn4.init(PAWN, 6, 3);
        pawn5.init(PAWN, 6, 4);
        pawn6.init(PAWN, 6, 5);
        pawn7.init(PAWN, 6, 6);
        pawn8.init(PAWN, 6, 7);
        rook1.init(ROOK, 7, 0);
        knight1.init(KNIGHT, 7, 1);
        bishop1.init(BISHOP, 7, 2);
        queen.init(QUEEN, 7, 3);
        king.init(KING, 7, 4);
        bishop2.init(BISHOP, 7, 5);
        knight2.init(KNIGHT, 7, 6);
        rook2.init(ROOK, 7, 7);
    } else {
        pawn1.init(PAWN, 1, 0);
        pawn2.init(PAWN, 1, 1);
        pawn3.init(PAWN, 1, 2);
        pawn4.init(PAWN, 1, 3);
        pawn5.init(PAWN, 1, 4);
        pawn6.init(PAWN, 1, 5);
        pawn7.init(PAWN, 1, 6);
        pawn8.init(PAWN, 1, 7);
        rook1.init(ROOK, 0, 0);
        knight1.init(KNIGHT, 0, 1);
        bishop1.init(BISHOP, 0, 2);
        queen.init(QUEEN, 0, 3);
        king.init(KING, 0, 4);
        bishop2.init(BISHOP, 0, 5);
        knight2.init(KNIGHT, 0, 6);
        rook2.init(ROOK, 0, 7);
    }
    number = side;
}

bool Player::check() {
    if (/*CONDITION*/0) {
        return true;
    } else {
        return false;
    }
}

bool Player::checkMate() {
    if (/*CONDITION*/0) {
        return true;
    } else {
        return false;
    }
}

void Player::loose() {

}

void Player::win() {

}
