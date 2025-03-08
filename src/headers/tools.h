#ifndef TOOLS_H
#define TOOLS_H

#include <gladiator.h>
#include <vector>
#define ID1 37
#define ID2 40 

double reductionAngle(double x);
void go_to(Gladiator * gladiator, Position cons, Position pos);
float normRobot(float x, float y);
float distanceTwoRobots(Position gladiatorPos, Position gladiatorAdvPos);
std::vector<float> distanceToAllAdvs(Gladiator* gladiator);


#endif
