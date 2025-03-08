#include "./headers/flee.h"

void flee(Gladiator * gladiator){

    MazeSquare * strat[2];
    MazeSquare * start = gladiator->maze->getNearestSquare();

    //etablir la strat
    if (start->northSquare != nullptr && start->northSquare->eastSquare != nullptr){
        strat[0] = start->northSquare;
        strat[1] = start->northSquare->eastSquare;
    }
    else if (start->northSquare != nullptr && start->northSquare->westSquare != nullptr){
        strat[0] = start->northSquare;
        strat[1] = start->northSquare->westSquare;
    }
    else if (start->southSquare != nullptr && start->southSquare->eastSquare != nullptr){
        strat[0] = start->southSquare;
        strat[1] = start->southSquare->eastSquare;
    }
    else if (start->southSquare != nullptr && start->southSquare->westSquare != nullptr){
        strat[0] = start->southSquare;
        strat[1] = start->southSquare->westSquare;
    }
    else if (start->eastSquare != nullptr && start->eastSquare->northSquare != nullptr){
        strat[0] = start->eastSquare;
        strat[1] = start->eastSquare->northSquare;
    }
    else if (start->eastSquare != nullptr && start->eastSquare->southSquare != nullptr){
        strat[0] = start->eastSquare;
        strat[1] = start->eastSquare->southSquare;
    }
    else if (start->westSquare != nullptr && start->westSquare->northSquare != nullptr){
        strat[0] = start->westSquare;
        strat[1] = start->westSquare->northSquare;
    }
    else if (start->westSquare != nullptr && start->westSquare->southSquare != nullptr){
        strat[0] = start->westSquare;
        strat[1] = start->westSquare->southSquare;
    }
    // fuite en ligne droite
    else if (start->northSquare != nullptr && start->northSquare->northSquare != nullptr){
        strat[0] = start->northSquare;
        strat[1] = start->northSquare->northSquare;
    }
    else if (start->southSquare != nullptr && start->southSquare->southSquare != nullptr){
        strat[0] = start->southSquare;
        strat[1] = start->southSquare->southSquare;
    }
    else if (start->eastSquare != nullptr && start->eastSquare->eastSquare != nullptr){
        strat[0] = start->eastSquare;
        strat[1] = start->eastSquare->eastSquare;
    }
    else if (start->westSquare != nullptr && start->westSquare->westSquare != nullptr){
        strat[0] = start->westSquare;
        strat[1] = start->westSquare->westSquare;
    }
    
    while (!toGo.empty()) toGo.pop();
    toGo.push(squareToCoord(strat[0]));
    toGo.push(squareToCoord(strat[1]));

    //executer la stat
    // for (int i = 0; i < 2; i++){
    //     // Position myPosition = gladiator->robot->getData().position;
    //     // Position nextPosition{(strat[0]->i + 1/2)*gladiator->maze->getSquareSize(), (strat[0]->j + 1/2)*gladiator->maze->getSquareSize(), 0};
    //     // go_to(gladiator, nextPosition, myPosition);
    // }
}