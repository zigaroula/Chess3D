#include "bishop.h"

void Bishop::computeAvailableMovements(std::vector<Piece> own, std::vector<Piece> opp) {
    std::vector<int> pos = std::vector<int>(posX+1, posY+1);
    bool found = false;
    while(pos[0]<8 && pos[1]<8 && !found) {
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            if (own[i].getPosition()[0]==pos[0] && own[i].getPosition()[1]==pos[1]) {
                found = true;
            }
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            if (opp[j].getPosition()[0]==pos[0] && opp[j].getPosition()[1]==pos[1]) {
                availableMovements.push_back(pos);
                found = true;
            }
        }
        if (!found) {
            availableMovements.push_back(pos);
        }
        pos[0]++;
        pos[1]++;
    }
    pos = std::vector<int>(posX-1, posY+1);
    found = false;
    while(pos[0]>0 && pos[1]<8) {
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            if (own[i].getPosition()[0]==pos[0] && own[i].getPosition()[1]==pos[1]) {
                found = true;
            }
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            if (opp[j].getPosition()[0]==pos[0] && opp[j].getPosition()[1]==pos[1]) {
                availableMovements.push_back(pos);
                found = true;
            }
        }
        if (!found) {
            availableMovements.push_back(pos);
        }
        pos[0]--;
        pos[1]++;
    }
    pos = std::vector<int>(posX+1, posY-1);
    found = false;
    while(pos[0]<8 && pos[1]>0) {
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            if (own[i].getPosition()[0]==pos[0] && own[i].getPosition()[1]==pos[1]) {
                found = true;
            }
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            if (opp[j].getPosition()[0]==pos[0] && opp[j].getPosition()[1]==pos[1]) {
                availableMovements.push_back(pos);
                found = true;
            }
        }
        if (!found) {
            availableMovements.push_back(pos);
        }
        pos[0]++;
        pos[1]--;
    }
    pos = std::vector<int>(posX-1, posY-1);
    found = false;
    while(pos[0]>0 && pos[1]>0) {
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            if (own[i].getPosition()[0]==pos[0] && own[i].getPosition()[1]==pos[1]) {
                found = true;
            }
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            if (opp[j].getPosition()[0]==pos[0] && opp[j].getPosition()[1]==pos[1]) {
                availableMovements.push_back(pos);
                found = true;
            }
        }
        if (!found) {
            availableMovements.push_back(pos);
        }
        pos[0]--;
        pos[1]--;
    }
}
