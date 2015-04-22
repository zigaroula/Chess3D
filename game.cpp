#include "game.h"
#include <fstream>

void Game::tryMovement(int vaoId1, int vaoId2)
{
    Player &current2 = (turn == 2)?player1:player2;
    Piece  *piece_joueur2 = current2.getPieceByVao(vaoId2);
    
    if (piece_joueur2 != nullptr)
    {
        tryMovement(vaoId1, piece_joueur2->getPosition()[0], piece_joueur2->getPosition()[1]);
    }
}
void Game::tryMovement(int vaoId, int caseX, int caseY)
{
    Player &current = (turn == 1)?player1:player2;
    Piece *current_piece = current.getPieceByVao(vaoId);

    if (current_piece != nullptr)
    {
        std::cout << "--> Player " << turn << " selected vao" << vaoId << "(" << current_piece->getPosition()[0] << ";" << current_piece->getPosition()[1] << ") and clicked on cell (" << caseX << "," << caseY << ")" <<  std::endl;

        if (current_piece->canMoveTo(caseX, caseY))
        {
            std::cout  << "\tMouvement valide, Mouvements possibles:";
            board.movePieceTo(current_piece->getVaoID(), caseX, caseY);
            //board.ejectPieceAt(caseX, caseY);
            changeTurn();
        }
        else
            std::cout  << "\tMouvement non valide, Mouvements possibles:";

        const std::vector<std::vector<int>> &mvts_possibles = current_piece->getAvailableMovements();
        for (auto a : mvts_possibles)
            std::cout << "(" << a[0] << "," << a[1] << ");";
        
        std::cout << std::endl;
    }
    else
        std::cout << "--> Player " << turn << " selected vao" << vaoId << " and clicked on cell (" << caseX << "," << caseY << ") VAO NULLPOINTER" <<  std::endl;
}

void Game::initClassicGame(Scene * _scene) {

    /*  Créer une nouvelle partie normale */

    scene = _scene;

    std::vector<std::vector<Piece *> > pieces;
    pieces = board.initClassic(_scene);

    none.init(0);
    player1.init(1, pieces[0]);
    player2.init(2, pieces[1]);

    turn = 1;
    computeAvailableMovements();

    //testDebug();
}

void Game::loadFromFile(Scene *_scene) {
    ///Recharge une partie précédente
    std::cout << "Opening a previous game..." << std::endl;
    
    std::vector<std::vector<Piece *> > pieces;
    pieces = board.initWithFile(_scene, "save.txt");
    
    none.init(0);
    player1.init(1, pieces[0]);
    player2.init(2, pieces[1]);
    
    std::string line;
    std::ifstream myfile;
    myfile.open("save.txt");
    
    myfile >> line;
    
    _scene->unselect();
    turn = std::stoi(line);
    
    computeAvailableMovements();
}

void Game::saveToFile() {
    ///Sauvegarde la partie en cours
    std::cout << "Saving the game..." << std::endl;
    
    std::ofstream myfile;
    myfile.open("save.txt");
 
    myfile << turn << std::endl;
    
    for (Piece *piece : player1.getPieces())
        myfile << "1 " << piece->getName() << " " << piece->getPosition()[0] << " " << piece->getPosition()[1] << std::endl;
    
    for (Piece *piece : player2.getPieces())
        myfile << "2 " << piece->getName() << " " << piece->getPosition()[0] << " " << piece->getPosition()[1] << std::endl;
    
    myfile.close();
}

bool Game::check(Player player, Player opponent, std::vector<int> KingPos) {

    for (unsigned int i = 0 ; i < opponent.getPieces().size() ; i++) {
        for (unsigned int j = 0 ; j < opponent.getPieces()[i]->getAvailableMovements().size() ; j++) {
            std::vector<int> checkSquare = opponent.getPieces()[i]->getAvailableMovements()[j];
            if ( checkSquare[0] == KingPos[0] && checkSquare[1] == KingPos[1] ) {
                return true;
            }
        }
    }
    return false;
}

bool Game::checkMate(Player player, Player opponent) {

    std::vector<int> tempPos = player.getKing()->getPosition();

    for (unsigned int j = 0 ; j < player.getKing()->getAvailableMovements().size() ; j++) {
        std::vector<int> kingPos = player.getKing()->getAvailableMovements()[j] ;
        player.getKing()->moveTo(kingPos[0], kingPos[1]);
        opponent.computeAvailableMovements(opponent.getPieces(), player.getPieces());
        if(!(check(player, opponent,player.getKing()->getAvailableMovements()[j]) )){
            std::cout << "\nPas en échec sur " << player.getKing()->getAvailableMovements()[j][0] << " : " << player.getKing()->getAvailableMovements()[j][1] << std::endl;
            return false;
        }
    }
     player.getKing()->moveTo(tempPos[0], tempPos[1]);
     opponent.computeAvailableMovements(opponent.getPieces(), player.getPieces());
    return true;
}

void Game::changeTurn() {
    /* Change le joueur en cours */
    turn = (turn == 1)?2:1;
    
    player1.computeAvailableMovements(player1.getPieces(), player2.getPieces());
    player2.computeAvailableMovements(player2.getPieces(), player1.getPieces());

    scene->unselect();


    if(turn == 1){

        bool checkState = check(player1, player2, player1.getKing()->getPosition());
        if (checkState){
            std::cout << "\nJoueur 1, vous êtes en échec !" << std::endl;
            if(checkMate(player1, player2)) endGame(2);
        }
    }else if (turn == 2){
        bool checkState = check(player2, player1, player2.getKing()->getPosition());
        if (checkState){
            std::cout << "\nJoueur 2, vous êtes en échec !" << std::endl;
            if(checkMate(player2, player1)) endGame(1);
        }
    }



}

void Game::computeAvailableMovements() {
    /* Calcule les mouvements disponibles pour toutes les pièces */
    player1.computeAvailableMovements(player1.getPieces(), player2.getPieces());
    player2.computeAvailableMovements(player2.getPieces(), player1.getPieces());
}

void Game::testDebug() {
    std::vector<Piece*> pieces = player1.getPieces();
    std::vector<std::vector<int> > debugMovements = pieces[0]->getAvailableMovements();
    std::cout << std::endl << "AVAILABLE MOVEMENTS" << std::endl;
    for (unsigned int i = 0 ; i < debugMovements.size() ; i++) {
        std::cout << debugMovements[i][0] << " " << debugMovements[i][1] << std::endl;
    }
}
void Game::endGame(int winner){

    std::cout << "\nLe joueur " << winner << " remporte la partie ! ";

}
