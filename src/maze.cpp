//
//  maze.cpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#include "maze.hpp"
#include <cmath>

/**
 * Sets the visibility of the maze
 *
 * @param new_mode - the new visibility
 */
void Maze::SetVisibility(int new_visibility) {
    if (new_visibility > 1) {
        visibility = new_visibility;
    } else {
        visibility = MIN_VISIBILITY;
    }
}

/**
 * Sets the status of the maze to completed or not
 *
 * @param new_status - new status of the maze
 */
void Maze::SetMazeCompleted(bool new_status) {
    maze_completed = new_status;
}

/**
 * Sets the status of the maze to in-battle-mode or not
 *
 * @param isTrue - new status of the maze
 */
void Maze::SetInBattleMode(bool isTrue) {
    inBattleMode = isTrue;
}

/**
 * Translates the location of the box
 *
 * @param isFreeMode - TRUE if in free mode; FALSE if in timed mode
 * @param location - the integer location of the point
 * @param isX - TRUE if the location is the X coordinate; FALSE if the Y coordinate
 * @return the translated location
 */
int Maze::BoxTranslateCoordinates(bool isFreeMode, int location, bool isX) {
    if (!isX) {
        return -location * CUBE_SIZE + MAZE_TRANSLATE * HALF;
    }
    if (isFreeMode) {
        if (isX) {
            return location * CUBE_SIZE - MAZE_TRANSLATE;
        }
    } else {
        if (isX) {
            return location * CUBE_SIZE - MAZE_TRANSLATE * HALF;
        }
    }
}

/**
 * Draws the maze
 */
void Maze::DrawMaze() {
    if (free_game_mode && picture_taken && !image_loaded) {
        ofEnableNormalizedTexCoords();
        player_box_image.load("player_screenshot.png");
        image_loaded = true;
    }
    
    if (maze_completed) {
        if (free_game_mode) {
            DrawWin();
            return;
        } else {
            maze_completed = false;
            TimeMazeSetup();
            return;
        }
    } else {
        for (int current_y = 0; current_y < HEIGHT; current_y++) {
            for (int current_x = 0; current_x < WIDTH; current_x++) {
                ofSetColor(0, 0, 0); // set default to BLACK
                if (std::abs(current_x - current_posX) < visibility &&
                    std::abs(current_y - current_posY) < visibility) {
                    // if within the visibility
                    ofPushMatrix();
                    ofTranslate(BoxTranslateCoordinates(free_game_mode, current_x, true),
                                BoxTranslateCoordinates(free_game_mode, current_y, false), 0);
                    if (maze_structure[current_x][current_y] == '#') {
                        ofSetColor(GRAY, GRAY, GRAY); // set to TRANSPARENT GRAY for maze walls
                    }
                    ofFill();
                    ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
                    ofNoFill();
                    ofSetColor(0, 0, 0); // set to BLACK for outline
                    ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
                    ofPopMatrix();
                }
            }
        }

        // draw player box
        ofPushMatrix();
        ofTranslate(BoxTranslateCoordinates(free_game_mode, current_posX, true),
                    BoxTranslateCoordinates(free_game_mode, current_posY, false), 0);
        if (free_game_mode && picture_taken) {
            // Code below derived from ofBox example
            // Use image of user on player box
            player_box_image.bind();
            ofFill();
            ofSetColor(FULL_COLOR);
            ofDrawBox(CUBE_SIZE);
            player_box_image.unbind();
        } else if (!free_game_mode) {
            ofSetColor(FULL_COLOR, 0, 0); // set to RED
            ofFill();
            ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
        }
        ofNoFill();
        ofSetColor(0);
        ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
        ofPopMatrix();
        
        // draw goal box
        ofPushMatrix();
        ofTranslate(BoxTranslateCoordinates(free_game_mode, end_x, true),
                    BoxTranslateCoordinates(free_game_mode, end_y, false), 0);
        ofSetColor(0.0, FULL_COLOR, 0.0); // set to GREEN
        ofFill();
        ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
        ofNoFill();
        ofSetColor(0);
        ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
        ofPopMatrix();
    }
}

