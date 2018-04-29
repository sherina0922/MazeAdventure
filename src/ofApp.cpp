//ofApp.cpp
#include "ofApp.h"
#include <iostream>
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(FRAME_RATE);
    
    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetCircleResolution(50);
    
    view_camera.setDistance(INITIAL_VIEW_DISTANCE);
    comp_camera.initGrabber(1280, 720);
    current_maze.FreeMazeSetup(player);
    
    current_timer.TimerSetup();
    
    // Free mode visilibility slider setup || Derived from guiExample
    free_gui.setup();
    visilibility_slider.addListener(this, &ofApp::visibilitySliderChanged);
    free_gui.add(visilibility_slider.setup("Visilibility", 1, 1, WIDTH)); //title, initial, min, max
    
    player = new Character();
    player->CharacterSetup();
}

//--------------------------------------------------------------
void ofApp::update() {
    if (USE_CAMERA_INPUT) {
        comp_tracking.FindPoint(comp_camera);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0, 0, 0);
    
     /*
     //drawing game over screen
     if (player->player_stats.isDead && GAME_MODE_FREE) {
     ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
     ofDrawBitmapString("GAME OVER!", ofGetWidth() / 2, ofGetHeight() / 2);
     return;
     } */
    
    if (!game_mode_chosen) {
        ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
        ofDrawBitmapString("Choose which mode to play\n1. Free mode\n2. Timed mode", ofGetWidth() * HALF, ofGetHeight() * HALF);
        return;
    }
    
    if (GAME_MODE_FREE) {
        if (!character_type_chosen) { //Choosing character type settings
            player->ChooseCharacterType();
            return;
        }
        free_gui.draw(); //draws visibility slider
        player->DrawCharacterStats();
    }
    
    view_camera.begin(); //perspective camera
    
    if (current_maze.inBattleMode) {
        //current_battle.InitiateBattle(player, current_maze.at(current_maze.current_posX).at(current_maze.current_posY));
        view_camera.setDistance(INITIAL_VIEW_DISTANCE); //reset and lock view
        view_camera.end();
        current_maze.inBattleMode = !current_battle.DrawBattle(player, player, current_battle.stop_clicked); //whether or not in battle mode determined by battle result
    } else {
        current_maze.DrawMaze(); //draw maze and player cubes
    }
    
    if (USE_CAMERA_INPUT) {
        comp_tracking.DrawStylus(comp_camera.getWidth(), comp_camera.getHeight());
        current_maze.CameraMovePosition(comp_tracking.brightest_pixel_x, comp_tracking.brightest_pixel_y);
    }
    
    view_camera.end();
    
    if (GAME_MODE_TIME) {
        //setup timer here
        //if time is not up, continue to draw the maze and regenerate if needed
        if (current_maze.game_ended) {
            ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
            ofSetColor(0, 0, 0);
            ofDrawBitmapString("CONGRATULATIONS!\nYOU WIN!", ofGetWidth() * HALF, ofGetHeight() * HALF);
            return;
        }
        if (current_timer.timer_ended) {
            ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
            ofSetColor(0, 0, 0);
            ofDrawBitmapString("TIME IS UP!\nNumber of mazes completed: " + std::to_string(current_maze.number_games - 1)
                               , ofGetWidth() * HALF, ofGetHeight() * HALF);
        } else {
            current_timer.DrawTimer();
        }
    }
}

//--------------------------------------------------------------
static void reset(ofApp &object) {
    object.game_mode_chosen = object.GAME_MODE_FREE = object.GAME_MODE_TIME = false;
    object.USE_CAMERA_INPUT = false;
    object.character_type_chosen = false;
    
    object.current_maze.inBattleMode = object.current_maze.maze_completed = false;
    object.current_maze.number_games = 0;
    
    object.current_battle.radius = INITIAL_RADIUS;
    
    object.current_timer.timer_paused = false;
    object.current_timer.TimerKeyPressed('t');
    
    object.view_camera.reset();
    
    object.setup();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (game_mode_chosen && GAME_MODE_FREE && !character_type_chosen) {
        switch (key) { //choosing character type
            case '1':
            case '2':
            case '3':
            case '4':
                player->CharacterKeyPressed(key);
                character_type_chosen = true;
                return;
                
            default:
                break;
        }
    }
    switch (key) {
        case 'r': //reset entire game
            //make separate reset method for this
            reset(*this);
            break;
            
        case 'c':
            //Use camera movement input
            USE_CAMERA_INPUT = !USE_CAMERA_INPUT;
            view_camera.reset();
            if (view_camera.getMouseInputEnabled()) //ofEasyCam camera movement, lock or unlock model movement
                view_camera.disableMouseInput();
            else
                view_camera.enableMouseInput();
            break;
            
        case 'w': //movement keys
        case 'a':
        case 's':
        case 'd':
            if (!current_timer.timer_paused) {
                current_maze.MazeKeyPressed(key);
                draw();
            }
            break;
            
        case 'f':
            //Make full screen
            ofToggleFullscreen();
            break;
            
        case 't': //reset timer
        case 'p': //pause timer
            current_timer.TimerKeyPressed(key);
            break;
            
        case '1': //choosing free game mode
            if (!game_mode_chosen) {
                game_mode_chosen = GAME_MODE_FREE = true;
                current_maze.FreeMazeSetup(player);
            }
            break;
            
        case '2': //choosing timed game mode
            if (!game_mode_chosen) {
                game_mode_chosen = GAME_MODE_TIME = true;
                current_maze.SetMode(SIZE); //set initial mode visibility to the size
                current_maze.free_game_mode = false;
                current_maze.TimeMazeSetup();
                current_timer.TimerKeyPressed('t');
            }
            break;
        case 'm':
            //cheat command to exit battle sequence
            current_maze.inBattleMode = false;
            break;
            
        case ' ': //stop circle in battle
            current_battle.stop_clicked = true;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::visibilitySliderChanged(int &visilibility_slider) {
    current_maze.SetMode(visilibility_slider);
    current_maze.DrawMaze();
    
    current_maze.SetMode(visilibility_slider);
    current_maze.DrawMaze();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}
