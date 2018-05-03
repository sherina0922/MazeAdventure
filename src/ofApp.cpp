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
    ofSetCircleResolution(CONSTANT_CIRCLE_RESOLUTION);
    
    view_camera.setDistance(INITIAL_VIEW_DISTANCE);
    comp_camera.initGrabber(GRABBER_X, GRABBER_Y);
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
    
    ofTrueTypeFont::setGlobalDpi(DEFAULT_DPI);
    font.load("courier_new.ttf", DEFAULT_FONT_SIZE, false);
}

/**
 * Updates the different game components
 */
void ofApp::update() {
    comp_camera.update();
    if (using_camera_input) {
        comp_tracking.FindPoint(comp_camera);
    }
}

/**
 * Draws the display depending on the status of different variables
 */
void ofApp::draw() {
    ofBackground(0, 0, 0); // Set background color to BLACK
    
    if (!game_mode_chosen) {
        DrawChooseGameMode();
        return;
    }
    if (GAME_MODE_FREE) {
        if (!current_maze.picture_taken) {
            // take picture
            comp_camera.draw(0, 0);
            return;
        } else if (!character_type_chosen) {
            player->ChooseCharacterType();
            return;
        } else if (!player->player_name_set) {
            player->DrawPlayerName();
            return;
        }
        free_gui.draw(); // draws visibility slider
        player->DrawCharacterStats();
    } else {
        // timed mode
        if (!current_timer.max_time_set) {
            current_timer.DrawSetMaxTime();
            return;
        }
    }
    
    view_camera.begin(); // perspective camera
    
    if (current_maze.inBattleMode) {
        using_camera_input = false;
        DrawBattleField();
    } else {
        current_maze.DrawMaze(); // draw maze and player cubes
        current_monster->monster_not_init = true;
    }
    if (using_camera_input) {
        comp_tracking.DrawStylus(comp_camera.getWidth(), comp_camera.getHeight());
        current_maze.CameraMovePosition(comp_tracking.brightest_pixel_x, comp_tracking.brightest_pixel_y);
    }
    
    view_camera.end();
    
    if (player->player_stats.isDead) {
        current_maze.SetMazeCompleted(true);
        DrawPlayerDead();
    }
    if (GAME_MODE_TIME) {
        DrawTimedMode();
    }
}


/**
 * Draws the choose game mode screen
 */
void ofApp::DrawChooseGameMode() {
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    font.drawString("Choose which mode to play\n1. Free mode\n2. Timed mode", ofGetWidth() * HALF - CHOOSE_MODE_OFFSET_X,
                    ofGetHeight() * HALF - CHOOSE_MODE_OFFSET_Y);
}

/**
 * Draws the battle mini-game in the free mode
 */
void ofApp::DrawBattleField() {
    view_camera.end();
    if (current_monster->monster_not_init) {
        // initialize monster's stats
        current_monster->DetermineMonster(current_maze.maze_structure[current_maze.current_posX][current_maze.current_posY]);
        current_monster->monster_not_init = false;
    }
    // whether or not in battle mode determined by battle result
    current_maze.inBattleMode = !current_battle.DrawBattle(player, current_monster);
}

/**
 * Draws the timed mode visuals
 */
void ofApp::DrawTimedMode() {
    // if time is not up, continue to draw the maze and regenerate
    if (current_maze.game_ended) {
        ofTranslate(ofGetWidth() * HALF, ofGetHeight() * HALF);
        current_maze.DrawWin();
        return;
    }
    if (current_timer.timer_ended) {
        current_timer.DrawTimeUp(current_maze.number_games);
    } else {
        current_timer.DrawTimer();
    }
}

/**
 * Draws the screen when the player has died in free mode
 */
void ofApp::DrawPlayerDead() {
    ofBackground(0, 0, 0);
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    font.drawString("YOU DIED!", ofGetScreenWidth() * HALF, ofGetScreenHeight() * HALF);
}

/**
 * Resets the game
 */
void ofApp::reset() {
    game_mode_chosen = GAME_MODE_FREE = GAME_MODE_TIME = false;
    using_camera_input = false;
    character_type_chosen = false;
    
    current_maze.MazeReset();
    current_battle.BattleReset();
    current_timer.TimerReset();
    player->CharacterReset();
    
    view_camera.reset();
    ofDisableNormalizedTexCoords();
    setup();
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
    } else if (!player->player_name_set && character_type_chosen && GAME_MODE_FREE) {
        player->CharacterKeyPressed(key);
        return;
    } else if (GAME_MODE_TIME && !current_timer.max_time_set) {
        current_timer.TimerKeyPressed(key);
        return;
    }
    
    switch (key) {
        case 'r': // reset entire game
            reset();
            break;
            
        case 'c':
            if (GAME_MODE_FREE && !player->player_name_set) {
                return;
            }
            // use camera movement input
            using_camera_input = !using_camera_input;
            view_camera.reset();
            if (view_camera.getMouseInputEnabled()) // ofEasyCam camera movement, lock or unlock model movement
                view_camera.disableMouseInput();
            else
                view_camera.enableMouseInput();
            break;
            
        case 'w': // movement keys
        case 'a':
        case 's':
        case 'd':
            if (!current_timer.timer_paused) {
                current_maze.MazeKeyPressed(key);
                draw();
            }
            break;
            
        case 'f':
            // make full screen
            ofToggleFullscreen();
            break;
            
        case 'p': // pause timer
            if (GAME_MODE_TIME) {
                current_timer.TimerKeyPressed(key);
                pause_sound.play();
            }
            break;
            
        case '1': // choosing free game mode
            if (!game_mode_chosen) {
                game_mode_chosen = GAME_MODE_FREE = true;
                current_maze.FreeMazeSetup(player);
            }
            break;
            
        case '2': // choosing timed game mode
            if (!game_mode_chosen) {
                game_mode_chosen = GAME_MODE_TIME = true;
                current_maze.SetVisibility(SIZE); //set initial mode visibility to the size
                current_maze.free_game_mode = false;
                current_maze.TimeMazeSetup();
                current_timer.TimerKeyPressed('t'); //"reset" or initialize timer to start
            }
            break;
        case 'm':
            // flee, automatically leave battle mode but will not regain health
            current_maze.inBattleMode = false;
            break;
            
        case ' ': // take screenshot or stop circle in battle
            if (!current_maze.picture_taken) {
                current_maze.MazeTakePicture();
                return;
            }
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



