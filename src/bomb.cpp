#include <bomb.h>

void dropbomb(Gladiator * gladiator, STATES & currState){
    if(gladiator->weapon->getBombCount() > 0){
        gladiator->weapon->dropBombs(1);
        currState = STATES::FLEE;
    }
    else{
        currState = STATES::MOVE;
    }
}