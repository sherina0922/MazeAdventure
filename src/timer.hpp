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
    
    //Timed mode variables
    float start_time;
    bool timer_ended;
    bool timer_paused = false;
    float time_remaining;
    
    void TimerSetup();
    void DrawTimedMode();
    void TimerKeyPressed(int key);
    void SetStartTime(float time);
    
};


