#include "headers/movement.h"

// Global values for movement defined here
Position POI = { -1, -1, -1 }; // The default target the robot is trying to meet
bool reachedPOI = false;
const MazeSquare* squarePOI = nullptr;
std::queue<coord> toGo;
float mazeSize = -1;
bool haveBeenOut = false;
MODE mode = MODE::EXPLORE;

// Non reset
float baseDistance = 0.0;

bool aim(Gladiator *gladiator, const Vector2 &target, float angThresh, float defaultSpeed, float defaultRotSpeed) {
    float POS_REACHED_THRESHOLD = gladiator->maze->getSquareSize() * 0.3;

    auto posRaw = gladiator->robot->getData().position;
    Vector2 pos{posRaw.x, posRaw.y};

    Vector2 posError = target - pos;

    float targetAngle = posError.angle();
    float angleError = moduloPi(targetAngle - posRaw.a);
    
    bool reverse = false;
    // Choosing to reverse.
    if (abs(moduloPi(targetAngle - (posRaw.a + M_PI))) < abs(angleError)) {
        reverse = true;
        gladiator->log("REVERSE INCOMING");
        angleError = moduloPi(angleError - M_PI);
    }

    bool targetReached = false;
    float leftCommand = 0.f;
    float rightCommand = 0.f;
    float d = posError.norm2();
    if (d < POS_REACHED_THRESHOLD) {
        targetReached = true;
    }

    else if (abs(angleError) > angThresh) {   
        float factor = defaultRotSpeed;
        if ((targetAngle - posRaw.a) < 0)
            factor = -factor;
        rightCommand = factor;
        leftCommand = -factor;
    }
    else {
        float factor = defaultSpeed;

        // Smoother transition function for speed scaling
        float k = 1;
        factor *= std::exp(-k * (baseDistance - d));  // Soft deceleration

        rightCommand = factor; // + angleError*0.1 => terme optionel, "pseudo correction angulaire";
        leftCommand = factor; // - angleError*0.1  => terme optionel, "pseudo correction angulaire";

        if (reverse){
            std::swap(leftCommand, rightCommand);
            leftCommand *= -1;
            rightCommand *= -1;
        }
    }

    gladiator->control->setWheelSpeed(WheelAxis::LEFT, leftCommand);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, rightCommand);

    return targetReached;
}

coord frontToGo() {
    coord p1 = toGo.front();
    toGo.pop();
    if (!toGo.empty()) {
        coord next = toGo.front();
        if (next.first == p1.first) {
            while (next.first == p1.first) {
                p1 = next;
                toGo.pop();
                if (toGo.empty()) break;
                next = toGo.front();
            }
        }
        else if (next.second == p1.second) {
            while (next.second == p1.second) {
                p1 = next;
                toGo.pop();
                if (toGo.empty()) break;
                next = toGo.front();
            }
        }
    }
    return p1;
}

Position getAllyPos(Gladiator* gladiator) {
    byte teamId = gladiator->robot->getData().teamId;
    byte id = gladiator->robot->getData().id;
    Position result = { -1, -1, -1 };

    
    uint8_t Listids[4] = {
        gladiator->game->getPlayingRobotsId().ids[0],
        gladiator->game->getPlayingRobotsId().ids[1],
        gladiator->game->getPlayingRobotsId().ids[2],
        gladiator->game->getPlayingRobotsId().ids[3]
    };

    for (int i = 0; i < 4; ++i) {
        RobotData rData = gladiator->game->getOtherRobotData(Listids[i]);
        if (rData.teamId == teamId && rData.id != id) {
            result = rData.position; 
            break;
        }
    }
    return result;
}

Position attackable(Gladiator* gladiator) {
    std::pair<float,byte> distAndId = distanceToAllAdvs(gladiator);
    Position result = { -1, -1, -1 };
    if (distAndId.first > 0.4) return result;
    Position posAdv = gladiator->game->getOtherRobotData(distAndId.second).position;
    Position gPos = gladiator->robot->getData().position;
    if (abs(posAdv.a - gPos.a) < M_PI * 0.8 &&  gladiator->game->getOtherRobotData(distAndId.second).lifes > 0) {
        result = posAdv;
    }
    return result;
}

coord positionToCoord(Gladiator* gladiator, Position pos) {
    float size = gladiator->maze->getSquareSize();
    byte i = std::floor(pos.x / size);
    byte j = std::floor(pos.y / size);
    i = (i > 12) ? 12 : i;
    j = (j > 12) ? 12 : j;

    return std::make_pair(i, j);
}

