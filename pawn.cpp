#include "pawn.h"

Pawn::Pawn(int side) {
    if (side == 1) {
        d = -1;
    } else if (side == 2) {
        d = 1;
    }
}

void Pawn::computeAvailableMovements(std::vector<Piece*> own, std::vector<Piece*> opp) {
    std::vector<int> pos = std::vector<int>();
    pos.resize(2);
    bool found = false;

    pos[0] = posX+d;
    pos[1] = posY;
    for (unsigned int i = 0 ; i < own.size() ; i++) {
        if (own[i]->getPosition()[0]==pos[0] && own[i]->getPosition()[1]==pos[1]) {
            found = true;
        }
    }
    for (unsigned int j = 0 ; j < opp.size() ; j++) {
        if (opp[j]->getPosition()[0]==pos[0] && opp[j]->getPosition()[1]==pos[1]) {
            found = true;
        }
    }
    if (!found && pos[0]>=0 && pos[0]<8 && pos[1]>=0 && pos[1]<8) {
        availableMovements.push_back(pos);
        if ((d==-1 && posX==6)||(d==1 && posX==1)) {
            pos[0] = posX+2*d;
            pos[1] = posY;
            for (unsigned int i = 0 ; i < own.size() ; i++) {
                if (own[i]->getPosition()[0]==pos[0] && own[i]->getPosition()[1]==pos[1]) {
                    found = true;
                }
            }
            for (unsigned int j = 0 ; j < opp.size() ; j++) {
                if (opp[j]->getPosition()[0]==pos[0] && opp[j]->getPosition()[1]==pos[1]) {
                    found = true;
                }
            }
            if (!found && pos[0]>=0 && pos[0]<8 && pos[1]>=0 && pos[1]<8) {
                availableMovements.push_back(pos);
            }
        }
    }

    pos[0] = posX+d;
    pos[1] = posY+1;
    for (unsigned int j = 0 ; j < opp.size() ; j++) {
        if (opp[j]->getPosition()[0]==pos[0] && opp[j]->getPosition()[1]==pos[1]) {
            availableMovements.push_back(pos);
        }
    }

    pos[0] = posX+d;
    pos[1] = posY-1;
    for (unsigned int j = 0 ; j < opp.size() ; j++) {
        if (opp[j]->getPosition()[0]==pos[0] && opp[j]->getPosition()[1]==pos[1]) {
            availableMovements.push_back(pos);
        }
    }

}
