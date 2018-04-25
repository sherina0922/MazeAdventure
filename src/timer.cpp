//
//  cameraTracking.cpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//
//
//  modeVisuals.cpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/21/18.
//

#include "timer.hpp"
const int millis_to_sec = 1000;

//--------------------------------------------------------------
void Timer::TimerSetup() {
    // Timed mode setup
    timer_end = false;
    start_time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
//Draws the timer bar
void Timer::DrawTimedMode() {
    time_gui.draw(); //doesnt actually do anything rn
    if (!timer_end) {
        float timer;
        if (timer_paused) {
            timer = time_remaining;
        } else {
            timer = (MAX_TIME + start_time) - ofGetElapsedTimeMillis(); //start_time
        }
        
        ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
        ofDrawRectangle(20, 20, ofGetWidth() - (timer / MAX_TIME) * ofGetWidth(), 10);
        ofDrawBitmapString("Time left: " + std::to_string(timer / millis_to_sec) + " seconds", 5,
                           50); //Displays how much time remaining
        
        //Add count of mazes completed here
        
        if (timer <= 0) {
            timer_end = true;
        }
    } else {
        ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("TIME IS UP!", ofGetWidth() / 2, ofGetHeight() / 2);
        //ofDrawBitmapString(<#const T &textString#>, <#float x#>, <#float y#>); //print number of mazes completed
    }
}

//--------------------------------------------------------------
void Timer::ModeVisualsKeyPressed(int key) {
    switch (key) {
        case 'r':
            timer_end = false; //reset timer
            start_time = ofGetElapsedTimeMillis();
            break;
            
        case 'p':
            //PAUSE TIMER
            if (timer_paused) {
                timer_paused = false;
                SetStartTime(ofGetElapsedTimeMillis() + time_remaining - MAX_TIME);
                
            } else {
                timer_paused = true;
                float current_time = ofGetElapsedTimeMillis();
                time_remaining = (MAX_TIME + start_time) - current_time;
            }
            break;
    }
    
}

//--------------------------------------------------------------
void Timer::SetStartTime(float time) {
    start_time = time;
}
