#include "ofApp.h"
#include <iostream>
#include <cmath>

/**
 * Sets up and initializes the basic elements of the different game components
 */
void ofApp::setup() {
    ofSetFrameRate(FRAME_RATE);
    
    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetCircleResolution(50);
    
    view_camera.setDistance(INITIAL_VIEW_DISTANCE);
    comp_camera.initGrabber(1280, 720);
    current_maze.FreeMazeSetup(player);
    
    current_timer.TimerSetup();
    pause_sound.load("pause_sound.wav");
    
    // Free mode visilibility slider setup || Derived from guiExample
    free_gui.setup();
    visilibility_slider.addListener(this, &ofApp::visibilitySliderChanged);
    free_gui.add(visilibility_slider.setup("Visilibility", INITIAL_VISIBILITY, 1, WIDTH)); //title, initial, min, max
    
    player = new Character();
    current_monster = new Character();
    player->CharacterSetup();
    current_monster->CharacterSetup();
}

/**
 * Updates the different game components
 */
void ofApp::update() {
    if (using_camera_input) {
        comp_tracking.FindPoint(comp_camera);
    }
}

/**
 * Draws the display depending on the status of different variables
 */
void ofApp::draw() {
    ofBackground(0, 0, 0);
    
    if (!game_mode_chosen) {
        ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
        ofDrawBitmapString("Choose which mode to play\n1. Free mode\n2. Timed mode", ofGetWidth() * HALF,
                           ofGetHeight() * HALF);
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
        view_camera.end();
        if (current_monster->monster_not_init) {
            //initialize monster's stats
            current_monster->DetermineMonster(
                                              current_maze.maze_structure[current_maze.current_posX][current_maze.current_posY]);
            current_monster->monster_not_init = false;
        }
        //whether or not in battle mode determined by battle result , current_battle.stop_clicked
        current_maze.inBattleMode = !current_battle.DrawBattle(player, current_monster);
        
    } else {
        current_maze.DrawMaze(); //draw maze and player cubes
        current_monster->monster_not_init = true;
    }
    
    if (using_camera_input) {
        comp_tracking.DrawStylus(comp_camera.getWidth(), comp_camera.getHeight());
        current_maze.CameraMovePosition(comp_tracking.brightest_pixel_x, comp_tracking.brightest_pixel_y);
    }
    
    view_camera.end();
    
    if (player->player_stats.isDead) {
        current_maze.SetMazeCompleted(true);
        ofBackground(0, 0, 0);
        ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
        ofDrawBitmapString("YOU DIED!", ofGetScreenWidth() * HALF, ofGetScreenHeight() * HALF);
    }
    
    if (GAME_MODE_TIME) {
        //if time is not up, continue to draw the maze and regenerate
        if (current_maze.game_ended) {
            ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
            ofSetColor(0, 0, 0);
            ofDrawBitmapString("CONGRATULATIONS!\nYOU WIN!", ofGetWidth() * HALF, ofGetHeight() * HALF);
            return;
        }
        if (current_timer.timer_ended) {
            ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
            ofSetColor(0, 0, 0);
            ofDrawBitmapString("TIME IS UP!\nNumber of mazes completed: " + std::to_string(current_maze.number_games - 1),
                               ofGetWidth() * HALF, ofGetHeight() * HALF);
        } else {
            current_timer.DrawTimer();
        }
    }
}

/**
 * Resets the game
 *
 * @param &object - the ofApp object to be reset
 */
static void reset(ofApp &object) {
    object.game_mode_chosen = object.GAME_MODE_FREE = object.GAME_MODE_TIME = false;
    object.using_camera_input = false;
    object.character_type_chosen = false;
    
    object.current_maze.inBattleMode = object.current_maze.maze_completed = false;
    object.current_maze.number_games = 0;
    
    object.current_battle.radius = INITIAL_RADIUS;
    
    object.current_timer.timer_paused = false;
    object.current_timer.TimerKeyPressed('t');
    
    object.view_camera.reset();
    
    object.setup();
}

/**
 * Determines the executable action based on the key pressed
 *
 * @param key - the Unicode value of the key pressed
 */
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
            reset(*this);
            break;
            
        case 'c':
            //Use camera movement input
            using_camera_input = !using_camera_input;
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
            
        case 'p': //pause timer
            current_timer.TimerKeyPressed(key);
            pause_sound.play();
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
                current_maze.SetVisibility(SIZE); //set initial mode visibility to the size
                current_maze.free_game_mode = false;
                current_maze.TimeMazeSetup();
                current_timer.TimerKeyPressed('t'); //"reset" or initialize timer to start
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

/**
 * Changes the maze visibility depending on the status of the visibility slider
 *
 * @param visilibility_slider - the slider gui that allows the user to change the visibility
 */
void ofApp::visibilitySliderChanged(int &visilibility_slider) {
    current_maze.SetVisibility(visilibility_slider);
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



