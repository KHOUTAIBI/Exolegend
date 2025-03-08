#include "headers/bomb.h"

struct FleeStrat{
    int distanceFromCenter{}; // in normmax
    MazeSquare * first{};
    MazeSquare * second{};

    FleeStrat(){}

    FleeStrat(int distance, MazeSquare * first, MazeSquare * second){
        this->distanceFromCenter = distance;
        this->first = first;
        this->second = second;
    }
};

// global best strat
FleeStrat bestStrat;


bool fleeStrat(Gladiator * gladiator){
    std::vector<FleeStrat> stratSet;
    MazeSquare * start = gladiator->maze->getNearestSquare();
    int distance;

    MazeSquare * plusTab[4] = {start->northSquare, start->westSquare, start->southSquare, start->eastSquare};

    for(int i = 0; i < 4; i++){
        if (plusTab[i] != nullptr && plusTab[i]->danger < 1){
            if(i % 2 == 0){
                if(plusTab[i]->westSquare != 0 && plusTab[i]->westSquare->danger < 1) {
                    distance = std::max(abs(plusTab[i]->westSquare->i - 6), abs(plusTab[i]->westSquare->j - 6));
                    stratSet.push_back(FleeStrat(distance ,plusTab[i], plusTab[i]->westSquare));
                }
                if(plusTab[i]->eastSquare != 0 && plusTab[i]->eastSquare->danger < 1) {
                    distance = std::max(abs(plusTab[i]->eastSquare->i - 6), abs(plusTab[i]->eastSquare->j - 6));
                    stratSet.push_back(FleeStrat(distance ,plusTab[i], plusTab[i]->eastSquare));
                }
            }
            else if(i % 2 == 1){
                if(plusTab[i]->northSquare != 0 && plusTab[i]->northSquare->danger < 1) {
                    distance = std::max(abs(plusTab[i]->northSquare->i - 6), abs(plusTab[i]->northSquare->j - 6));
                    stratSet.push_back(FleeStrat(distance ,plusTab[i], plusTab[i]->northSquare));
                }
                if(plusTab[i]->southSquare != 0 && plusTab[i]->southSquare->danger < 1) {
                    distance = std::max(abs(plusTab[i]->southSquare->i - 6), abs(plusTab[i]->southSquare->j - 6));
                    stratSet.push_back(FleeStrat(distance ,plusTab[i], plusTab[i]->southSquare));
                }
            }
        }
    }

    if(stratSet.empty()){
        return false;
    }

    bestStrat = stratSet[0];
    for(auto S : stratSet){
        if (S.distanceFromCenter < bestStrat.distanceFromCenter){
            bestStrat = S;
        }
    }
    return true;
}

bool canDropBomb(Gladiator * gladiator, MazeSquare ** strat){
    return (gladiator->weapon->getBombCount() > 0) && (strat != nullptr) && (gladiator->maze->getNearestSquare()->possession == 0);
}


int dropBombAndFlee(Gladiator * gladiator){
    bool escape = fleeStrat(gladiator);
    escape = escape && (gladiator->weapon->getBombCount() > 0) && (gladiator->maze->getNearestSquare()->possession != gladiator->robot->getData().teamId);

    if(escape) {
        gladiator->weapon->dropBombs(gladiator->weapon->getBombCount());
        while (!toGo.empty()) toGo.pop();
        gladiator->log("the best first strat is (%i,%i)",bestStrat.first->i,bestStrat.first->j);
        gladiator->log("the best second strat is  (%i,%i)",bestStrat.second->i,bestStrat.second->j);
        toGo.push(squareToCoord(bestStrat.first));
        toGo.push(squareToCoord(bestStrat.second));
        mode = MODE::FLEE;
        return 0;
    }
    else {
        return 1;
    }
}

