#include "headers/tools.h"

float kw = 1.2;
float kv = 1.f;
float wlimit = 3.f;
float vlimit = 1.0;
float erreurPos = 0.07;

double reductionAngle(double x){
    x = fmod(x + PI, 2 * PI);
    if (x < 0)
        x += 2 * PI;
    return x - PI;
}

void go_to(Gladiator * gladiator, Position cons, Position pos){

    double consvl, consvr;
    double dx = cons.x - pos.x;
    double dy = cons.y - pos.y;
    double d = sqrt(dx * dx + dy * dy);

    if (d > erreurPos)
    {
        double rho = atan2(dy, dx);
        double consw = kw * reductionAngle(rho - pos.a);

        double consv = kv * d * cos(reductionAngle(rho - pos.a));
        consw = abs(consw) > wlimit ? (consw > 0 ? 1 : -1) * wlimit : consw;
        consv = abs(consv) > vlimit ? (consv > 0 ? 1 : -1) * vlimit : consv;

        consvl = consv - gladiator->robot->getRobotRadius() * consw; // GFA 3.6.2
        consvr = consv + gladiator->robot->getRobotRadius() * consw; // GFA 3.6.2
    }
    else
    {
        consvr = 0;
        consvl = 0;
    }

    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, consvr, false); // GFA 3.2.1
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, consvl, false);  // GFA 3.2.1
}

// norm function, tool to be used later
float normRobot(float x, float y){
    return std::sqrt(
        pow(x,2) + pow(y,2)
    );
}

// funciton returning distance between two robots
float distance(Position gladiatorPos, Position gladiatorAdvPos){

    return normRobot(
        gladiatorPos.x - gladiatorAdvPos.x,
        gladiatorPos.y - gladiatorAdvPos.y
    );
}

// Function which returns the distances to all robots
std::vector<float> distanceToAllAdvs(Gladiator* gladiator){

    std::vector<float> distancesToAdvs;
    uint8_t Listids[4] = {
        gladiator->game->getPlayingRobotsId().ids[0],
        gladiator->game->getPlayingRobotsId().ids[1],
        gladiator->game->getPlayingRobotsId().ids[2],
        gladiator->game->getPlayingRobotsId().ids[3]
    };

    for (int i = 0; i < 4; i++){
        if (Listids[i] != ID1 && Listids[i] != ID2){
            distancesToAdvs.push_back(distance(gladiator->robot->getData().position, gladiator->game->getOtherRobotData(Listids[i]).position));
        }
    }

    // sorting an easily sortable array
    if (distancesToAdvs[1] <= distancesToAdvs[0]){
        distancesToAdvs[0] = distancesToAdvs[1];
    }

    return distancesToAdvs;
}

Position getSquarePosition(const MazeSquare* square) {
    return square->coin.p;
}

bool isOutsideMaze(Gladiator* gladiator, const Position& pos) {
    float currMazeSize = gladiator->maze->getCurrentMazeSize();
    float half = currMazeSize / 2.0f;
    double distX = distance({ pos.x, 0, 0 }, { 1.5, 0, 0 });
    double distY = distance({ 0, pos.y, 0 }, { 0, 1.5, 0 });
    bool result = false;

    if (distX > half || distY > half) {
        result = true;
    }
    
    return result;
}

float moduloPi(float a) // return angle in [-pi; pi]
{
    return (a < 0.0) ? (std::fmod(a - M_PI, 2 * M_PI) + M_PI) : (std::fmod(a + M_PI, 2 * M_PI) - M_PI);
}
