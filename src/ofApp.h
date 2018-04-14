//ofApp.h
#pragma once

#include "ofMain.h"
#define WIDTH 41
#define HEIGHT 21

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

    // Game variables
    int current_posX, current_posY; //the player's current position coordinates (in maze)
    int exit_posX, exit_posY; //the postion coordinates of the exit/goal
    char maze[WIDTH][HEIGHT];

    int mode; //level of difficulty which determines visibility
    bool mode_chosen; //TRUE if mode is already determined; FALSE if not chosen yet

    // Computer camera inputs
    bool use_camera_input; //TRUE if player decides to use camera input to move; FALSE if otherwise and by default
    ofVideoGrabber comp_camera; // Computer Camera
    int brightest_pixel_x; //X-coordinate of brightest pixel
    int brightest_pixel_y; //Y-coordinate of brightest pixel

    // 3D view camera
    ofEasyCam view_camera;


};
