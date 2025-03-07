#ifndef FLEE_H
#define FLEE_H

#include "gladiator.h"
#include "SomethingRobotics.h"
#include "tools.h"

enum DIR {N, S, E, W};

void flee(Gladiator * gladiator, STATES & currState);

#endif