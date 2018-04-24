//ofApp.cpp
#include "ofApp.h"
#include <iostream>
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
    //srand((unsigned)time(NULL));
    ofSetFrameRate(frame_rate);
    
    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetCircleResolution(50);
    
    view_camera.setDistance(initial_cam_distance); //Initial Distance : 150
    comp_camera.initGrabber(1280, 720);
    current_maze.FreeMazeSetup();
    
    current_timer.TimerSetup();
    
    // Free mode visilibility slider setup || Derived from guiExample
    free_gui.setup();
    visilibility_slider.addListener(this, &ofApp::visibilitySliderChanged);
    free_gui.add(visilibility_slider.setup("Visilibility", 1, 1, WIDTH)); //title, initial, min, max
    
    player.CharacterSetup();
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
    
    if (!game_mode_chosen) {
        ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
        ofDrawBitmapString("1. Free mode\n2. Timed mode", ofGetWidth() / 2, ofGetHeight() / 2);
        return;
    }
    if (GAME_MODE_FREE) {
        if (!character_type_chosen) { //Choosing character race settings
            player.ChooseCharacterType();
         return;
         }
        free_gui.draw();
        player.DrawCharacterStats();
    }
    
    view_camera.begin(); //perspective camera
    current_maze.DrawMaze(); //draws maze and player cubes
    
    if (USE_CAMERA_INPUT) {
        comp_tracking.DrawStylus(comp_camera.getWidth(), comp_camera.getHeight());
        current_maze.CameraMovePosition(comp_tracking.brightest_pixel_x, comp_tracking.brightest_pixel_y);
    }
    
    view_camera.end();
    
    if (GAME_MODE_TIME) {
        //setup timer here
        //if time is not up, continue to draw the maze and regenerate if needed
        current_timer.DrawTimedMode();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (game_mode_chosen && GAME_MODE_FREE && !character_type_chosen) {
        switch (key) {
            case '1':
            case '2':
            case '3':
            case '4':
                player.CharacterKeyPressed(key);
                character_type_chosen = true;
                return;
                
            default:
                break;
        }
    }
    switch (key) {
        case 'r': //reset entire game
            game_mode_chosen = GAME_MODE_FREE = GAME_MODE_TIME = false;
            USE_CAMERA_INPUT = false;
            setup();
            break;
            
        case 'c':
            //Use camera movement input
            USE_CAMERA_INPUT = !USE_CAMERA_INPUT;
            view_camera.setDistance(initial_cam_distance);
            if (view_camera.getMouseInputEnabled()) //ofEasyCam camera movement, lock or unlock model movement
                view_camera.disableMouseInput();
            else
                view_camera.enableMouseInput();
            break;
            
        case 'w':
        case 'a':
        case 's':
        case 'd':
            current_maze.MazeKeyPressed(key);
            break;
            
        case 'f':
            //Make full screen
            ofToggleFullscreen();
            break;
            
        case 't': //reset timer
        case 'p': //pause timer
            current_timer.ModeVisualsKeyPressed(key);
            break;
            
        case '1':
            if (!game_mode_chosen) {
                GAME_MODE_FREE = true;
                game_mode_chosen = true;
                current_maze.FreeMazeSetup();
            }
            break;
            
        case '2':
            if (!game_mode_chosen) {
                GAME_MODE_TIME = true;
                game_mode_chosen = true;
                current_maze.SetMode(SIZE);
                current_maze.TimeMazeSetup();
                current_timer.ModeVisualsKeyPressed('r');
            }
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
