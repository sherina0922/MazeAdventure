//
//  mazeGenerator.hpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/22/18.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <stack>
#include <fstream>
#include <vector>

#include "constants.cpp"

// CELL STRUCTURE
struct Cell
{
    bool visited;
    bool top_wall;
    bool bottom_wall;
    bool left_wall;
    bool right_wall;
    char value; // '#' if wall; ' ' if empty
};

// FUNCTION DECLARATIONS
void PopulateNewMaze();
void InitializeMaze(Cell Level[][SIZE]);
void Redraw(Cell Level[][SIZE]);
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY);
void KnockWall(Cell structure[][SIZE], int &currentX, int &currentY, int direction);
void SaveMaze(Cell Level[][SIZE]);
bool MazeValid(Cell check_maze[][SIZE]);
std::string GetFileContents();

