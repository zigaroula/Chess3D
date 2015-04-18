#include "board.h"

Board::Board() {

}

Board::~Board() {

}

void Board::init() {

    computeAllSquares();
}

glm::vec3 Board::computeRealPosition(int i, int j){
    return centerToSquare0 + glm::vec3(i*squareOffset , 0.0f, j*squareOffset);
}

void Board::computeAllSquares(){

    squares = std::vector<std::vector<glm::vec3> >(8);
    for(int i=0; i < 7; i++){
        squares[i] = std::vector<glm::vec3> (8);
        for(int j=0; j <7; j++)
            squares[i][j] = computeRealPosition(i,j);
    }
}
