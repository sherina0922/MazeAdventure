//ofApp.cpp
#include "ofApp.h"
#include <iostream>
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
    srand((unsigned)time(NULL));

    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetCircleResolution(40);

    view_camera.setDistance(150); //150

    //If using camera input
    comp_camera.initGrabber(1280, 720);

    Maze::MazeSetup();
    
    current_posX = START_X;
    current_posY = START_Y;
    exit_posX = END_X;
    exit_posY = END_Y;
    
    //Character::CharacterSetup();
}

//--------------------------------------------------------------
void ofApp::update() {
    if (USE_CAMERA_INPUT) {
        CameraTracking::FindPoint(comp_camera);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0,0,0);
    /*
    if (!race_chosen) {
        ofDrawBitmapString(Character::GenerateRaceMenuString(), ofGetScreenWidth() / 2, ofGetScreenHeight() / 2);
    }
    if (!difficulty_chosen) {
        std::string difficulty_options = "1. Easy\n2. Medium\n3. Difficult";
        ofDrawBitmapString(difficulty_options, ofGetScreenWidth() / 2, ofGetScreenHeight() / 2);
    }
    if (!game_started) {
        //ofDrawBitmapString(<#const T &textString#>, <#float x#>, <#float y#>);
    } else { */
        view_camera.begin();

        //Draws the maze
    Maze::DrawMaze();

        if (USE_CAMERA_INPUT) {
            CameraTracking::DrawStylus(comp_camera.getWidth(), comp_camera.getHeight());
        }
        view_camera.end();
    //}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key > 0 && key < 4) {
        
    }
    switch (key) {
        case 'c':
            //Use camera movement input
            USE_CAMERA_INPUT  = !USE_CAMERA_INPUT;
            view_camera.setDistance(150);
            if (view_camera.getMouseInputEnabled()) //ofEasyCam camera movement, lock or unlock model movement
                view_camera.disableMouseInput();
            else
                view_camera.enableMouseInput();
            break;
            
        case 'w':
        case 'a':
        case 's':
        case 'd':
            Maze::MazeKeyPressed(key);
            break;
            
        case 'f':
            //Make full screen
            ofToggleFullscreen();
            break;

        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

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
