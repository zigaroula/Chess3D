#include "board.h"
#include <iostream>

Board::Board(){

}

Board::~Board() {

}

void Board::initClassic(Scene * _scene) {

    scene=_scene;
    computeAllSquares();

//##DEBUG
//    placerPion(0,0);
//    placerPion(7,7);
//    placerPion(0,7);


}

glm::vec3 Board::computeRealPosition(int i, int j){
    return centerToSquare0 + glm::vec3(i*squareOffset , 0.0f, j*squareOffset);
}

void Board::computeAllSquares(){

    squares = std::vector<std::vector<glm::vec3> >(8);
    for(int i=0; i < 8; i++){
        squares[i] = std::vector<glm::vec3> (8);
        for(int j=0; j <8; j++)
            squares[i][j] = computeRealPosition(i,j);
    }

}
//###DEBUG
void Board::placerPion(int i, int j){

    scene->addVaoPiece("models/pion.obj",1,getPosAt(i,j));
}
