#ifndef SOMETHINGROBOTICS_H
#define SOMETHINGROBOTICS_H

#include <algorithm>
#include <cstdio>
#include <iostream>

// Defining the states 
enum STATES{
    MOVE,
    ATTACK,
    FLEE,
    BOMB,
};

STATES currState = STATES::MOVE;

inline void command(){
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