//ofApp.cpp
#include "ofApp.h"
#include <iostream>
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
    srand((unsigned)time(NULL));
    ofSetFrameRate(60);

    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetCircleResolution(50);

    view_camera.setDistance(150); //Initial Distance : 150

    //If using camera input
    comp_camera.initGrabber(1280, 720);

    Maze::MazeSetup();
    
    // Button/Slider Setup || Derived from guiExample
    gui.setup();
    visilibility_slider.addListener(this, &ofApp::visibilitySliderChanged);
    gui.add(visilibility_slider.setup("Visilibility", 1, 1, WIDTH)); //title, initial, min, max
    
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
    gui.draw();
    
    /*
    if (!race_chosen) { //Choosing character race settings
        ofDrawBitmapString(Character::GenerateRaceMenuString(), ofGetScreenWidth() / 2, ofGetScreenHeight() / 2);

    } */
    //else {
        view_camera.begin(); //perspective camera

        Maze::DrawMaze(); //draws maze and player cubes

        if (USE_CAMERA_INPUT) {
            CameraTracking::DrawStylus(comp_camera.getWidth(), comp_camera.getHeight());
        }
        view_camera.end();

    //} //commented out else bracket
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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
void ofApp::visibilitySliderChanged(int &visilibility_slider){
    Maze::SetMode(visilibility_slider);
    Maze::DrawMaze();
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
