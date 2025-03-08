#ifndef SOMETHINGROBOTICS_H
#define SOMETHINGROBOTICS_H

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <gladiator.h>
#include "./headers/Attack.h"

// Defining the states
enum STATES{
    MOVE,
    ATTACK,
    FLEE,
    BOMB,
};


inline void command(Gladiator * gladiator, STATES& currState){
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