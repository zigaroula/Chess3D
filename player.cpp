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

    for(unsigned int i =0; i < pieces.size() ; i++){
        std::cerr << std::endl << pieces[i]->getName() <<", numero " << pieces[i]->getVaoID() << std::endl;
        if(pieces[i]->getName() == "King" ) {
            king = (King *) pieces[i];
            //break;
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



Piece * Player::getPieceByVao(int VaoId){
    for(unsigned int i =0; i < pieces.size() ;i++){
        if(pieces[i]->getVaoID() == VaoId){
            return pieces[i];
        }
    }

    return nullptr;
}
