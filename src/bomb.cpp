#include "./headers/bomb.h"
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

std::vector<FleeStrat> stratSet;


bool fleeStrat(Gladiator * gladiator, FleeStrat & bestStrat){
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

    bestStrat = * stratSet.begin();
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
    FleeStrat bestStrat;
    bool escape = fleeStrat(gladiator, bestStrat) && gladiator->weapon->getBombCount() && (gladiator->maze->getNearestSquare()->possession != gladiator->robot->getData().teamId);

    if(escape) {
        gladiator->weapon->dropBombs(gladiator->weapon->getBombCount());
        while (!toGo.empty()) toGo.pop();
        toGo.push(sqToCo(bestStrat.first));
        toGo.push(sqToCo(bestStrat.second));
        return 0;
    }
    else {
        return 1;
    }
}

