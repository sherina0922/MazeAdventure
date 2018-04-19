//
//  maze.hpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include "ofMain.h"

#define WIDTH 41
#define HEIGHT 21 
#define CUBE_SIZE 5.0
#define START_X 2
#define START_Y 19
#define END_X 39
#define END_Y 19
#define FULL_COLOR 255

static char maze_structure[WIDTH][HEIGHT];
static int current_posX, current_posY; //the player's current position coordinates (in maze)
static int mode; //level of difficulty which determines visibility
static bool mode_chosen; //TRUE if mode is already determined; FALSE if not chosen yet
static bool game_ended = false;

class Maze {
    public :
    
    static void SetMode(int new_mode);
    static void SetGameEnded(bool new_status);
    static void DrawMaze();
    static void MazeSetup();
    static void MazeKeyPressed(const char key);
    
};

#endif 

