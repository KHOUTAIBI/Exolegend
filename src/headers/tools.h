#ifndef TOOLS_H
#define TOOLS_H

#include "gladiator.h"

float kw = 1.2;
float kv = 1.f;
float wlimit = 3.f;
float vlimit = 0.6;
float erreurPos = 0.07;

double reductionAngle(double x);
void go_to(Gladiator * gladiator, Position cons, Position pos);

#endif