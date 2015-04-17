#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
enum type{KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN};

class Piece
{
    public:
        Piece();
        void init(int, int, int);
        virtual ~Piece();
        ///Renvoie true si la pièce peut aller sur la case
        bool canMoveTo(int, int);
        ///Déplace la pièce
        void moveTo(int, int);
        std::vector<std::vector<int> > getAvailableMovements() { return availableMovements; }
        std::vector<int> getPosition() { return std::vector<int>(posX, posY); }
        ///Calcule l'ensemble des mouvements d'une pièce
        void computeAvailableMovements(std::vector<Piece>, std::vector<Piece>);
    private:
        int posX;
        int posY;
        ///Nature de la pièce
        int type;
        ///Liste des mouvements disponibles
        std::vector<std::vector<int> > availableMovements;
};

#endif // PIECE_H
