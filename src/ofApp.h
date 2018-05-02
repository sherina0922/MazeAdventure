//ofApp.h
#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "maze.hpp"
#include "cameraTracking.hpp"
#include "character.hpp"
#include "timer.hpp"
#include "../../../../../Applications/of_v0.9.8_osx_release/addons/ofxGui/src/ofxButton.h"
#include "battleField.hpp"

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
    
    void visibilitySliderChanged(int & visilibility_slider);    // Changes the maze visibility
    void DrawPlayerDead();                                      // Draws the player dead screen
    void DrawTimedMode();                                       // Draws the timed mode visuals
    void DrawBattleField();                                     // Draws the battle in free mode visuals
    void DrawChooseGameMode();                                  // Draws the choose game mode screen
    void reset();                                               // Resets the entire game
    
    // Status variables
    bool game_mode_chosen = false;
    bool GAME_MODE_FREE = false; // TRUE if player decides to play free game mode (has battling)
    bool GAME_MODE_TIME = false; // TRUE if player decides to play time mode
     
    // Timed mode elements
    Timer current_timer;
    ofSoundPlayer pause_sound;
    
    // Free mode elements
    bool character_type_chosen = false;
    ofxPanel free_gui;
    ofxIntSlider visilibility_slider;
    ofxButton difficulty_button;
    ofxButton race_button;
    Character *player;
    Character *current_monster;
    Battle current_battle;
    
    // Camera and view elements
    bool using_camera_input = false; //TRUE if player decides to use camera input to move; FALSE if otherwise and by default
    CameraTracking comp_tracking;
    ofVideoGrabber comp_camera; // Computer Camera
    ofEasyCam view_camera; // 3D view camera
    Maze current_maze;
    ofTrueTypeFont font;
};
