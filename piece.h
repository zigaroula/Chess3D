#ifndef PIECE_H
#define PIECE_H

enum type{KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN};

class Piece
{
    public:
        Piece();
        void init(int, int, int);
        virtual ~Piece();
        bool canMoveTo(int, int);
        void moveTo(int, int);
    private:
        int posX;
        int posY;
        int type;
};

#endif // PIECE_H
