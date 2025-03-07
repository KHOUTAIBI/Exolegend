#include "gladiator.h"
#include "./headers/Attack.h"
#include "./headers/SomethingRobotics.h"

Gladiator *gladiator;
Gladiator *othergladiator;
RobotData gadiatorData; // data of the robots
RobotData othergladiatorData;

void reset();
void setup(){
    gladiator = new Gladiator(); //gladiator 1, friendly
    gladiator->game->onReset(&reset); // GFA 4.4.1
    gladiator->weapon->initWeapon(WeaponPin::M1, WeaponMode::SERVO); //Sertting the weapong mode of the robot to servo
}

void reset(){
    gladiator->log("Call of reset function"); // GFA 4.5.1
}

void loop(){
    if (gladiator->game->isStarted()){
        gladiator->log("Game has begun"); // GFA 4.5.1
        gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.2); 
        gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.2);
        attack(gladiator, 20);
    }
    else{
        gladiator->log("Game has not Startd yet"); // GFA 4.5.1
    }

    delay(300);
}
