#include "./headers/bomb.h"

void dropbomb(Gladiator * gladiator, STATES& currentState){
    if(gladiator->weapon->getBombCount() > 0){
        gladiator->weapon->dropBombs(1);
        currentState = STATES::FLEE;
    }
    else{
        currentState = STATES::MOVE;
    }
}