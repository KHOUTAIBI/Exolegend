#ifndef FLEE_H
#define FLEE_H

#include "./SomethingRobotics.h"

enum DIR {N, S, E, W};

void flee(Gladiator* gladiator, STATES& currentState);

#endif