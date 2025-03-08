#ifndef TOOLS_H
#define TOOLS_H

#include "gladiator.h"
#include <vector>
#define ID1 37
#define ID2 40 

float kw = 1.2;
float kv = 1.f;
float wlimit = 3.f;
float vlimit = 0.6;
float erreurPos = 0.07;

double reductionAngle(double x);
void go_to(Gladiator * gladiator, Position cons, Position pos);


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
std::vector<float> distanceToAllAdvs(Gladiator* gladiator){

    std::vector<float> distancesToAdvs;
    uint8_t Listids[4] = {
        gladiator->game->getPlayingRobotsId().ids[0],
        gladiator->game->getPlayingRobotsId().ids[1],
        gladiator->game->getPlayingRobotsId().ids[2],
        gladiator->game->getPlayingRobotsId().ids[3]
    };

    for (int i = 0; i < 4; i++){
        if (Listids[i] != ID1 && Listids[i] != ID2){
            distancesToAdvs.push_back(distanceTwoRobots(gladiator->robot->getData().position, gladiator->game->getOtherRobotData(Listids[i]).position));
        }
    }

    // sorting an easily sortable array
    if (distancesToAdvs[1] <= distancesToAdvs[0]){
        distancesToAdvs[0] = distancesToAdvs[1];
    }

    return distancesToAdvs;
}


#endif
