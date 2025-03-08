    #include "gladiator.h"
#include "./headers/SomethingRobotics.h"

Gladiator *gladiator; // init gladiator
RobotData gadiatorData; // data of the robots

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
        
        // gladiator->log("Game has begun"); // GFA 4.5.1
        command(gladiator);
    }
    else{
        // gladiator->log("Game has not Startd yet"); // GFA 4.5.1
    }

    delay(300);
}
