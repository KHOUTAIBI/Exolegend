#include "gladiator.h"
#include "./headers/Attack.h"
#include "./headers/SomethingRobotics.h"
#include "./headers/tools.h"

Gladiator *gladiator; // init gladiator
RobotData gadiatorData; // data of the robots

void reset();
void setup()
{
    // instanciation de l'objet gladiator
    gladiator = new Gladiator();
    // enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    gladiator->game->onReset(&reset); // GFA 4.4.1
    gladiator->weapon->initWeapon(WeaponPin::M1, WeaponMode::SERVO); //Sertting the weapong mode of the robot to servo
}

void reset()
{
    // fonction de reset:
    // initialisation de toutes vos variables avant le début d'un match
    gladiator->log("Call of reset function"); // GFA 4.5.1
}

void loop(){
    if (gladiator->game->isStarted()){
        gladiator->log("Game has begun"); // GFA 4.5.1
        gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.2); 
        gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.2);
        float* distances = distanceToAllAdvs(gladiator);
        std::cout <<distances[0];
        attack(gladiator, 20);
    }
    else
    {
        gladiator->log("Hello world - Game not Startd yet"); // GFA 4.5.1
    }
    delay(300);
}
