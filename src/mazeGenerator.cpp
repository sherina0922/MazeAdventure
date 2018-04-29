//
// mazeGenerator.cpp
// final-project-sherina0922
//
// Created by Sherina Hung on 4/22/18.

#include "mazeGenerator.hpp"

//--------------------------------------------------------------
// MAIN
void PopulateNewMaze() {
    //basically main function of maze generator
    Cell new_maze[SIZE][SIZE];
    int posX = 0;
    int posY = 0;
    int endX = 0;
    int endY = 0;
    
    InitializeMaze(new_maze);
    //Redraw(new_maze);
    GenerateMaze(new_maze, posX, posY, endX, endY);
    if (MazeValid(new_maze)) {
        SaveMaze(new_maze);
    } else {
        PopulateNewMaze();
    }
}

//--------------------------------------------------------------
// INITIALIZE MAZE
void InitializeMaze(Cell structure[][SIZE]) {
    for (int index_x = 0; index_x < SIZE; index_x++) {
        for (int index_y = 0; index_y < SIZE; index_y++) {
            structure[index_x][index_y].value = '#';
            structure[index_x][index_y].visited = false;
            structure[index_x][index_y].top_wall = true;
            structure[index_x][index_y].bottom_wall = true;
            structure[index_x][index_y].left_wall = true;
            structure[index_x][index_y].right_wall = true;
        }
    }
    for (int index_x = 1; index_x < SIZE - 1; index_x++) {
        for (int index_y = 1; index_y < SIZE - 1; index_y++) {
            // Border Cells have fewer accessible walls
            structure[1][index_y].top_wall = false;
            structure[SIZE - NEXT_CELL_INDEX][index_y].bottom_wall = false;
            structure[index_x][1].left_wall = false;
            structure[index_x][SIZE - NEXT_CELL_INDEX].right_wall = false;
        }
    }
}

//--------------------------------------------------------------
/*
 // REDRAW MAZE -> std prints out the maze - checking purposes only
 void Redraw(Cell Level[][SIZE]) {
 for(int i = 0; i < SIZE; i++) {
 std::cout << std::endl;
 for(int j = 0; j < SIZE; j++) {
 std::cout << " " << Level[i][j].value;
 }
 }
 }
 */

