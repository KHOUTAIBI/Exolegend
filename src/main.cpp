#include "gladiator.h"
#include "./headers/SomethingRobotics.h"

Gladiator *gladiator; // init gladiator
RobotData gadiatorData; // data of the robots
STATES currState = STATES::MOVE;

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
        uint8_t Listids[2] = {
            gladiator->game->getPlayingRobotsId().ids[0],
            gladiator->game->getPlayingRobotsId().ids[1],
        };

        gladiator->log("Game has begun"); // GFA 4.5.1
        std::vector<float> distances = distanceToAllAdvs(gladiator);
        gladiator->log("%f",distances[0]);
        gladiator->log("%f",distances[1]);
        if (gladiator->robot->getData().id != Listids[0]) attack(gladiator, Listids[0]);
        else attack(gladiator, Listids[1]);
    }
    else{
        gladiator->log("Game has not Startd yet"); // GFA 4.5.1
    }

    delay(300);
}
