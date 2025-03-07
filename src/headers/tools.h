#ifndef TOOLS_H
#define TOOLS_H

#include <gladiator.h>
#include <vector>

#define ID1 37
#define ID2 40 

// norm function, tool to be used later
float normRobot(float x, float y){
    return std::sqrt(
        pow(x,2) + pow(y,2)
    );
}

// funciton returning distance between two robots
float distanceTwoRobots(Position gladiatorPos, Position gladiatorAdvPos){

    return normRobot(
        gladiatorPos.x - gladiatorAdvPos.x,
        gladiatorPos.y - gladiatorAdvPos.y
    );
}




#endif