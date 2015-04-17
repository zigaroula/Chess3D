#include "game.h"

Game::Game() {

}

void Game::initClassicGame() {
    none.init(0);
    player1.init(1);
    player2.init(2);
    turn = 1;
}

void Game::loadFromFile() {

}

void Game::saveToFile() {

}

Player Game::check() {
    for (unsigned int i = 0 ; i < player1.getPieces().size() ; i++) {
        for (unsigned int j = 0 ; j < player1.getPieces()[i].getAvailableMovements().size() ; j++) {
            if (player1.getPieces()[i].getAvailableMovements()[j] == player2.getKing().getPosition()) {
                return player2;
            }
        }
    }

    for (unsigned int i = 0 ; i < player2.getPieces().size() ; i++) {
        for (unsigned int j = 0 ; j < player2.getPieces()[i].getAvailableMovements().size() ; j++) {
            if (player2.getPieces()[i].getAvailableMovements()[j] == player1.getKing().getPosition()) {
                return player1;
            }
        }
    }

    return none;
}

Player Game::checkMate() { ///trop compliqué
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
