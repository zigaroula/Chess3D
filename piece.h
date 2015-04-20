#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <string>

class Piece
{
    public:
        Piece();
        virtual void init(int, int);
        virtual ~Piece();
        virtual int getVaoID() const {return vaoID;}
        virtual void setVaoID(int _vaoID) {vaoID = _vaoID;}
        ///Renvoie true si la pièce peut aller sur la case
        bool canMoveTo(int, int);
        ///Déplace la pièce
        void moveTo(int, int);
        virtual std::string getModelPath() const{ return "";}
        std::vector<std::vector<int> > getAvailableMovements() { return availableMovements; }
        std::vector<int> getPosition();
        ///Calcule l'ensemble des mouvements d'une pièce
        virtual void computeAvailableMovements(std::vector<Piece*>, std::vector<Piece*>);


    protected:
        int posX;
        int posY;
        int vaoID;
        ///Liste des mouvements disponibles
        std::vector<std::vector<int> > availableMovements;
};

#endif // PIECE_H