/**
 * Draws the win screen
 */
void Maze::DrawWin() {
    ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("CONGRATULATIONS!\nYOU WIN!", 0, 0);
    return;
}

/**
 * Reads in maze structure data from a text file according to the game mode and loads the sound effects
 */
void Maze::ReadMazeFromFile() {
    using std::vector;
    using std::string;
    string line;
    string file_contents;
    string file_name = "";
    
    if (free_game_mode) {
        // Maze below derived from https://www.youtube.com/watch?v=9Ozu-B2HLY4
        file_name = "free-maze-data.txt";
    } else {
        // Maze below randomly generated by algorithm and manually inserted in file
        file_name = "maze-data.txt";
    }
    ofBuffer buffer = ofBufferFromFile(file_name);
    for (ofBuffer::Line iterator = buffer.getLines().begin(), end = buffer.getLines().end(); iterator != end; ++iterator) {
        line = *iterator;
        if(!line.empty()) {
            file_contents += line;
        }
    }
    
    if (!free_game_mode) { // time game mode
        int vector_index = 0;
        vector<string> separated_maze_string_vector(file_contents.length() / CHARS_IN_MAZE); //split string by maze char size
        for (int index = 0; index < file_contents.length(); index += CHARS_IN_MAZE) {
            separated_maze_string_vector.at(vector_index++) = file_contents.substr(index, CHARS_IN_MAZE);
        }
        // make char 2D vector for each maze
        vector <vector<char>> temp_maze_structure;
        int char_count;
        for (string each_maze_string : separated_maze_string_vector) {
            temp_maze_structure.clear();
            char_count = 0;
            temp_maze_structure.resize(SIZE);
            for (int index_x = 0; index_x < SIZE; index_x++) {
                temp_maze_structure.at(index_x).resize(SIZE);
                // update each cell
                for (int index_y = 0; index_y < SIZE; index_y++) {
                    temp_maze_structure.at(index_x).at(index_y) = each_maze_string.at(char_count++);
                }
            }
            generated_maze_vector.push_back(temp_maze_structure);
        }
    } else { // free game mode
        int char_count = 0;
        maze_structure.resize(WIDTH);
        for (int index = 0; index < WIDTH; ++index) {
            maze_structure[index].resize(HEIGHT);
        }
        // update each cell and set start and end positions
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                maze_structure[x][y] = file_contents.at(char_count++);
                if (maze_structure[x][y] == 'S') {
                    start_x = current_posX = x;
                    start_y = current_posY = y;
                } else if (maze_structure[x][y] == 'E') {
                    end_x = x;
                    end_y = y;
                }
            }
        }
    }
    // load game sound effects
    next_maze_sound.load("next_maze.wav");
    win_sound.load("game_win.wav");
    game_over_sound.load("game_over.wav");
}

/**
 * Sets up the maze in timed mode
 */
void Maze::TimeMazeSetup() {
    free_game_mode = false;
    if (generated_maze_vector.empty()) {
        ReadMazeFromFile();
    }
    maze_structure.resize(SIZE);
    for (int index = 0; index < SIZE; index++) {
        maze_structure[index].resize(SIZE);
    }
    
    if (number_games <= generated_maze_vector.size() - 1) {
        next_maze_sound.play();
        SetVisibility(SIZE - DECREASE_VISIBILITY * number_games); // decrease visibility as continue to go through mazes
        maze_structure = generated_maze_vector.at(number_games++);
    } else {
        game_ended = true;
        win_sound.play();
        return;
    }
    
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            if (maze_structure[x][y] == 'S') { // setting starting location
                start_x = current_posX = x;
                start_y = current_posY = y;
            } else if (maze_structure[x][y] == 'E') { // setting end location
                end_x = x;
                end_y = y;
            }
        }
    }
}

/**
 * Sets up the maze in free mode
 *
 * @param current_player - the Character of the current player
 */
void Maze::FreeMazeSetup(Character *current_player) {
    maze_copy_player = current_player;
    free_game_mode = true;
    ReadMazeFromFile();
}

