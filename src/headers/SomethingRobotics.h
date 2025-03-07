#ifndef SOMETHINGROBOTICS_H
#define SOMETHINGROBOTICS_H

#include <algorithm>
#include <cstdio>
#include <iostream>

#include "gladiator.h"
#include "headers/Attack.h"

// Defining the states and pins
enum STATES{
    MOVE,
    ATTACK,
    FLEE,
    BOMB,
};


STATES currState = STATES::MOVE;

inline void command(Gladiator* gladiator){
    if (currState == STATES::MOVE){
        
    }
    else if (currState == STATES::ATTACK){
        
    }
    else if (currState == STATES::FLEE){
        
    }
    else if (currState == STATES::BOMB) {

    }
}




#endif