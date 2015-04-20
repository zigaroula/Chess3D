#include "player.h"
#include <typeinfo>

Player::Player() {

}

Player::~Player() {

}

void Player::init(int side) {
    number = side;
}

void Player::init(int side,  std::vector<Piece *> const & _pieces) {

    number = side;
    pieces = _pieces;
    
    for (unsigned int i = 0; i < pieces.size() ; i++){
        if (typeid(*pieces[i]) == typeid(King())){

        }
    }


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
    king = new King();
    queen = new Queen();
    if (side == 1) {
        king->init(2,2);
        queen->init(2,3);
    } else if (side == 2) {
        king->init(2,1);
        queen->init(1,1);
    }
    number = side;
    pieces.push_back(king);
    pieces.push_back(queen);
}

Piece * Player::getPieceByVao(int VaoId){
    for(unsigned int i =0; i < pieces.size() ;i++){
        if(pieces[i]->getVaoID() == VaoId){
            return pieces[i];
        }
    }

    return nullptr;
}
