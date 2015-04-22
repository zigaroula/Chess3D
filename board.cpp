#include "board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Board::Board(){

}

Board::~Board() {

}

std::vector<Piece *> Board::initPieceFromFile(int side)
{
    std::vector<Piece *> pieces;
    std::string line;
    std::ifstream myfile;
    myfile.open("save.txt");
    
    std::getline(myfile, line);
    while(std::getline(myfile, line))
    {
        std::istringstream iss(line);
        std::string playerId, pieceName, x, y;
        
        std::getline(iss, playerId, ' ');
        std::getline(iss, pieceName, ' ');
        std::getline(iss, x, ' ');
        std::getline(iss, y, ' ');
        
        if (std::stoi(playerId) == side)
        {
            Piece *piece = nullptr;
            
            if (pieceName == "King") {
                piece = new King();
                
            } else if (pieceName == "Bishop")
                piece = new Bishop();
            else if (pieceName == "Knight")
                piece = new Knight();
            else if (pieceName == "Pawn")
                piece = new Pawn(side);
            else if (pieceName == "Queen")
                piece = new Queen();
            else if (pieceName == "Rook")
                piece = new Rook();
            
            piece->init(std::stoi(x), std::stoi(y));
            pieces.push_back(piece);
        }
    }
    
    return pieces;
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
    
    return pieces;
}

std::vector<std::vector<Piece *> > Board::initWithFile(Scene * _scene, std::string filename) {
    
    scene=_scene;
    
    std::vector<std::vector<Piece *> > pieces;
    
    pieces.resize(2);
    pieces[0] = initPieceFromFile(1);
    pieces[1] = initPieceFromFile(2);
    
    std::vector<std::string> model; std::vector<int> team ; std::vector<glm::vec3> pos ;
    
    for (int i = 0; i<2; i++){
        for (int j = 0; j<pieces[i].size(); j++){
            
            model.push_back(pieces[i][j]->getModelPath());
            team.push_back(i+1);
            pos.push_back(getPosAt(pieces[i][j]->getPosition()));
        }
    }

    std::vector<int> vaoIDs = scene->addVaoPiecesLoadedGame(model, team, pos);
    
    for (int i = 0; i<2; i++){
        for (int j = 0; j<pieces[i].size(); j++){
            int indice = (i*16) + j ;
            pieces[i][j]->setVaoID(vaoIDs[indice]);
            vaoIDsMap[vaoIDs[indice]] = pieces[i][j];
        }
    }
    
    return pieces;
}

std::vector<std::vector<Piece *> > Board::initClassic(Scene * _scene) {

    scene=_scene;
    computeAllSquares();

    std::vector<std::vector<Piece *> > pieces;

    pieces.push_back(initPiece(1));
    pieces.push_back(initPiece(2));

    std::vector<std::string> model; std::vector<int> team ; std::vector<glm::vec3> pos ;

    for (int i = 0; i<2; i++){
        for (int j = 0; j<16; j++){

            model.push_back(pieces[i][j]->getModelPath());
            team.push_back(i+1);
            pos.push_back(getPosAt(pieces[i][j]->getPosition()));
        }
    }

    std::vector<int> vaoIDs = scene->addVaoPieces(model,team,pos);

    for (int i = 0; i<2; i++){
        for (int j = 0; j<16; j++){
            int indice = (i*16) + j ;
            pieces[i][j]->setVaoID(vaoIDs[indice]);
            vaoIDsMap[vaoIDs[indice]] = pieces[i][j];
        }
    }

    return pieces;
}

glm::vec3 Board::computeRealPosition(int i, int j){
    return centerToSquare0 + glm::vec3(j*squareOffset, 0.0f, i*squareOffset);
}

void Board::computeAllSquares(){

    squares = std::vector<std::vector<glm::vec3> >(8);
    for(int i=0; i < 8; i++){
        squares[i].resize(8);
        for(int j=0; j <8; j++)
            squares[i][j] = computeRealPosition(i,j);
    }

}
void Board::movePieceTo(int vao, int i, int j){
    Piece * piece = vaoIDsMap[vao];

    if (piece == nullptr) throw std::string("La piece demandée n'existe pas");

    if(piece->getName() == "Knight"){
        scene->jumpVAOTo(vao -1, getPosAt(i,j));
    }else{
        scene->slideVAOTo(vao - 1,getPosAt(i,j));
    }

    //ejectPieceAt(i,j);

    piece->moveTo(i,j);

}

void Board::ejectPieceAt(int x, int y) {
    Piece * piece;
    for (unsigned int i = 1 ; i < vaoIDsMap.size() ; i++) {
        std::cout << "segfault" << std::endl;
        piece = vaoIDsMap[i];
        std::vector<int> position;
        position[0] = x;
        position[1] = y;
        if (piece->getPosition()[0] == position[0] && piece->getPosition()[1] == position[1]) {
            scene->jumpVAOTo(i -1, getPosAt(x+2,y+2));
        }
    }
}
