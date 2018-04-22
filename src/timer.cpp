//
//  modeVisuals.cpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/21/18.
//

#include "timer.hpp"

const float MAX_TIME = 150000.0;

void Timer::TimerSetup() {
    // Timed mode setup
    timer_end = false;
    start_time = ofGetElapsedTimef();
}

//Draws the timer bar
void Timer::DrawTimedMode() {
    time_gui.draw(); //doesnt actually do anything rn
    if (!timer_end) {
        float timer = (MAX_TIME + start_time) - ofGetElapsedTimeMillis(); //start_time
        
        ofSetColor(255, 255, 255);
        ofDrawRectangle(20, 20, ofGetWidth() - (timer / MAX_TIME)*ofGetWidth(), 10);
        ofDrawBitmapString("Time left: " + std::to_string(timer / 1000) + " seconds", 5, 50); //Displays how much time remaining
        //Add count of mazes completed here
        
        if (timer <= 0) {
            timer_end = true;
        }
    } else {
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("TIME IS UP!", ofGetWidth() / 2, ofGetHeight() / 2);
    }
}

void Timer::ModeVisualsKeyPressed(int key) {
    switch (key) {
    case 'r':
        timer_end = false; //reset timer
        start_time = ofGetElapsedTimeMillis();
        break;
        
    case 'p':
        //PAUSE TIMER
        break;
    }
    
}

void Timer::SetStartTime() {
    start_time = ofGetElapsedTimef();
}
