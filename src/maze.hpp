//
//  maze.hpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "mazeGenerator.hpp"
#include <vector>
#include <fstream>

#include "constants.cpp"
#include "character.hpp"
#include "battleField.hpp"

//static bool inBattleMode = false;

class Maze {
    public :
    
    vector< vector <char> > maze_structure; //need to make vector so can change size
    
    //char time_maze_structure[21][21];
    int current_posX, current_posY; //the player's current position coordinates (in maze)
    int start_x, start_y;
    int end_x, end_y;
    int mode; //level of difficulty which determines visibility
    //bool mode_chosen; //TRUE if mode is already determined; FALSE if not chosen yet
    bool game_ended = false;
    bool inBattleMode = false;
    std::vector < vector< vector <char> > > generated_maze_vector;
    
    Character *maze_copy_player;
    
    ofSoundPlayer sound;
    
    int number_games = 0;
    bool free_game_mode = false;
    
    void SetMode(int new_mode);
    void SetGameEnded(bool new_status);
    void DrawMaze();
    void FreeMazeSetup(Character *current_player);
    void TimeMazeSetup();
    void MazeKeyPressed(const char key);
    void CameraMovePosition(int camera_current_x, int camera_current_y);
    void CheckGameStatus(int posX, int posY);
    void SetInBattleMode(bool isTrue);
    void ReadMazeFromFile();
    
};