/**
 * Determines which direction to move if possible according to the key pressed
 *
 * @param key - the Unicode value of the key pressed
 */
void Maze::MazeKeyPressed(const char key) {
    if (inBattleMode) {
        return;
    }
    switch (key) {
        case 'w':
            // Move up
            if (maze_structure[current_posX][current_posY - 1] != '#') {
                current_posY--;
            }
            break;
            
        case 's':
            // Move down
            if (maze_structure[current_posX][current_posY + 1] != '#') {
                current_posY++;
            }
            break;
            
        case 'a':
            // Move left
            if (maze_structure[current_posX - 1][current_posY] != '#') {
                current_posX--;
            }
            break;
            
        case 'd':
            // Move right
            if (maze_structure[current_posX + 1][current_posY] != '#') {
                current_posX++;
            }
            break;
    }
    CheckGameStatus();
}

/**
 * Determines which direction to move according to the pixel location of the brightest point
 *
 * @param camera_current_x - the X position of the brightest pixel point
 * @param camera_current_y - the Y position of the brightest pixel point
 */
void Maze::CameraMovePosition(int camera_current_x, int camera_current_y) {
    if ((camera_current_x == 0 || camera_current_y == 0)
        || std::abs(camera_current_x) > MAZE_TRANSLATE
        || std::abs(camera_current_y) > MAZE_TRANSLATE) {
        return;
    }

    //Determine which direction to move from angle of brightest point
    //Splits screen into "triangles"
    double pixel_slope = std::atan(camera_current_y / camera_current_x);
    if (pixel_slope > 0) {
        if (camera_current_x > 0) {
            if (pixel_slope < PI_OVER_FOUR) {
                // Move right
                if (maze_structure[current_posX + 1][current_posY] != '#') {
                    current_posX++;
                    return;
                }
            } else {
                // Move up
                if (maze_structure[current_posX][current_posY - 1] != '#') {
                    current_posY--;
                    return;
                }
            }
        } else {
            if (pixel_slope < PI_OVER_FOUR) {
                // Move left
                if (maze_structure[current_posX - 1][current_posY] != '#') {
                    current_posX--;
                    return;
                }
            } else {
                // Move down
                if (maze_structure[current_posX][current_posY + 1] != '#') {
                    current_posY++;
                    return;
                }
            }
        }
        
    } else {
        if (camera_current_x > 0) {
            if (std::abs(pixel_slope) < PI_OVER_FOUR) {
                // Move right
                if (maze_structure[current_posX + 1][current_posY] != '#') {
                    current_posX++;
                    return;
                }
            } else {
                // Move down
                if (maze_structure[current_posX][current_posY + 1] != '#') {
                    current_posY++;
                    return;
                }
            }
        } else {
            if (std::abs(pixel_slope) < PI_OVER_FOUR) {
                // Move left
                if (maze_structure[current_posX - 1][current_posY] != '#') {
                    current_posX--;
                    return;
                }
            } else {
                // Move up
                if (maze_structure[current_posX][current_posY - 1] != '#') {
                    current_posY--;
                    return;
                }
            }
        }
        
    }
    // check if game ended
    CheckGameStatus();
}

/**
 * Determines whether the game has ended or is in battle mode
 */
void Maze::CheckGameStatus() {
    if (current_posX == end_x && current_posY == end_y) {
        Maze::SetMazeCompleted(true);
        if (free_game_mode) {
            win_sound.play();
        }
    } else if (std::isdigit(maze_structure[current_posX][current_posY]) && free_game_mode) {
        inBattleMode = true;
        next_maze_sound.play();
        return;
    }
}

/**
 * Resets the maze
 */
void Maze::MazeReset() {
    inBattleMode = maze_completed = game_ended = false;
    number_games = 0;
    player_box_image.clear();
    image_loaded = picture_taken = false;
}

/**
 * Takes a picture of the current screen and saves the image for the player box
 */
void Maze::MazeTakePicture() {
    player_box_image.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
    player_box_image.save("player_screenshot.png");
    picture_taken = true;
}
