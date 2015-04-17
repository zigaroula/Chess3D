#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "piece.h"

class Player
{
    public:
        Player();
        virtual ~Player();
        void init(int);
        void loose();
        void win();
        std::vector<Piece> getPieces() const { return pieces; }
        Piece getKing() const { return pieces[15]; }
        ///Calcule les mouvements disponibles pour toutes les pièces du joueur
        void computeAvailableMovements(std::vector<Piece>, std::vector<Piece>);
    private:
        ///Numéro du joueur
        int number;
        ///Liste des pièces du joueur
        std::vector<Piece> pieces;
};

#endif // PLAYER_H
