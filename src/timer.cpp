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

//--------------------------------------------------------------
void Timer::TimerSetup() {
    // Timed mode setup
    timer_ended = false;
    start_time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
//Draws the timer bar
void Timer::DrawTimedMode() {
    if (!timer_ended) {
        float timer;
        
        if (timer_paused) {
            timer = time_remaining;
        } else {
            timer = (MAX_TIME + start_time) - ofGetElapsedTimeMillis(); //start_time
        }
        
        ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
        ofDrawRectangle(20, 20, ofGetWidth() - (timer / MAX_TIME) * ofGetWidth(), 10);
        ofDrawBitmapString("Time left: " + std::to_string(timer / MILLIS_TO_SEC) + " seconds", 5,
                           50); //Displays how much time remaining
        if (timer <= 0) {
            timer_ended = true;
        }
    }
}

//--------------------------------------------------------------
void Timer::TimerKeyPressed(int key) {
    switch (key) {
        case 't':
            timer_ended = false; //reset timer
            SetStartTime(ofGetElapsedTimeMillis());
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
