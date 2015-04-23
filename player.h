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
        void deletePieceAt(std::vector<int>);
        void deletePieces();


    private:
        ///Numéro du joueur
        int number;
        ///Liste des pièces du joueur
        std::vector<Piece*> pieces;
        ///une référence directe vers le roi
        King *king;
};

#endif // PLAYER_H
