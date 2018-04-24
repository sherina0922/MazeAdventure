//
//  mazeGenerator.hpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/22/18.
//

#ifndef mazeGenerator_hpp
#define mazeGenerator_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <stack>
#include <fstream>
#include <vector>

#include "constants.cpp"
/********************************
 * USED FOR THE SIZE OF THE MAZE *
 *   Must be an odd number for   *
 *    maze traversal reasons     *
 ********************************/

// CELL STRUCTURE
struct Cell
{
    bool visited;
    bool top_wall;
    bool bot_wall;
    bool left_wall;
    bool right_wall;
    char value; //# if wall; ' ' if empty
};

// FUNCTION DECLARATIONS
void PopulateNewMaze();
void Initialize(Cell Level[][SIZE]);
void Redraw(Cell Level[][SIZE]);
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY);
void SaveMaze(Cell Level[][SIZE]);
bool MazeValid(Cell check_maze[][SIZE]);
std::string GetFileContents();


#endif /* mazeGenerator_hpp */