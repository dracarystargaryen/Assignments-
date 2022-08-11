#include "Game.h"
#include <iostream>


using namespace std;


int main() {
    //Declare pathfinding in game
    pf::Game maze;

    //Load Map level by declaring the map level the start finding the path
    astar.loadMap("Level1.txt");
    astar.setMovement(true);
    auto path = astar.findPath(pf::Vec2i(0, 0), pf::Vec2i(10, 7), pf::heuristic::euclidean, 10); //automatically finds the position using heuristic analysis

    //Finds the coordinates of the game 
    for (const auto& coord : path) {
        std::cout << coord.x << ", " << coord.y << "\n";
    }
    system("pause");
    return 0;
}