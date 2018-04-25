//
//  maze.cpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/15/18.
//

#include "../src/maze.hpp"
#include <cmath>
//using namespace maze;

//--------------------------------------------------------------
void Maze::SetMode(int new_mode) {
    mode = new_mode;
}

//--------------------------------------------------------------
void Maze::SetGameEnded(bool new_status) {
    game_ended = new_status;
}

//--------------------------------------------------------------
void Maze::SetInBattleMode(bool isTrue) {
    inBattleMode = isTrue;
}

//--------------------------------------------------------------
void Maze::DrawMaze() {
    
    if (game_ended) {
        if (free_game_mode) {
            if (maze_copy_player->player_stats.health > 0) {
                ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
                ofSetColor(0, 0, 0);
                ofDrawBitmapString("CONGRATULATIONS!\nYOU WIN!", 0, 0);
                return;
            }
        } else {
            Maze::TimeMazeSetup();
            game_ended = false;
            //number_games++;
            //Maze::SetMode(maze_structure.size() - 5 * number_games);
        }
    } else {
        
        for (int current_y = 0; current_y < HEIGHT; current_y++) {
            for (int current_x = 0; current_x < WIDTH; current_x++) {
                
                if (std::abs(current_x - current_posX) < mode &&
                    std::abs(current_y - current_posY) < mode) {
                    
                    ofPushMatrix();
                    ofTranslate(current_x * CUBE_SIZE - 100, -current_y * CUBE_SIZE + 50, 0);
                    
                    if (maze_structure[current_x][current_y] == '#') {
                        ofSetColor(GRAY, GRAY, GRAY); //Set to TRANSPARENT GRAY for maze walls
                    
                    } else if (maze_structure[current_x][current_y] == 'M') {
                        ofSetColor(0, 0, FULL_COLOR); //Set to BLUE for monsters
                    }
                    
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
        ofTranslate(current_posX * CUBE_SIZE - 100, -current_posY * CUBE_SIZE + 50, 0);
        ofSetColor(FULL_COLOR, 0.0, 0.0); //Set to RED
        ofFill();
        ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
        ofNoFill();
        ofSetColor(0);
        ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
        ofPopMatrix();
        
        //draw goal box
        ofPushMatrix();
        ofTranslate(end_x * CUBE_SIZE - 100, -end_y * CUBE_SIZE + 50, 0);
        ofSetColor(0.0, FULL_COLOR, 0.0); //Set to GREEN
        ofFill();
        ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
        ofNoFill();
        ofSetColor(0);
        ofDrawBox(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE);
        ofPopMatrix();
        
    }
}

//--------------------------------------------------------------
void Maze::TimeMazeSetup() {
    free_game_mode = false;
    //  WRITE METHOD TO READ IN TEXT FILE AND TURN INTO CHAR ARRAY VECTOR
    /*
     PopulateNewMaze();
     maze_structure.resize(21);
     for (int index = 0; index < 41; ++index) {
     maze_structure[index].resize(21);
     }
     
     std::string line;
     char each_char;
     std::ifstream file;
     std::string file_contents;
     
     file.open("maze_data.txt");
     if (file.is_open()) {
     while (file >> std::noskipws >> each_char) {
     file_contents += each_char;
     }
     file.close();
     }
     file.close();
     file_contents.erase(std::remove(file_contents.begin(), file_contents.end(), '\n'), file_contents.end());
     
     int count = 0; //442 * number_games;
     
     start_x = 0;
     start_y = 0;
     for (int height = 0; height < maze_structure.size(); height++) {
     for (int width = 0; width < maze_structure[0].size(); width++) {
     maze_structure[height][width] = file_contents.at(count); //converts string to char
     count++;
     }
     }
     
     for (int x = 0 ; x < maze_structure.size() ; x++) {
     for (int y = 0 ; y < maze_structure[0].size() ; y++) {
     if (maze_structure[x][y] == 'S') {
     start_x = x;
     start_y = y;
     } else if (maze_structure[x][y] == 'E') {
     end_x = x;
     end_y = y;
     }
     }
     }
     */
    //FreeMazeSetup();
    unsigned char adventure_maze_template[HEIGHT][WIDTH] = { //delete all this later when maze generator works
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', 'M', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', 'M', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', 'M', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        
    };
    
    maze_structure.resize(WIDTH);
    for (int index = 0; index < WIDTH; ++index) {
        maze_structure[index].resize(HEIGHT);
    }
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze_structure[x][y] = adventure_maze_template[y][x];
            if (adventure_maze_template[y][x] == 'S') {
                start_x = current_posX = x;
                start_y = current_posY = y;
            } else if (adventure_maze_template[y][x] == 'E') {
                end_x = x;
                end_y = y;
            }
        }
    }
    free_game_mode = false;
}

//--------------------------------------------------------------
void Maze::FreeMazeSetup(Character *current_player) {
    maze_copy_player = current_player;
    
    sound.load("laser_sound.mp3"); //for testing purposes only
    free_game_mode = true;
    //Maze setup: Maze below derived from https://www.youtube.com/watch?v=9Ozu-B2HLY4  make as file and read
    //make maze generator??? decrease visibility as player goes through more mazes???
    
    unsigned char adventure_maze_template[HEIGHT][WIDTH] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', 'M', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', 'M', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', 'M', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        
    };
    
    //15,15
    //29,13
    
    maze_structure.resize(WIDTH);
    for (int index = 0; index < WIDTH; ++index) {
        maze_structure[index].resize(HEIGHT);
    }
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze_structure[x][y] = adventure_maze_template[y][x];
            if (adventure_maze_template[y][x] == 'S') {
                start_x = current_posX = x;
                start_y = current_posY = y;
            } else if (adventure_maze_template[y][x] == 'E') {
                end_x = x;
                end_y = y;
            }
        }
    }
}

//--------------------------------------------------------------
void Maze::MazeKeyPressed(const char key) {
    //if (inBattleMode) {
    //    return;
    //}
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
    CheckGameStatus(current_posX, current_posY);
}

//--------------------------------------------------------------
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
    CheckGameStatus(current_posX, current_posY);
    
}

//--------------------------------------------------------------
void Maze::CheckGameStatus(int posX, int posY) {
    if (current_posX == end_x && current_posY == end_y) {
        Maze::SetGameEnded(true);
    } else if (maze_structure[current_posX][current_posY] == 'M' && free_game_mode) {
        //sound.play();
        //SetInBattleMode(true);
        //Maze::SetGameEnded(!Battle::InitiateBattle(maze_copy_player, current_posX, current_posY));
        inBattleMode = true;
        return;
    }
}
