#include "gladiator.h"
#include "./headers/SomethingRobotics.h"

Gladiator *gladiator;
Gladiator *othergladiator;
RobotData gadiatorData; // data of the robots
RobotData othergladiatorData;

void reset();
void setup(){
    gladiator = new Gladiator(); //gladiator 1, friendly
    othergladiator = new Gladiator(); // gladiator 2, adversary
    gladiator->game->onReset(&reset); // GFA 4.4.1
    othergladiator->game->onReset(&reset);
    gladiator->weapon->initWeapon(WeaponPin::M1, WeaponMode::SERVO); //Sertting the weapong mode of the robot to servo
    othergladiator->weapon->initWeapon(WeaponPin::M1, WeaponMode::SERVO); //second robot
}

void reset(){
    gladiator->log("Call of reset function"); // GFA 4.5.1
}

void loop(){
    if (gladiator->game->isStarted()){
        
        gladiator->log("Game has begun"); // GFA 4.5.1
        // gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.2); 
        // gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.2); 
        gladiator->weapon->setTarget(WeaponPin::M1, 0);
        gladiator->weapon->setTarget(WeaponPin::M1, 100);
        gladiator->robot->getData();
        othergladiator->robot->getData();

        

    }
    else{
        gladiator->log("Game has not Startd yet"); // GFA 4.5.1
    }

    delay(300);
}
