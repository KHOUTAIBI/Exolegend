#include "gladiator.h"
#include "headers/SomethingRobotics.h"

Gladiator *gladiator; // init gladiator
RobotData gadiatorData; // data of the robots

void reset();
void setup(){
    gladiator = new Gladiator(); //gladiator 1, friendly
    gladiator->game->onReset(&reset); // GFA 4.4.1
    gladiator->weapon->initWeapon(WeaponPin::M1, WeaponMode::SERVO); //Sertting the weapong mode of the robot to servo
    if(gladiator->robot->getData().id == 37){
        gladiator->robot->setCalibrationOffset(0.0103, -0.0053, 0);
    }
    if(gladiator->robot->getData().id == 40){
        gladiator->robot->setCalibrationOffset(0.0111, -0.0037, 0);
    }
    
}

void reset(){
    gladiator->log("Call of reset function"); // GFA 4.5.1
    nearestPOI = { -1, -1, -1};
    while (!toGo.empty()) toGo.pop();
    lastPos = { 0, 0, 0 };
    mazeSize = -1;
}

void loop(){
    
    if (gladiator->game->isStarted()){
        // gladiator->log("Game has begun"); // GFA 4.5.1
        command(gladiator);
    }
    else{
        // gladiator->log("Game has not Startd yet"); // GFA 4.5.1
    }

    delay(300);
}
