#include "board.h"
#include <iostream>

Board::Board(){

}

Board::~Board() {

}

std::vector<Piece *> Board::initPiece(int side){
    std::vector<Piece *> pieces;

    Piece * pawn1 = new Pawn(side);
    Piece * pawn2 = new Pawn(side);
    Piece * pawn3 = new Pawn(side);
    Piece * pawn4 = new Pawn(side);
    Piece * pawn5 = new Pawn(side);
    Piece * pawn6 = new Pawn(side);
    Piece * pawn7 = new Pawn(side);
    Piece * pawn8 = new Pawn(side);
    Piece * rook1 = new Rook();
    Piece * rook2 = new Rook();
    Piece * knight1 = new Knight();
    Piece * knight2 = new Knight();
    Piece * bishop1 = new Bishop();
    Piece * bishop2 = new Bishop();
    Piece * queen = new Queen();
    Piece * king = new King();

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

    for (int i = 0; i < pieces.size() ; i++){

    }

}

std::vector<std::vector<Piece *> > Board::initClassic(Scene * _scene) {

    scene=_scene;
    computeAllSquares();

   std::vector<std::vector<Piece *> > pieces =  std::vector<std::vector<Piece *> >(3);



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
