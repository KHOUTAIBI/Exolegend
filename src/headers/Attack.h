#ifndef ATTACK_H
#define ATTACK_H

#include <gladiator.h>
#include "./headers/tools.h"



// Funciton to speed up and hit the robot
inline void moveAgress(Gladiator* gladiator){

    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.9);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.9);

}


// Function to decide when to attack a robot
inline void attack(Gladiator* gladiator , byte adverId){  

    // getting position data
    Position gladiatorPosition = gladiator->robot->getData().position;
    Position gladiatorAdvposition = gladiator->game->getOtherRobotData(adverId).position;  

    go_to(gladiator,gladiatorPosition,gladiatorAdvposition);

    float alphaGlad = gladiatorPosition.a;
    float alphaAdvGlad = gladiatorAdvposition.a;
    
    // Move aggressively in high speed when near target and the difference in angle < 50
    // TO CHANGE
    if (distanceTwoRobots(gladiatorPosition, gladiatorAdvposition) <  0.001 && abs(alphaGlad - alphaAdvGlad) < 10){
        moveAgress(gladiator);
    }
}

#endif