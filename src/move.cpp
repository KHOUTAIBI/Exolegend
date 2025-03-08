#include "headers/move.h"

Position nearestPOI = { -1, -1, -1};
std::queue<coord> toGo;
Position lastPos = { 0, 0, 0 };
float mazeSize = -1;

double distance(Position p1, Position p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x * x + y * y);
}

Position getSquarePosition(const MazeSquare* square) {
    return square->coin.p;
}

coord sqToCo(const MazeSquare* square) {
    return std::make_pair(square->i, square->j);
}

void nodesToQueue(Node* tail) {
    if (tail->previous == nullptr) {
        toGo.push(tail->co);
    }
    else {
        nodesToQueue(tail->previous);
        toGo.push(tail->co);
    }
}

// Get NearestPOI travelPoint from Square
Position POIFromSquare(Position gPos, MazeSquare* square) {
    Position pos = square->coin.p;
    pos.x = 2*pos.x - (2*gPos.x - lastPos.x);
    pos.y = 2*pos.y - (2*gPos.y - lastPos.y);
    return pos;
}

// Search for the bomb  
void BFS(Gladiator* gladiator, coord s) {
    std::queue<coord> f;
    f.push(s);
    std::set<coord> visited;
    std::map<coord, Node*> nodes;
    Node* parent = new Node;
    parent->co = s;
    nodes.insert({s, parent});
    visited.insert(s);
    
    while (!f.empty()) {
        coord nS = f.front();
        parent = nodes.at(nS);
        f.pop();

        const MazeSquare* square = gladiator->maze->getSquare(nS.first, nS.second);

        // We can update here : add a selection over the color of the ground
        if (square->coin.value > 0) {
            nodesToQueue(parent);
            break;
        }

        if (square->northSquare != nullptr) {
            coord north = sqToCo(square->northSquare);
            if (visited.find(north) == visited.end()) {
                Node* node = new Node;
                node->co = north;
                node->previous = parent;
                nodes.insert({north, node});
                f.push(north);
                visited.insert(north);
            }
        }
        if (square->southSquare != nullptr){
            coord south = sqToCo(square->southSquare);
            if (visited.find(south) == visited.end()) {
                Node* node = new Node;
                node->co = south;
                node->previous = parent;
                nodes.insert({south, node});
                f.push(south);
                visited.insert(south);
            }
        } 
        if (square->westSquare != nullptr) {
            coord west = sqToCo(square->westSquare);
            if (visited.find(west) == visited.end()) {
                Node* node = new Node;
                node->co = west;
                node->previous = parent;
                nodes.insert({west, node});
                f.push(west);
                visited.insert(west);
            }
        }
        if (square->eastSquare != nullptr) {
            coord east = sqToCo(square->eastSquare);
            if (visited.find(east) == visited.end()) {
                Node* node = new Node;
                node->co = east;
                node->previous = parent;
                nodes.insert({east, node});
                f.push(east);
                visited.insert(east);
            }
        }
    }

    for (const auto& node : nodes) {
        delete node.second;
    }
}

bool aim(Gladiator *gladiator, const Vector2 &target, float angThresh, float defaultSpeed) {
    float POS_REACHED_THRESHOLD = 0.1;

    auto posRaw = gladiator->robot->getData().position;
    Vector2 pos{posRaw.x, posRaw.y};

    Vector2 posError = target - pos;

    float targetAngle = posError.angle();
    float angleError = moduloPi(targetAngle - posRaw.a);

    bool targetReached = false;
    float leftCommand = 0.f;
    float rightCommand = 0.f;
    
    if (posError.norm2() < POS_REACHED_THRESHOLD) {
        targetReached = true;
    }
    else if (abs(angleError) > angThresh && abs(angleError) < M_PI - angThresh) {   
        float factor = 0.05;
        if (angleError < 0)
            factor = -factor;
        rightCommand = factor;
        leftCommand = -factor;
    }
    else {
        float factor = defaultSpeed;
        if (abs(angleError) > M_PI - angThresh) factor = -factor;
        rightCommand = factor; //+angleError*0.1  => terme optionel, "pseudo correction angulaire";
        leftCommand = factor;  //-angleError*0.1   => terme optionel, "pseudo correction angulaire";
    }

    gladiator->control->setWheelSpeed(WheelAxis::LEFT, leftCommand);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, rightCommand);

    return targetReached;
}

bool isCloseEnough(Position gPos) {
    // printf("%lf\n", distance(gPos, nearestPOI));
    return distance(gPos, nearestPOI) < 0.1;
}

void move(Gladiator* gladiator) {
    Position gladiatorPos = gladiator->robot->getData().position;
    int outside = isOutsideMaze(gladiator);
    if (outside == 1) {
        aim(gladiator, { 1.5, gladiatorPos.y }, (M_PI / 2.0), 0.5);
        while (!toGo.empty()) toGo.pop();
    }
    else if (outside == 2) {
        aim(gladiator, { gladiatorPos.x, 1.5 }, (M_PI / 2.0), 0.5);
        while (!toGo.empty()) toGo.pop();
    }
    else {
        // nearestPOI = findNearestPOI(gladiator);
        if (nearestPOI.x == -1) nearestPOI = gladiatorPos;

        int newSize = gladiator->maze->getCurrentMazeSize();
        if (mazeSize != newSize) {
            mazeSize = newSize;
            nearestPOI = gladiatorPos;
            while (!toGo.empty()) toGo.pop();
        }

        // if (gladiator->weapon->getBombCount()) {
        //     gladiator->weapon->dropBombs(1);
        // }

        const MazeSquare* square = gladiator->maze->getNearestSquare();
        
        // Construct toGo
        if (toGo.empty() && isCloseEnough(gladiatorPos)) {
            coord co = sqToCo(square);
            // printf("Starting with : %x %x\n", co.first, co.second);
            BFS(gladiator, co);
        }
        if (!toGo.empty() && isCloseEnough(gladiatorPos)) {
            coord co = toGo.front();
            // printf("CO : %x %x\n", co.first, co.second);
            nearestPOI = getSquarePosition(gladiator->maze->getSquare(co.first, co.second));
            // printf("NPOI : %lf %lf\n", nearestPOI.x, nearestPOI.y);
            toGo.pop();
            // puts("---");
        }

        // goTo(gladiator, nearestPOI, gladiatorPos);
        aim(gladiator, { nearestPOI.x, nearestPOI.y });
    }

    lastPos = gladiatorPos;
}

int isOutsideMaze(Gladiator *gladiator) {
    float mazeSize = gladiator->maze->getCurrentMazeSize();
    Position position = gladiator->robot->getData().position;
    float half = mazeSize / 2.0f;
    double distX = distance({ position.x, 0, 0 }, { 1.5, 0, 0 });
    double distY = distance({ 0, position.y, 0 }, { 0, 1.5, 0 });
    bool result = 0;

    if (distX > half) {
        result = 1;
    }
    else if (distY > half) {
        result = 2;
    }
    
    return result;
}