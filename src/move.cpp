#include "headers/move.h"

bool gotPOI = true;
Position nearestPOI = { -1, -1, -1};
std::queue<coord> toGo;
Position lastPos = { 0, 0, 0 };
float mazeSize = -1;
bool firstMove = true;

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

bool isCloseEnough(Position gPos) {
    // printf("%lf\n", distance(gPos, nearestPOI));
    return distance(gPos, nearestPOI) < 0.1;
}

void move(Gladiator* gladiator) {
    // nearestPOI = findNearestPOI(gladiator);
    Position gladiatorPos = gladiator->robot->getData().position;
    if (nearestPOI.x == -1) nearestPOI = gladiatorPos;

    // if (gladiator->weapon->canDropBombs(1)) {
    //     gladiator->weapon->dropBombs(1);
    // }

    float newSize = gladiator->maze->getCurrentMazeSize();

    if (newSize != mazeSize) {
        mazeSize = newSize;
        while (!toGo.empty()) toGo.pop();
    }

    const MazeSquare* square = gladiator->maze->getNearestSquare();
    
    // Construct toGo
    if (toGo.empty() && isCloseEnough(gladiatorPos)) {
        coord co = sqToCo(square);
        printf("Starting with : %x %x\n", co.first, co.second);
        BFS(gladiator, co);
    }

    // while (!toGo.empty()) {
    //     // puts("Not empty");
    //     coord co = toGo.front();
    //     printf("CO : %x %x\n", co.first, co.second);
    //     toGo.pop();
    // }

    if (!toGo.empty() && isCloseEnough(gladiatorPos)) {
        coord co = toGo.front();
        printf("CO : %x %x\n", co.first, co.second);
        // nearestPOI = POIFromSquare(gladiatorPos, gladiator->maze->getSquare(co.first, co.second));
        nearestPOI = getSquarePosition(gladiator->maze->getSquare(co.first, co.second));
        printf("NPOI : %lf %lf\n", nearestPOI.x, nearestPOI.y);
        // printf("Element is : %x %x\n", co.first, co.second);
        toGo.pop();
        puts("---");
    }

    // goTo(gladiator, nearestPOI, gladiatorPos);
    aim(gladiator, { nearestPOI.x, nearestPOI.y }, false);

    lastPos = gladiatorPos;
}