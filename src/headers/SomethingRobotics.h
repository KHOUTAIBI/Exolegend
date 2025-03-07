#ifndef SOMETHINGROBOTICS_H
#define SOMETHINGROBOTICS_H

#include <algorithm>
#include <cstdio>
#include <iostream>
#include "gladiator.h"
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

inline void command(Gladiator * gladiator){
    
    if (currState == STATES::MOVE){
        
    }
    else if (currState == STATES::ATTACK){
        
    }
    else if (currState == STATES::FLEE){
        flee(gladiator, currState);
    }
    else if (currState == STATES::BOMB) {
        dropbomb(gladiator, currState);
    }
}


#endif