#include "player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::init(int side) {
    if (side == 1) {
        pawn1->init(6, 0);
        pawn2->init(6, 1);
        pawn3->init(6, 2);
        pawn4->init(6, 3);
        pawn5->init(6, 4);
        pawn6->init(6, 5);
        pawn7->init(6, 6);
        pawn8->init(6, 7);
        rook1->init(7, 0);
        knight1->init(7, 1);
        bishop1->init(7, 2);
        queen->init(7, 3);
        king->init(7, 4);
        bishop2->init(7, 5);
        knight2->init(7, 6);
        rook2->init(7, 7);
    } else if (side == 2) {
        pawn1->init(1, 0);
        pawn2->init(1, 1);
        pawn3->init(1, 2);
        pawn4->init(1, 3);
        pawn5->init(1, 4);
        pawn6->init(1, 5);
        pawn7->init(1, 6);
        pawn8->init(1, 7);
        rook1->init(0, 0);
        knight1->init(0, 1);
        bishop1->init(0, 2);
        queen->init(0, 3);
        king->init(0, 4);
        bishop2->init(0, 5);
        knight2->init(0, 6);
        rook2->init(0, 7);
    }
    number = side;
    pieces.push_back(pawn1);
    pieces.push_back(pawn2);
    pieces.push_back(pawn3);
    pieces.push_back(pawn4);
    pieces.push_back(pawn5);
    pieces.push_back(pawn6);
    pieces.push_back(pawn7);
    pieces.push_back(pawn8);
    pieces.push_back(rook1);
    pieces.push_back(rook2);
    pieces.push_back(knight1);
    pieces.push_back(knight2);
    pieces.push_back(bishop1);
    pieces.push_back(bishop2);
    pieces.push_back(queen);
    pieces.push_back(king);
}

void Player::loose() {

}

void Player::win() {

}

void Player::computeAvailableMovements(std::vector<Piece*> own, std::vector<Piece*> opp) {
    for (unsigned int i = 0 ; i < pieces.size() ; i++) {
        pieces[i]->computeAvailableMovements(own, opp);
    }
}

void Player::initDebug(int side) {
    rook1 = new Rook();
    pawn1 = new Pawn();
    if (side == 1) {
        rook1->init(4,4);
        pawn1->init(2,4);
    } else if (side == 2) {
        rook1->init(4,1);
        pawn1->init(5,1);
    }
    number = side;
    pieces.push_back(pawn1);
    pieces.push_back(rook1);
}
