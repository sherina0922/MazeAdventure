//
//  timer.cpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/21/18.
//

#include "timer.hpp"

/**
 * Sets up the timer and loads the game over sound
 */
void Timer::TimerSetup() {
    // Timed mode setup
    timer_ended = false;
    start_time = ofGetElapsedTimef();
    game_over_sound.load("game_over.wav");
}

/**
 * Draws the timer bar
 */
void Timer::DrawTimer() {
    if (!timer_ended) {
        float timer;
        if (timer_paused) {
            //draw paused screen
            ofBackground(0, 0, 0); //Set color BLACK
            timer = time_remaining;
            ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //set color WHITE
            ofDrawBitmapString("Press P to unpause!", ofGetWidth() * HALF, ofGetHeight() * HALF);
        } else {
            timer = (MAX_TIME + start_time) - ofGetElapsedTimeMillis(); //start_time
        }
        
        //draw time bar and time left
        ofSetColor(0, 0, FULL_COLOR);
        ofFill();
        ofDrawRectangle(TIMER_LOCATION, TIMER_LOCATION, ofGetWidth() - 2 * TIMER_LOCATION, TIMER_HEIGHT);
        ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //set color WHITE
        ofFill();
        ofDrawRectangle(TIMER_LOCATION, TIMER_LOCATION,
                        (ofGetWidth() - 2 * TIMER_LOCATION) - (timer / MAX_TIME) * (ofGetWidth() - 2 * TIMER_LOCATION),
                        TIMER_HEIGHT);
        ofDrawBitmapString("Time left: " + std::to_string(timer / MILLIS_TO_SEC) + " seconds", TIMER_LOCATION,
                           TIMER_LOCATION * 2 + TIMER_HEIGHT); //Displays how many seconds remaining
        if (timer <= 0) {
            game_over_sound.play();
            timer_ended = true;
        }
    }
}

/**
 * Determines whether to reset or pause the timer depending on the key pressed
 *
 * @param key - the Unicode value of the key pressed
 */
void Timer::TimerKeyPressed(int key) {
    switch (key) {
        case 't':
            //RESETS timer
            timer_ended = false;
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

/**
 * Sets the start time of the timer to the new time
 *
 * @param time - the new time
 */
void Timer::SetStartTime(float time) {
    start_time = time;
}

