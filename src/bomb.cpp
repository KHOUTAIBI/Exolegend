#include "./headers/bomb.h"

bool fleeStrat(Gladiator * gladiator){
    bool result = true;
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
    else{
        result = false;
    }

    if(strat[0]->danger > 0 && strat[1]->danger > 0){
        result = false;
    }

    while (!toGo.empty()) toGo.pop();
    toGo.push(sqToCo(strat[0]));
    toGo.push(sqToCo(strat[1]));
    return result;
}

bool canDropBomb(Gladiator * gladiator, MazeSquare ** strat){
    return (gladiator->weapon->getBombCount() > 0) && (strat != nullptr) && (gladiator->maze->getNearestSquare()->possession == 0);
}


int dropBombAndFlee(Gladiator * gladiator){
    bool escape = fleeStrat(gladiator);

    if(escape && gladiator->weapon->getBombCount() && 
        (gladiator->maze->getNearestSquare()->possession != gladiator->robot->getData().teamId)) {
        gladiator->weapon->dropBombs(1);
        return 0;
    }
    else {
        while (!toGo.empty()) toGo.pop();
        return 1;
    }
}

