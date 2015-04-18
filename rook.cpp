#include "rook.h"

void Rook::computeAvailableMovements(std::vector<Piece*> own, std::vector<Piece*> opp) {
    std::vector<int> pos = std::vector<int>();
    pos.resize(2);
    pos[0] = posX+1;
    pos[1] = posY;
    std::cout << "Debut : " << pos[0] << " " <<  pos[1] << std::endl;
    bool found = false;
    //std::cout << "bishop" << std::endl;
    while(pos[0]<8 && !found) {
    std::cout << pos[0] << " " <<  pos[1] << std::endl;
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            if (own[i]->getPosition()[0]==pos[0] && own[i]->getPosition()[1]==pos[1]) {
                //std::cout << own[i]->getPosition()[0] << " " <<  own[i]->getPosition()[1] << std::endl;
                found = true;
            }
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            if (opp[j]->getPosition()[0]==pos[0] && opp[j]->getPosition()[1]==pos[1]) {
                availableMovements.push_back(pos);
                std::cout << "Ajout : " << pos[0] << " " <<  pos[1] << std::endl;
                found = true;
            }
        }
        if (!found) {
            availableMovements.push_back(pos);
            std::cout << "Ajout : " << pos[0] << " " <<  pos[1] << std::endl;
        }
        pos[0]++;
    }
    pos[0] = posX-1;
    pos[1] = posY;
    std::cout << "Debut : " << pos[0] << " " <<  pos[1] << std::endl;
    found = false;
    while(pos[0]>=0 && !found) {
    std::cout << pos[0] << " " <<  pos[1] << std::endl;
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            if (own[i]->getPosition()[0]==pos[0] && own[i]->getPosition()[1]==pos[1]) {
                found = true;
            }
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            if (opp[j]->getPosition()[0]==pos[0] && opp[j]->getPosition()[1]==pos[1]) {
                availableMovements.push_back(pos);
                std::cout << "Ajout : " << pos[0] << " " <<  pos[1] << std::endl;
                found = true;
            }
        }
        if (!found) {
            availableMovements.push_back(pos);
            std::cout << "Ajout : " << pos[0] << " " <<  pos[1] << std::endl;
        }
        pos[0]--;
    }
    pos[0] = posX;
    pos[1] = posY+1;
    std::cout << "Debut : " << pos[0] << " " <<  pos[1] << std::endl;
    found = false;
    while(pos[1]<8 && !found) {
    std::cout << pos[0] << " " <<  pos[1] << std::endl;
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            if (own[i]->getPosition()[0]==pos[0] && own[i]->getPosition()[1]==pos[1]) {
                found = true;
            }
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            if (opp[j]->getPosition()[0]==pos[0] && opp[j]->getPosition()[1]==pos[1]) {
                availableMovements.push_back(pos);
                std::cout << "Ajout : " << pos[0] << " " <<  pos[1] << std::endl;
                found = true;
            }
        }
        if (!found) {
            availableMovements.push_back(pos);
            std::cout << "Ajout : " << pos[0] << " " <<  pos[1] << std::endl;
        }
        pos[1]++;
    }
    pos[0] = posX;
    pos[1] = posY-1;
    std::cout << "Debut : " << pos[0] << " " <<  pos[1] << std::endl;
    found = false;
    while(pos[1]>=0 && !found) {
    std::cout << pos[0] << " " <<  pos[1] << std::endl;
        for (unsigned int i = 0 ; i < own.size() ; i++) {
            if (own[i]->getPosition()[0]==pos[0] && own[i]->getPosition()[1]==pos[1]) {
                found = true;
            }
        }
        for (unsigned int j = 0 ; j < opp.size() ; j++) {
            if (opp[j]->getPosition()[0]==pos[0] && opp[j]->getPosition()[1]==pos[1]) {
                availableMovements.push_back(pos);
                std::cout << "Ajout : " << pos[0] << " " <<  pos[1] << std::endl;
                found = true;
            }
        }
        if (!found) {
            availableMovements.push_back(pos);
            std::cout << "Ajout : " << pos[0] << " " <<  pos[1] << std::endl;
        }
        pos[1]--;
    }
}
