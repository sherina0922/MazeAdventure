//ofApp.h
#pragma once

#include "ofMain.h"
#include "maze.hpp"
#include "cameraTracking.hpp"

#define WIDTH 41
#define HEIGHT 21
#define START_X 2
#define START_Y 19
#define END_X 39
#define END_Y 19

class ofApp : public ofBaseApp{

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

    bool game_started = false;
    
    // Computer camera inputs
    bool USE_CAMERA_INPUT = false; //TRUE if player decides to use camera input to move; FALSE if otherwise and by default
    ofVideoGrabber comp_camera; // Computer Camera

    // 3D view camera
    ofEasyCam view_camera;


};
