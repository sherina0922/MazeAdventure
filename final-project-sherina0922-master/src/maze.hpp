//
//  maze.hpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#pragma once

#include <stdio.h>
#include "ofMain.h"

#define WIDTH 41
#define HEIGHT 21

extern int current_posX, current_posY; //the player's current position coordinates (in maze)
extern int exit_posX, exit_posY; //the postion coordinates of the exit/goal
extern char maze_structure[WIDTH][HEIGHT];
extern int mode; //level of difficulty which determines visibility
extern bool mode_chosen; //TRUE if mode is already determined; FALSE if not chosen yet

class Maze {
    public :
    
     static void DrawMaze();
     static void MazeSetup();
     static void MazeKeyPressed(const char key);
};

