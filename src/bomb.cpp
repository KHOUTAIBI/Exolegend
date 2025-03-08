#include "./headers/bomb.h"

MazeSquare ** fleeStrat(Gladiator * gladiator){
    MazeSquare * strat[2];
    MazeSquare * start = gladiator->maze->getNearestSquare();

    //etablir la strat
    if (start->northSquare != nullptr && start->northSquare->eastSquare != nullptr){
        strat[0] = start->northSquare;
        strat[1] = start->northSquare->eastSquare;
        return strat;
    }
    else if (start->northSquare != nullptr && start->northSquare->westSquare != nullptr){
        strat[0] = start->northSquare;
        strat[1] = start->northSquare->westSquare;
        return strat;
    }
    else if (start->southSquare != nullptr && start->southSquare->eastSquare != nullptr){
        strat[0] = start->southSquare;
        strat[1] = start->southSquare->eastSquare;
        return strat;
    }
    else if (start->southSquare != nullptr && start->southSquare->westSquare != nullptr){
        strat[0] = start->southSquare;
        strat[1] = start->southSquare->westSquare;
        return strat;
    }
    else if (start->eastSquare != nullptr && start->eastSquare->northSquare != nullptr){
        strat[0] = start->eastSquare;
        strat[1] = start->eastSquare->northSquare;
        return strat;
    }
    else if (start->eastSquare != nullptr && start->eastSquare->southSquare != nullptr){
        strat[0] = start->eastSquare;
        strat[1] = start->eastSquare->southSquare;
        return strat;
    }
    else if (start->westSquare != nullptr && start->westSquare->northSquare != nullptr){
        strat[0] = start->westSquare;
        strat[1] = start->westSquare->northSquare;
        return strat;
    }
    else if (start->westSquare != nullptr && start->westSquare->southSquare != nullptr){
        strat[0] = start->westSquare;
        strat[1] = start->westSquare->southSquare;
        return strat;
    }
    else{
        return nullptr;
    }
}

bool canDropBomb(Gladiator * gladiator, MazeSquare ** strat){
    return (gladiator->weapon->getBombCount() > 0) && (strat != nullptr) && (gladiator->maze->getNearestSquare()->possession == 0);
}


int dropBombAndFlee(Gladiator * gladiator){
    MazeSquare ** strat = fleeStrat(gladiator);

    if(canDropBomb(gladiator, strat)){
        gladiator->weapon->dropBombs(1);
        // add strat to goto
    }
    return 0;
    
}

