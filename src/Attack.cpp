#include "headers/Attack.h"


bool canAttack(Position gladiatorPosition, Position gladiatorAdvposition, float distanceThreshhold){
    return distance(gladiatorPosition, gladiatorAdvposition) <  distanceThreshhold;

}



// function to attack
void attack(Gladiator* gladiator , byte adverId){
    
    // getting position data
    Position gladiatorPosition = gladiator->robot->getData().position;
    Position gladiatorAdvposition = gladiator->game->getOtherRobotData(adverId).position;  
    
    // Move aggressively in high speed when near target and the difference in angle < 50
    // TO CHANGE
    aim(gladiator, Vector2(gladiatorAdvposition.x, gladiatorPosition.y),0.2f, 0.5, 0.1);

}

