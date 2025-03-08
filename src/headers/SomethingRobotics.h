#ifndef SOMETHINGROBOTICS_H
#define SOMETHINGROBOTICS_H

#include "bomb.h"

// Defining the states
enum class STATES{
    MOVE,
    ATTACK,
    FLEE,
    BOMB,
};

STATES currState = STATES::MOVE;

inline void command(Gladiator* gladiator){
    if (currState == STATES::MOVE){
        StateMove nextState = control(gladiator);
        if (nextState == StateMove::BOMB) {
            currState = STATES::BOMB;
        }
    }
    else if (currState == STATES::ATTACK){
        
    }
    else if (currState == STATES::FLEE){
    }
    else if (currState == STATES::BOMB) {
        dropBombAndFlee(gladiator);
        currState = STATES::MOVE;
    }
}

#endif