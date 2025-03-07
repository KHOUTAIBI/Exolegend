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

// Function which returns the distances to all robots
float* distanceToAllAdvs(Gladiator* gladiator){

    float distancesToAdvs[2];
    uint8_t* Listids[4];

    for (int i = 0; i < 4; i++){
        if (Listids[i] != ID1 && Listids[i] != ID2){
            distancesToAdvs[i] = distanceTwoRobots(gladiator->robot->getData().position, gladiator->game->getOtherRobotData(Listids[i]).position);
        }
    }

    // sorting an easily sortable array
    if (distancesToAdvs[1] <= distancesToAdvs[0]){
        distancesToAdvs[0] = distancesToAdvs[1];
    }

    return &distancesToAdvs[0];
}


#endif