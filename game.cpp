#include "game.h"

void Game::tryMovement(int vaoId, int caseX, int caseY)
{

    std::cout << "Player " << turn << " selected vao" << vaoId << " and clicked on cell (" << caseX << "," << caseY << ")" <<  std::endl;
    Player &current = (turn == 1)?player1:player2;
    
    Piece *current_piece = current.getPieceByVao(vaoId);
    
    if (current_piece != nullptr)
    {

        std::cout << current_piece->getPosition()[0] << ";" << current_piece->getPosition()[1] << std::endl;
        
        if (current_piece->canMoveTo(caseX, caseY))
        {
            std::cout  << "--> Mouvement valide" << std::endl;
            board.movePieceTo(current_piece->getVaoID(), caseX, caseY);
        }
        else
        {
            std::cout  << "--> Mouvement non valide" << std::endl;
            std::cout << "Mouvements possibles:" << std::endl;
            const std::vector<std::vector<int>> &mvts = current_piece->getAvailableMovements();
            for (auto a : mvts)
                std::cout << a[0] << ";" << a[1] << std::endl;
        }
    }
    

}

void Game::initClassicGame(Scene * _scene) {


    std::vector<std::vector<Piece *> > pieces;
    pieces = board.initClassic(_scene);

    none.init(0);
    player1.init(1, pieces[0]);
    player2.init(2, pieces[1]);

    turn = 1;
    computeAvailableMovements();

    //testDebug();
}

void Game::loadFromFile() {

}

void Game::saveToFile() {

}

Player Game::check() {
    for (unsigned int i = 0 ; i < player1.getPieces().size() ; i++) {
        for (unsigned int j = 0 ; j < player1.getPieces()[i]->getAvailableMovements().size() ; j++) {
            if (player1.getPieces()[i]->getAvailableMovements()[j] == player2.getKing()->getPosition()) {
                return player2;
            }
        }
    }

    for (unsigned int i = 0 ; i < player2.getPieces().size() ; i++) {
        for (unsigned int j = 0 ; j < player2.getPieces()[i]->getAvailableMovements().size() ; j++) {
            if (player2.getPieces()[i]->getAvailableMovements()[j] == player1.getKing()->getPosition()) {
                return player1;
            }
        }
    }

    return none;
}

Player Game::checkMate() { //trop compliqué
    /*int cM = 0;
    bool c = false;
    for (unsigned int k = 0 ; k < player2.getKing().getAvailableMovements().size() ; k++) {
        for (unsigned int i = 0 ; i < player1.getPieces().size() ; i++) {
            for (unsigned int j = 0 ; j < player1.getPieces()[i].getAvailableMovements().size() ; j++) {
                if (player1.getPieces()[i].getAvailableMovements()[j] == player2.getKing().getAvailableMovements()[k]) {
                    c = true;
                }
            }
        }
        if (c) {
            cM++;
        }
        c = false;
    }
    if (cM = )

    cM = 0;
    c = false;
    for (unsigned int k = 0 ; k < player1.getKing().getAvailableMovements().size() ; k++) {
        for (unsigned int i = 0 ; i < player2.getPieces().size() ; i++) {
            for (unsigned int j = 0 ; j < player2.getPieces()[i].getAvailableMovements().size() ; j++) {
                if (player2.getPieces()[i].getAvailableMovements()[j] == player1.getKing().getAvailableMovements()[k]) {
                    c = true;
                }
            }
        }
        if (c) {
            cM++;
        }
        c = false;
    }*/
    return none;
}

void Game::changeTurn() {
    if (turn == 1) {
        turn = 2;
    } else {
        turn = 1;
    }
    player1.computeAvailableMovements(player1.getPieces(), player2.getPieces());
    player2.computeAvailableMovements(player2.getPieces(), player1.getPieces());
}

void Game::computeAvailableMovements() {
    player1.computeAvailableMovements(player1.getPieces(), player2.getPieces());
    player2.computeAvailableMovements(player1.getPieces(), player2.getPieces());
}

void Game::testDebug() {
    std::vector<Piece*> pieces = player1.getPieces();
    std::vector<std::vector<int> > debugMovements = pieces[0]->getAvailableMovements();
    std::cout << std::endl << "AVAILABLE MOVEMENTS" << std::endl;
    for (unsigned int i = 0 ; i < debugMovements.size() ; i++) {
        std::cout << debugMovements[i][0] << " " << debugMovements[i][1] << std::endl;
    }
}
