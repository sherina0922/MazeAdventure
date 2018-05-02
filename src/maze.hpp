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
    vector< vector <char> > maze_structure;
    int current_posX, current_posY;         // the player's current position coordinates (in maze)
    int start_x, start_y;                   // the starting position
    int end_x, end_y;                       // the exit position
    int visibility;                         // the visibility of the maze
    
    bool maze_completed = false;
    bool game_ended = false;
    bool inBattleMode = false;
    bool free_game_mode = false;
    
    std::vector < vector< vector <char> > > generated_maze_vector;
    Character *maze_copy_player;
    ofSoundPlayer next_maze_sound;
    ofSoundPlayer win_sound;
    ofSoundPlayer game_over_sound;
    
    bool picture_taken = false;
    bool image_loaded = false;
    ofImage player_box_image;
    
    int number_games = 0;
    
    void SetVisibility(int new_visibility);                                 // Sets the visibility
    void SetMazeCompleted(bool new_status);                                 // Sets the status of maze completed
    void DrawMaze();                                                        // Draws the maze and player cubes
    void FreeMazeSetup(Character *current_player);                          // Sets up the maze for free mode
    void TimeMazeSetup();                                                   // Sets up the maze for timed mode
    void MazeKeyPressed(const char key);                                    // Determines direction according to key pressed
    void CameraMovePosition(int camera_current_x, int camera_current_y);    // Determines direction according to camera input
    void CheckGameStatus();                                                 // Checks if game ended or in battle mode
    void SetInBattleMode(bool isTrue);                                      // Sets the maze status to battle mode or not
    void ReadMazeFromFile();                                                // Reads the maze data from text files
    int BoxTranslateCoordinates(bool isFreeMode, int location, bool isX);   // Translates the location of boxes
    void DrawWin();                                                         // Draws the win screen
    
};


