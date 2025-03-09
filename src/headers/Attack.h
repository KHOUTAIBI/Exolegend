#ifndef ATTACK_H
#define ATTACK_H

#include <gladiator.h>
#include "./headers/tools.h"
#include "headers/movement.h"



// Funciton to speed up and hit the robot
inline void moveAgress(Gladiator* gladiator){

    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.9);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.9);

}


// Function to decide when to attack a robot
void attack(Gladiator* gladiator , byte adverId);

#endif