float speed = 0.0f;

StateMove control(Gladiator* gladiator) {
    StateMove result = StateMove::STAY; // Returned value for the machine state
    Position gPos = gladiator->robot->getData().position;
    
    if (isOutsideMaze(gladiator, gPos)) {
        // Handle the case when the robot is outside the maze
        // gladiator->log("I'm outside, HEEELP !");
        aim(gladiator, { 1.5, 1.5 }, 0.2, 1.0, 0.2);
        while (!toGo.empty()) toGo.pop();
        toGo.push(std::make_pair(6, 6));
        mode = MODE::FAST;
        delay(50);
    }
    else {
        // Current square we're on 
        const MazeSquare* square = gladiator->maze->getNearestSquare();
        
        if (POI.x == -1) {
            squarePOI = square;
            POI = gPos;
        }
        
        // Detect if the arena size changed and reset our path
        int newSize = gladiator->maze->getCurrentMazeSize();
        if (mazeSize == -1) {
            mazeSize = newSize;
        }
        else if (mazeSize != newSize) {
            mazeSize = newSize;
            POI = gPos;
            while (!toGo.empty()) toGo.pop();
        }

        Position toAttack = attackable(gladiator);
        if (toAttack.x != -1) {
            mode = MODE::FAST;
            coord co = positionToCoord(gladiator, toAttack);
            squarePOI = gladiator->maze->getSquare(co.first, co.second);
            POI = { toAttack.x, toAttack.y };
            baseDistance = distance(gPos, POI);
            reachedPOI = false;
        }

        // Adapt the speed to the mode
        switch (mode) {
            case MODE::EXPLORE:
            speed = 0.4f;
            break;
            case MODE::FLEE:
            speed = 0.5f;
            break;
            case MODE::ATTACK:
            case MODE::FAST:
            speed = 0.8f;
            break;
        }

        // If toGo is empty and the current POI is reached we can pursue 
        if (toGo.empty() && reachedPOI) {
            // gladiator->log("BFS");
            coord co = squareToCoord(square);
            
            if (gladiator->weapon->getBombCount() == 0) {
                BFS(gladiator, co, WANTED::FREE_BOMB, false); // Search for the closest FREE_BOMB
                if (toGo.empty()) {
                    BFS(gladiator, co, WANTED::BOMB, false);
                }
                mode = MODE::EXPLORE;
            }
            else if (square->possession == gladiator->robot->getData().teamId) {
                BFS(gladiator, co, WANTED::FREE_SQUARE, false); // Search for the closest FREE_SQUARE
                mode = MODE::EXPLORE;
            }
            else {
                result = StateMove::BOMB;
                return result;
            }
            // TODO tourner en rond à la fin
            
            // Handle the case when we are in a dead end
            if (toGo.empty()) {
                // gladiator->log("STILL EMPTY - DEAD END");
                toGo.push(std::make_pair(6, 6));
                mode = MODE::FAST;
            }
        }

        if (gladiator->weapon->getBombCount() && square->danger == 0 && square->possession != gladiator->robot->getData().teamId) result = StateMove::BOMB;

        // Case when we have a path to follow
        if (!toGo.empty() && reachedPOI) {
            // gladiator->log("POI reached");
            // New POI
            coord co = frontToGo();
            // gladiator->log("Target : %d %d\n", co.first, co.second);
            squarePOI = gladiator->maze->getSquare(co.first, co.second);
            POI = getSquarePosition(squarePOI);

            // Check if my ally is to close to that POI
            // Position allyPos = getAllyPos(gladiator);
            // if (allyPos.x != -1 && distance(allyPos, gPos) < 0.5) {
            //     while (!toGo.empty()) toGo.pop();
            //     POI = gPos;
            //     squarePOI = square;
            //     reachedPOI = false;
            // }
            // Handle the case where he want to go outside
            if (isOutsideMaze(gladiator, POI)) {
                POI = { 1.5, 1.5 };
                squarePOI = gladiator->maze->getSquare(6, 6);
                while (!toGo.empty()) toGo.pop();
                speed = 1.0f;
                mode = MODE::FAST;
            }
            // Compute the baseDistance
            baseDistance = distance(gPos, POI);
            reachedPOI = false;
        }

        // Choose how to move (in an intelligent way [i hope ^^])
        if (squarePOI->danger == 0 || // We are in danger
            square->danger >= squarePOI->danger // The current square is worst than the POI
        ) {
            reachedPOI = aim(gladiator, { POI.x, POI.y }, 0.15f, speed, 0.1f);
        }
        else {
            while (!toGo.empty()) toGo.pop();
            const MazeSquare* currentSquare = gladiator->maze->getNearestSquare();
            if (currentSquare->danger > 0) {
                coord co = squareToCoord(currentSquare);
                BFS(gladiator, co, WANTED::DANGER_FREE, true);
            }
            else {
                coord co = squareToCoord(currentSquare);
                BFS(gladiator, co, WANTED::DANGER_FREE, false);
            }
        }
    }

    return result;
}

