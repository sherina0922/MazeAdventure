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

class Maze {
    public :
    
    char maze_structure[WIDTH][HEIGHT];
    int current_posX, current_posY; //the player's current position coordinates (in maze)
    int mode; //level of difficulty which determines visibility
    bool mode_chosen; //TRUE if mode is already determined; FALSE if not chosen yet
    bool game_ended = false;
    
    void SetMode(int new_mode);
    void SetGameEnded(bool new_status);
    void DrawMaze();
    void MazeSetup();
    void MazeKeyPressed(const char key);
    void CameraMovePosition(int camera_current_x, int camera_current_y);
    
};

#endif 

