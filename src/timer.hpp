//
//  modeVisuals.hpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/21/18.
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "maze.hpp"

#include "constants.cpp"

class Timer {
public:
    float start_time;
    bool timer_ended;
    bool timer_paused = false;
    float time_remaining;
    ofSoundPlayer game_over_sound;
    ofTrueTypeFont font;
    
    void TimerSetup();                      // Sets up the timer
    void DrawTimer();                       // Draws the timer
    void TimerKeyPressed(int key);          // Determines pause or reset
    void SetStartTime(float time);          // Sets start time to new time
    void DrawTimeUp(int mazes_completed);   // Draws the time up screen
    
};