coord squareToCoord(const MazeSquare *square)
{
    return std::make_pair(square->i, square->j);
}

void nodesToQueue(Node *tail, std::queue<coord> &qu) {
    if (tail->previous == nullptr) {
        qu.push(tail->co);
    }
    else {
        nodesToQueue(tail->previous, qu);
        qu.push(tail->co);
    }
}

// Function to summarize the addition of new point in BFS
void registerSquare(const MazeSquare* square, const int& depth, std::queue<std::pair<int, coord>>& f, std::set<coord>& visited, std::map<coord, Node*>& nodes, Node* parent, bool controlDanger) {
    if (square != nullptr ) {
        coord co = squareToCoord(square);
        if (visited.find(co) == visited.end() && (controlDanger || square->danger < 1)) {
            Node* node = new Node;
            node->co = co;
            node->idx = parent->idx + 1;
            node->previous = parent;
            nodes.insert({co, node});
            f.push(std::make_pair(depth, co));
            visited.insert(co);
        }
    }
}

void BFS(Gladiator *gladiator, coord start, WANTED type, bool controlDanger) {
    std::queue<std::pair<int, coord>> f; // The list of nodes to process (here the first int is the depth of the node)
    f.push(std::make_pair(0, start));

    std::set<coord> visited; // List of visited nodes
    visited.insert(start);

    std::map<coord, Node*> nodes; // Map of nodes of the oriented graph
    Node* parent = new Node;
    parent->co = start;
    parent->idx = 0; // First element of the path
    nodes.insert({start, parent}); 

    int endDepth = -1;
    Node* bestCandidates = nullptr;

    while (!f.empty()) {
        const std::pair<int, coord>& element = f.front();
        int depth = element.first + 1;
        if (depth > endDepth && endDepth != -1) break;

        coord current = element.second;

        parent = nodes.at(current); // Nodes in the oriented graph
        f.pop();

        // Current square the BFS is on
        const MazeSquare* square = gladiator->maze->getSquare(current.first, current.second);

        bool updateBC = false;

        // Condition checking according to the type of square needed
        if (type == WANTED::FREE_BOMB) {
            if (square->coin.value > 0 && square->possession != gladiator->robot->getData().teamId) {
                updateBC = true;
            }
        }
        else if (type == WANTED::BOMB) {
            if (square->coin.value > 0) {
                updateBC = true;
            }
        }
        else if (type == WANTED::DANGER_FREE) {
            if (square->danger < 1) {
                updateBC = true;
            }
        }
        else if (type == WANTED::FREE_SQUARE) {
            if (square->possession != gladiator->robot->getData().teamId) {
                updateBC = true;
            }
        }
        
        // The condition have been triggered, see if the BC need to change
        if (updateBC) {
            if (endDepth == -1) endDepth = depth; // Will stop after this depth
            if (bestCandidates == nullptr || bestCandidates->idx > parent->idx) {
                bestCandidates = parent;
            } 
        }
        
        registerSquare(square->northSquare, depth, f, visited, nodes, parent, controlDanger);
        registerSquare(square->eastSquare, depth, f, visited, nodes, parent, controlDanger);
        registerSquare(square->southSquare, depth, f, visited, nodes, parent, controlDanger);
        registerSquare(square->westSquare, depth, f, visited, nodes, parent, controlDanger);
    }

    // We get the path of the best canditates and copy it in toGo
    if (bestCandidates != nullptr) {
        nodesToQueue(bestCandidates, toGo);
    }

    // We clear everything we have allocate
    for (const auto& node : nodes) {
        delete node.second;
    }
}
