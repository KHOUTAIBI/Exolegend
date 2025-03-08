#ifndef SOMETHINGROBOTICS_H
#define SOMETHINGROBOTICS_H

#include "move.h"

// Defining the states
enum STATES{
    MOVE,
    ATTACK,
    FLEE,
    BOMB,
};

STATES currState = STATES::MOVE;

inline void command(Gladiator* gladiator){
    if (currState == STATES::MOVE){
        move(gladiator);
    }
    else if (currState == STATES::ATTACK){
        
    }
    else if (currState == STATES::FLEE){
    
    }
    else if (currState == STATES::BOMB) {

    }
}

#endif