#include "gladiator.h"
#include "headers/SomethingRobotics.h"

Gladiator *gladiator; // init gladiator
RobotData gadiatorData; // data of the robots
uint8_t ListIdsAdvs[2];

void reset();
void setup(){
    gladiator = new Gladiator(); //gladiator 1, friendly
    gladiator->game->onReset(&reset); // GFA 4.4.1
    gladiator->weapon->initWeapon(WeaponPin::M1, WeaponMode::SERVO); //Sertting the weapong mode of the robot to servo
    

    if(gladiator->robot->getData().id == 37){
        gladiator->robot->setCalibrationOffset(0.0192, 0.0011, 0);
    }
    if(gladiator->robot->getData().id == 40){
        gladiator->robot->setCalibrationOffset(0.0111, -0.0037, 0);
    }
    


}

void reset(){
    gladiator->log("Call of reset function"); // GFA 4.5.1
    POI = { -1, -1, -1};
    squarePOI = nullptr;
    reachedPOI = false;
    while (!toGo.empty()) toGo.pop();
    mazeSize = -1;
    haveBeenOut = false;
    for (int i = 0; i < 4; i++){
        ListIdsAdvs[i] = 0;
    }
}

void loop(){
    
    if (gladiator->game->isStarted()){
        // gladiator->log("Game has begun"); // GFA 4.5.1
        command(gladiator);
    }
    else{
        // gladiator->log("Game has not Startd yet"); // GFA 4.5.1
    }

    delay(5);
}
