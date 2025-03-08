#ifndef ATTACK_H
#define ATTACK_H

#include <gladiator.h>
#include "./headers/tools.h"

float kw = 1.2;
float kv = 1.f;
float wlimit = 3.f;
float vlimit = 0.6;
float erreurPos = 0.07;

// Funciton to speed up and hit the robot
inline void moveAgress(Gladiator* gladiator){
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.9);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.9);
}

void go_to(Gladiator* gladiator,Position cons, Position pos);
double reductionAngle(double x);

// Function to decide when to attack a robot
inline void attack(Gladiator* gladiator , byte adverId){  

    // getting position data
    Position gladiatorPosition = gladiator->robot->getData().position;
    Position gladiatorAdvposition = gladiator->game->getOtherRobotData(adverId).position;  

    go_to(gladiator,gladiatorPosition,gladiatorAdvposition);

    float alphaGlad = gladiatorPosition.a;
    float alphaAdvGlad = gladiatorAdvposition.a;
    
    // Move aggressively in high speed when near target and the difference in angle < 50
    // TO CHANGE
    if (distanceTwoRobots(gladiatorPosition, gladiatorAdvposition) <  0.001 && abs(alphaGlad - alphaAdvGlad) < 10){
        moveAgress(gladiator);
    }


}

void go_to(Gladiator* gladiator,Position cons, Position pos)
{
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

double reductionAngle(double x){
    x = fmod(x + PI, 2 * PI);
    if (x < 0)
        x += 2 * PI;
    return x - PI;
}

#endif