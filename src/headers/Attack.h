#ifndef ATTACK_H
#define ATTACK_H

#include <gladiator.h>
#include "./headers/tools.h"


// Function to decide when to attack a robot
inline void attack(Gladiator* gladiator , Gladiator* gladiatorAdv){  
    RobotData gladiatorData = gladiator->robot->getData();
    RobotData gladiatorAdvData = gladiator->robot->getData();  

    // Move aggressively in high spedd when near target
    if (distanceTwoRobots(gladiatorData, gladiatorAdvData) <  1){
        moveAgress(gladiator);
    }

    return;
}

// Funciton to speed up and hit the robot
inline void moveAgress(Gladiator* gladiator){
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.9);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.9);
}

#endif