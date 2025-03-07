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
float distanceTwoRobots(RobotData gladiatorData, RobotData gladiatorAdvData){

    return normRobot(
        gladiatorData.position.x - gladiatorAdvData.position.x,
        gladiatorData.position.y - gladiatorAdvData.position.y
    );
}

// Function returning array of position from a robot to all adversaries
// Not using vectors in order to save memory, mallocing fout floats is better
float* distanceToAllAdv(Gladiator* gladiator,Gladiator* friendlygladiator){
    
    RobotList listAdv = gladiator->game->getPlayingRobotsId();
    RobotData gladiatorData = gladiator->robot->getData();
    RobotData firendlygladData = gladiator->robot->getData();
    float distancesTogladiator[4];

    // First appending the gladiator data

    for (int i = 0; i < 4; i++){
        if (listAdv.ids[i] != ID1 && listAdv.ids[i] != ID2){  
            
            distancesTogladiator[i] = distanceTwoRobots(
                gladiatorData,
                gladiator->game->getOtherRobotData(listAdv.ids[i])
            );

        }
    }

    // Then appending the adversary
    for (int i = 0; i < 4; i++){
        if (listAdv.ids[i] != ID1 && listAdv.ids[i] != ID2){  
            
            distancesTogladiator[i] = distanceTwoRobots(
                firendlygladData,
                gladiator->game->getOtherRobotData(listAdv.ids[i])
            );

        }
    }

    return &distancesTogladiator[0]; 
}


#endif