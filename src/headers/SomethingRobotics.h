#ifndef SOMETHINGROBOTICS_H
#define SOMETHINGROBOTICS_H

#include "bomb.h"
#include "flee.h"

// Defining the states
enum STATES{
    MOVE,
    ATTACK,
    FLEE,
    BOMB,
};

STATES currState = STATES::MOVE;

inline void command(Gladiator* gladiator){
    if (gladiator->weapon->getBombCount() > 0){
        currState = STATES::BOMB;
    }
    printf("%d\n", currState);
    if (currState == STATES::MOVE){
        move(gladiator);
    }
    else if (currState == STATES::ATTACK){
        
    }
    else if (currState == STATES::FLEE){
        currState = (STATES) flee(gladiator);
    }
    else if (currState == STATES::BOMB) {
        currState = (STATES) dropBombAndFlee(gladiator);
    }
}

#endif