//--------------------------------------------------------------
// Code below derived from https://www.youtube.com/watch?v=EvAzVhAii_o
void GenerateMaze(Cell structure[][SIZE], int &posX, int &posY, int &endX, int &endY) {
    //Pick randomly the starting cell
    int random = 0;
    int randomX = posX = ((2 * rand()) + 1) % (SIZE - 1);  // Generate a random odd number between 1 and SIZE
    int randomY = posY = ((2 * rand()) + 1) % (SIZE - 1);  // Generate a random odd number between 1 and SIZE
    structure[posY][posX].value = 'S';    // Set S as the start cell
    structure[posY][posX].visited = true;
    
    int visited_cells = 1;
    int total_cells = std::pow(((SIZE - 1) * HALF), 2);
    std::stack<int> back_trackX, back_trackY;   // Stack is used to trace the reverse path
    
    while (visited_cells < total_cells) {
        if ((!structure[randomY - NEXT_CELL_INDEX][randomX].visited &&
             structure[randomY][randomX].top_wall &&
             structure[randomY - NEXT_CELL_INDEX][randomX].bottom_wall) ||
            
            (!structure[randomY + NEXT_CELL_INDEX][randomX].visited &&
             structure[randomY][randomX].bottom_wall &&
             structure[randomY + NEXT_CELL_INDEX][randomX].top_wall) ||
            
            (!structure[randomY][randomX - NEXT_CELL_INDEX].visited &&
             structure[randomY][randomX].left_wall &&
             structure[randomY][randomX - NEXT_CELL_INDEX].right_wall) ||
            
            (!structure[randomY][randomX + NEXT_CELL_INDEX].visited &&
             structure[randomY][randomX].right_wall &&
             structure[randomY][randomX + NEXT_CELL_INDEX].left_wall)) {
                
                random = (rand() % NUMBER_DIRECTIONS) + 1;              // Pick a random wall 1-4 to knock down
                
                // GO UP
                if ((random == UP) && (randomY > 1)) {
                    if (!structure[randomY - NEXT_CELL_INDEX][randomX].visited) {        // If not visited
                        
                        structure[randomY - 1][randomX].value = ' ';        // Delete display
                        structure[randomY - 1][randomX].visited = true;       // Mark cell as visited
                        structure[randomY][randomX].top_wall = false;       // Knock down wall
                        
                        back_trackX.push(randomX);                      // Push X for back track
                        back_trackY.push(randomY);                      // Push Y for back track
                        
                        randomY -= NEXT_CELL_INDEX;                                   // Move to next cell
                        structure[randomY][randomX].visited = true;         // Mark cell moved to as visited
                        structure[randomY][randomX].value = ' ';          // Update path
                        structure[randomY][randomX].bottom_wall = false;       // Knock down wall
                        visited_cells++;                                 // Increase visitedCells counter
                    }
                }
                
                // GO DOWN
                else if ((random == DOWN) && (randomY < SIZE - NEXT_CELL_INDEX)) {
                    if (!structure[randomY + NEXT_CELL_INDEX][randomX].visited) {        // If not visited
                        
                        structure[randomY + 1][randomX].value = ' ';        // Delete display
                        structure[randomY + 1][randomX].visited = true;       // Mark cell as visited
                        structure[randomY][randomX].bottom_wall = false;       // Knock down wall
                        
                        back_trackX.push(randomX);                      // Push X for back track
                        back_trackY.push(randomY);                      // Push Y for back track
                        
                        randomY += NEXT_CELL_INDEX;                                   // Move to next cell
                        structure[randomY][randomX].visited = true;         // Mark cell moved to as visited
                        structure[randomY][randomX].value = ' ';          // Update path
                        structure[randomY][randomX].top_wall = false;       // Knock down wall
                        visited_cells++;                                 // Increase visitedCells counter
                    }
                }
                
                // GO LEFT
                else if ((random == LEFT) && (randomX > 1)) {
                    if (!structure[randomY][randomX - NEXT_CELL_INDEX].visited) {        // If not visited
                        
                        structure[randomY][randomX - 1].value = ' ';        // Delete display
                        structure[randomY][randomX - 1].visited = true;       // Mark cell as visited
                        structure[randomY][randomX].left_wall = false;      // Knock down wall
                        
                        back_trackX.push(randomX);                      // Push X for back track
                        back_trackY.push(randomY);                      // Push Y for back track
                        
                        randomX -= NEXT_CELL_INDEX;                                   // Move to next cell
                        structure[randomY][randomX].visited = true;         // Mark cell moved to as visited
                        structure[randomY][randomX].value = ' ';          // Update path
                        structure[randomY][randomX].right_wall = false;     // Knock down wall
                        visited_cells++;                                 // Increase visitedCells counter
                    }
                }
                
                // GO RIGHT
                else if ((random == RIGHT) && (randomX < SIZE - NEXT_CELL_INDEX)) {
                    if (!structure[randomY][randomX + NEXT_CELL_INDEX].visited) {        // If not visited
                        
                        structure[randomY][randomX + 1].value = ' ';        // Delete display
                        structure[randomY][randomX + 1].visited = true;       // Mark cell as visited
                        structure[randomY][randomX].right_wall = false;     // Knock down wall
                        
                        back_trackX.push(randomX);                      // Push X for back track
                        back_trackY.push(randomY);                      // Push Y for back track
                        
                        randomX += NEXT_CELL_INDEX;                                   // Move to next cell
                        structure[randomY][randomX].visited = true;         // Mark cell moved to as visited
                        structure[randomY][randomX].value = ' ';          // Update path
                        structure[randomY][randomX].left_wall = false;      // Knock down wall
                        visited_cells++;                                 // Increase visitedCells counter
                    }
                }
            } else {
                if (!back_trackX.empty()) {
                    randomX = back_trackX.top();
                    back_trackX.pop();
                }
                
                if (!back_trackY.empty()) {
                    randomY = back_trackY.top();
                    back_trackY.pop();
                }
            }
    }
    endX = randomX;
    endY = randomY;
    structure[endY][endX].value = 'E';
}

//--------------------------------------------------------------
// SAVE MAZE
void SaveMaze(Cell structure[][SIZE]) {
    //note: overwrites anything already in the file, so always read from first line :)
    //note: but also produces circle of death sometimes and nothing runs... generally 2/3 of the time and almost def if
    //move on to the second maze
    std::ofstream output;
    std::string filename = "/Users/sherinahung/Documents/GitHub/final-project-sherina0922/bin/data/test-maze-data.txt";
    char input;
    
    output.open(filename);
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            output << structure[i][j].value;
        }
        output << std::endl;
    }
    output.close();
}

//--------------------------------------------------------------
bool MazeValid(Cell check_maze[][SIZE]) {
    bool isAllEmpty = false;
    bool isAllFull = false;
    for (int index_x = 0; index_x < SIZE; index_x++) {
        for (int index_y = 0; index_y < SIZE; index_y++) {
            if (check_maze[index_x][index_y].value == ' ') {
                isAllFull = false;
            } else if (check_maze[index_x][index_y].value == '#') {
                isAllEmpty = false;
            }
        }
    }
    if (isAllEmpty || isAllFull) {
        return false;
    }
    return true;
}

