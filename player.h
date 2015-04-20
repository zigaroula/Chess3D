#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

class Player
{
    public:
        Player();
        virtual ~Player();
        void init(int side);
        void init(int side, const std::vector<Piece *> &_pieces);
        void loose();
        void win();
        std::vector<Piece*> getPieces() const { return pieces; }
        Piece * getPieceByVao(int VaoId);
        Piece* getKing() const { return king; }
        ///Calcule les mouvements disponibles pour toutes les pièces du joueur
        void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);

        ///DEBUGGING
        void initDebug(int);

    private:
        ///Numéro du joueur
        int number;
        ///Liste des pièces du joueur
        std::vector<Piece*> pieces;
        Pawn *pawn1, *pawn2, *pawn3, *pawn4, *pawn5, *pawn6, *pawn7, *pawn8;
        Rook *rook1, *rook2;
        Knight *knight1, *knight2;
        Bishop *bishop1, *bishop2;
        Queen *queen;
        King *king;
};

#endif // PLAYER_H
