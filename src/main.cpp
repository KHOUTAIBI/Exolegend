#include "gladiator.h"
#include "./headers/SomethingRobotics.h"

Gladiator *gladiator;

void reset();
void setup(){
    gladiator = new Gladiator();
    gladiator->game->onReset(&reset); // GFA 4.4.1
}

void reset(){
    gladiator->log("Call of reset function"); // GFA 4.5.1
}

void loop(){
    if (gladiator->game->isStarted()){
        
        gladiator->log("Game has begun"); // GFA 4.5.1
        gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.2); 
        gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.2); 
    }
    else{
        gladiator->log("Game has not Startd yet"); // GFA 4.5.1
    }

    delay(300);
}
