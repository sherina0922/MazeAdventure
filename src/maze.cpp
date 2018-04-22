//
//  maze.cpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#include "../src/maze.h"
#include <cmath>
//using namespace maze;


void Maze::SetMode(int new_mode) {
    mode = new_mode;
}

void Maze::SetGameEnded(bool new_status) {
    game_ended = new_status;
}

void Maze::DrawMaze() {
    
    if (game_ended) {
        ofBackground(FULL_COLOR,FULL_COLOR,FULL_COLOR);
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("CONGRATULATIONS!\nYOU WIN!", 0, 0);
        return;
    }

    for (int current_y = 0; current_y < HEIGHT; current_y++) {
        for (int current_x = 0; current_x < WIDTH; current_x++) {
            if (maze_structure[current_x][current_y] == '#' &&
                std::abs(current_x - current_posX) < mode &&
                std::abs(current_y - current_posY) < mode) {
                
                ofPushMatrix();
                ofTranslate(current_x * CUBE_SIZE - 100, -current_y * CUBE_SIZE + 50,0);
                ofSetColor(63.0,63.0,63.0); //Set to TRANSPARENT GRAY
                ofFill();
                ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
                ofNoFill();
                ofSetColor(0);
                ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
                ofPopMatrix();
            }
        }
    }
    
    //draw player box
    ofPushMatrix();
    ofTranslate(current_posX * CUBE_SIZE - 100, -current_posY * CUBE_SIZE + 50,0);
    ofSetColor(FULL_COLOR,0.0,0.0); //Set to RED
    ofFill();
    ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
    ofNoFill();
    ofSetColor(0);
    ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
    ofPopMatrix();
    
    //draw goal box
    ofPushMatrix();
    ofTranslate(end_x * CUBE_SIZE - 100, -end_y * CUBE_SIZE + 50,0);
    ofSetColor(0.0,FULL_COLOR,0.0); //Set to GREEN
    ofFill();
    ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
    ofNoFill();
    ofSetColor(0);
    ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
    ofPopMatrix();
}

void Maze::MazeSetup() {
    //Maze setup: Maze below derived from https://www.youtube.com/watch?v=9Ozu-B2HLY4  make as file and read
    //make maze generator??? decrease visibility as player goes through more mazes???

    unsigned char adventure_maze_template[HEIGHT][WIDTH] = {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
        {'#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#','#','#',' ','#',' ','#'},
        {'#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#'},
        {'#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#','#',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#'},
        {'#',' ','#','#','#','#','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#','#','#','#','#',' ','#','#','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#'},
        {'#','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#'},
        {'#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#'},
        {'#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#'},
        {'#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#'},
        {'#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#','#','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#'},
        {'#',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#'},
        {'#',' ','#','#','#',' ','#','#','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#'},
        {'#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#'},
        {'#',' ','#',' ','#','#','#',' ','#',' ','#','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#',' ','#'},
        {'#',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#'},
        {'#',' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#'},
        {'#','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','E','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        
    };
    
    for (int y = 0 ; y < HEIGHT ; y++) {
        for (int x = 0 ; x < WIDTH ; x++) {
            maze_structure[x][y] = adventure_maze_template[y][x];
            if (adventure_maze_template[y][x] == 'S') {
                start_x = x;
                start_y = y;
            } else if (adventure_maze_template[y][x] == 'E') {
                end_x = x;
                end_y = y;
            }
        }
    }
    
    //Hard set current position and exit position
    current_posX = start_x;
    current_posY = start_y;
}

void Maze::MazeKeyPressed(const char key) {
    switch (key) {
        case 'w':
            // Move up
            if (maze_structure[current_posX][current_posY - 1] != '#') {
                current_posY--;
            }
            break;
            
        case 's':
            //Move down
            if (maze_structure[current_posX][current_posY + 1] != '#') {
                current_posY++;
            }
            break;
            
        case 'a':
            //Move left
            if (maze_structure[current_posX - 1][current_posY] != '#') {
                current_posX--;
            }
            break;
            
        case 'd':
            //Move right
            if (maze_structure[current_posX + 1][current_posY] != '#') {
                current_posX++;
            }
            break;
            
        /*case 'e':
            //Set difficulty to EASY
            mode = WIDTH;
            break;
            
        case 'm':
            //Set difficulty to MEDIUM
            mode = 5;
            break;
            
        case 'h':
            //Set difficulty to HARD
            mode = 2;
            break; */
            
    }
    //check if game ended
    if (current_posX == end_x && current_posY == end_y) {
        Maze::SetGameEnded(true);
    }
}

void Maze::CameraMovePosition(int camera_current_x, int camera_current_y) {
    if (camera_current_x == 0 && camera_current_y == 0
        || std::abs(camera_current_x) > 100 || std::abs(camera_current_y) > 100) {
        return;
    }
    /*
    float pixel_slope = std::abs(std::atan(camera_current_y / camera_current_x));
    if (pixel_slope >= 0 && pixel_slope <= 1) {
        if (camera_current_x > 0) {
            if (maze_structure[current_posX + 1][current_posY] != '#') {
                current_posX++;
            }
        } else {
            if (maze_structure[current_posX - 1][current_posY] != '#') {
                current_posX--;
            }
        }
    } else {
        if (camera_current_y > 0) {
            if (maze_structure[current_posX][current_posY + 1] != '#') {
                current_posY++;
            }
        } else {
            if (maze_structure[current_posX][current_posY - 1] != '#') {
                current_posY--;
            }
        }
    }
     */
    if (camera_current_x > 0) {
        if (camera_current_y > 0) {
            //Move up
            if (maze_structure[current_posX][current_posY - 1] != '#') {
                current_posY--;
            }
        } else {
            //Move right
            if (maze_structure[current_posX + 1][current_posY] != '#') {
                current_posX++;
            }
        }
    } else {
        if (camera_current_y > 0) {
            //Move down
            if (maze_structure[current_posX][current_posY + 1] != '#') {
                current_posY++;
            }
        } else {
            //Move left
            if (maze_structure[current_posX - 1][current_posY] != '#') {
                current_posX--;
            }
        }
    }
    //check if game ended
    if (current_posX == end_x && current_posY == end_y) {
        Maze::SetGameEnded(true);
    }
}

