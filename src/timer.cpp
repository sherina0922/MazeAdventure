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
    timer_ended = false;
    start_time = ofGetElapsedTimef();
    game_over_sound.load("game_over.wav");
    ofTrueTypeFont::setGlobalDpi(DEFAULT_DPI);
    font.load("courier_new.ttf", DEFAULT_FONT_SIZE, false);
}

/**
 * Draws the timer bar
 */
void Timer::DrawTimer() {
    if (!timer_ended) {
        float timer;
        if (timer_paused) {
            // draw paused screen
            ofBackground(0, 0, 0); // set color BLACK
            timer = time_remaining;
            ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); // set color WHITE
            font.drawString("Press P to unpause!", ofGetWidth() * HALF, ofGetHeight() * HALF);
        } else {
            timer = (MAX_TIME + start_time) - ofGetElapsedTimeMillis();
        }
        
        // draw remaining time bar
        ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //set color WHITE
        ofFill();
        ofDrawRectangle(TIMER_LOCATION, TIMER_LOCATION,
                        (ofGetWidth() - 2 * TIMER_LOCATION) - (1 - (timer / MAX_TIME)) * (ofGetWidth() - 2 * TIMER_LOCATION),
                        TIMER_HEIGHT);
        
        font.drawString("Time left: " + std::to_string(timer / MILLIS_TO_SEC) + " seconds", TIMER_LOCATION,
                           TIMER_LOCATION * 2 + TIMER_HEIGHT); // displays how many seconds remaining
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
            // resets timer
            timer_ended = false;
            SetStartTime(ofGetElapsedTimeMillis());
            break;
            
        case 'p':
            // pause timer
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

/**
 * Draws the time up game over screen in Timed mode
 *
 * @param mazes_completed - the number of mazes completed within time limit
 */
void Timer::DrawTimeUp(int mazes_completed) {
    ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    ofSetColor(0, 0, 0);
    font.drawString("TIME IS UP!\nNumber of mazes completed: "
                       + std::to_string(mazes_completed - 1),
                       ofGetWidth() * HALF, ofGetHeight() * HALF);
}

