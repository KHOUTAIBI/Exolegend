#include "./headers/flee.h"

int flee(Gladiator * gladiator){

    MazeSquare * strat[2];
    MazeSquare * start = gladiator->maze->getNearestSquare();



    //executer la stat
    Position pos, mypos;
    
    pos = getSquarePosition(strat[0]);
    mypos = gladiator->robot->getData().position;
    aim(gladiator, {pos.x, pos.y}, false);
    while (start->danger > 0){};

    
    
    return 0;
}