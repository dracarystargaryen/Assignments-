#include "AStar.h"
#include <iostream>

using namespace std;

int main() {

    //Declare pathfinding in game
    pf::AStar maze;

    //Algorithm begins searching for path as the mad loads
    maze.loadMap("Level1.txt");
    maze.setDiagonalMovement(true);
    auto path = maze.findPath(pf::PathFinderAlgo(0, 0), pf::PathFinderAlgo(10, 7), pf::heuristic::euclidean, 10); //automatically finds the position using heuristic analysis

    //Finds the coordinates of the game 
    for (const auto& coord : path) {
        cout << coord.i << ", " << coord.j << "\n";
    }
    system("pause");
    return 0;
}
