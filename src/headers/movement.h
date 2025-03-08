#ifndef MOVEMENT
#define MOVEMENT

#include "tools.h"
#include <queue>
#include <set>
#include <map>

// Alias for the square's coordinates
using coord = std::pair<byte, byte>;

// Linked element for the oriented graph
typedef struct Node {
    coord co;
    byte idx; // Give you, from a tail, the number of parent he have
    Node* previous = nullptr;
    Node* next = nullptr; 
} Node;

// Extern value
extern Position POI; // The default target the robot is trying to meet
extern bool reachedPOI;
extern const MazeSquare* squarePOI;
extern std::queue<coord> toGo;
extern float mazeSize;
extern bool haveBeenOut;

// FLAG for the state machine after the control function
enum class StateMove { STAY, BOMB, FLEE };
enum class WANTED { FREE_SQUARE, FREE_BOMB, BOMB, DANGER_FREE };

bool aim(Gladiator *gladiator, 
        const Vector2 &target, 
        float angThresh = 0.2, 
        float defaultSpeed = 0.2, 
        float defaultRotSpeed = 0.08);

StateMove control(Gladiator* gladiator);

coord squareToCoord(const MazeSquare* square);

void nodesToQueue(Node* tail, std::queue<coord>& qu); // Travel along this arc and append, from bottom to top, the element to qu

// Return the first and closest (according to depth) element of the desired type
void BFS(Gladiator* gladiator, coord start, WANTED type = WANTED::FREE_BOMB);
#endif