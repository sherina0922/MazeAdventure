//ofApp.h
#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "maze.h"
#include "cameraTracking.hpp"
#include "character.hpp"
#include "../../../../../Applications/of_v0.9.8_osx_release/addons/ofxGui/src/ofxButton.h"

#define WIDTH 41
#define HEIGHT 21

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void visibilitySliderChanged(int & visilibility_slider);

    bool game_started = false;
    bool difficulty_chosen = false;
    bool race_chosen = false;
    
    //Character player;
    ofxPanel gui;
    ofxIntSlider visilibility_slider;
    ofxButton difficulty_button;
    ofxButton race_button;
    
    // Computer camera inputs
    bool USE_CAMERA_INPUT = false; //TRUE if player decides to use camera input to move; FALSE if otherwise and by default
    ofVideoGrabber comp_camera; // Computer Camera

    // 3D view camera
    ofEasyCam view_camera;


};
