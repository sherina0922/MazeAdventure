//
//  mazeGenerator.cpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/22/18.
//

#include "mazeGenerator.hpp"
#include <iostream>
#include <ctime>
#include <stack>
#include <fstream>
//#include "stdafx.h" //http://sourceforge.net/p/wpbdc/website/ci/master/tree/Judge/StdAfx.h

// MAIN
void GenerateNewMaze() {
    Cell new_maze[SIZE][SIZE];
    int posX = 0;
    int posY = 0;
    int goalX = 0;
    int goalY = 0;
    
    Initialize(new_maze);
    //Redraw(new_maze);
    GenerateMaze(new_maze, posX, posY, goalX, goalY);
    if (MazeValid(new_maze)) {
        SaveMaze(new_maze);
    }
}

// INITIALIZE MAZE
void Initialize(Cell Level[][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            Level[i][j].value = '#';
            Level[i][j].visited = false;
            Level[i][j].top_wall = true;
            Level[i][j].bot_wall = true;
            Level[i][j].left_wall = true;
            Level[i][j].right_wall = true;
        }
    }
    for(int i = 1; i < SIZE - 1; i++) {
        for(int j = 1; j < SIZE - 1; j++) {
            // Border Cells have fewer accessible walls
            Level[1][j].top_wall = false;
            Level[SIZE - 2][j].bot_wall = false;
            Level[i][1].left_wall = false;
            Level[i][SIZE - 2].right_wall = false;
        }
    }
}

/*// CLEAR SCREEN
 void ClearScreen()
 {
 HANDLE hOut;
 COORD Position;
 hOut = GetStdHandle(STD_OUTPUT_HANDLE);
 Position.X = 0;
 Position.Y = 0;
 SetConsoleCursorPosition(hOut, Position);
 }*/

/*
// REDRAW MAZE
void Redraw(Cell Level[][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        std::cout << std::endl;
        for(int j = 0; j < SIZE; j++)
            std::cout << " " << Level[i][j].value;
    }
}
*/

// GENERATE MAZE
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY) {
    srand((unsigned)time(NULL));    // Pick random start cell
    int random = 0;
    int randomX = ((2 * rand()) + 1) % (SIZE - 1);  // Generate a random odd number between 1 and SIZE
    int randomY = ((2 * rand()) + 1) % (SIZE - 1);  // Generate a random odd number between 1 and SIZE
    posX = randomX; // Save player's initial X position
    posY = randomY; // Save player's initial Y position
    int visitedCells = 1;
    int totalCells = ((SIZE - 1) / 2) * ((SIZE - 1) / 2);
    int percent = 0;
    std::stack<int> back_trackX, back_trackY;   // Stack is used to trace the reverse path
    
    Level[randomY][randomX].value = 'S';    // Set S as the start cell
    Level[randomY][randomX].visited = true; // Set start cell as visited;
    
    while(visitedCells < totalCells)
    {
        if(((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true && Level[randomY - 2][randomX].bot_wall == true)) ||
           ((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true && Level[randomY + 2][randomX].top_wall == true)) ||
           ((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true && Level[randomY][randomX - 2].right_wall == true)) ||
           ((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true && Level[randomY][randomX + 2].left_wall == true)))
        {
            random = (rand() % 4) + 1;              // Pick a random wall 1-4 to knock down
            
            // GO UP
            if((random == 1) && (randomY > 1)) {
                if(Level[randomY - 2][randomX].visited == false) {        // If not visited
                    Level[randomY - 1][randomX].value = ' ';        // Delete display
                    Level[randomY - 1][randomX].visited = true;       // Mark cell as visited
                    Level[randomY][randomX].top_wall = false;       // Knock down wall
                    
                    back_trackX.push(randomX);                      // Push X for back track
                    back_trackY.push(randomY);                      // Push Y for back track
                    
                    randomY -= 2;                                   // Move to next cell
                    Level[randomY][randomX].visited = true;         // Mark cell moved to as visited
                    Level[randomY][randomX].value = ' ';          // Update path
                    Level[randomY][randomX].bot_wall = false;       // Knock down wall
                    visitedCells++;                                 // Increase visitedCells counter
                }
                else
                    continue;
            }
            
            // GO DOWN
            else if((random == 2) && (randomY < SIZE - 2)) {
                if(Level[randomY + 2][randomX].visited == false) {        // If not visited
                    Level[randomY + 1][randomX].value = ' ';        // Delete display
                    Level[randomY + 1][randomX].visited = true;       // Mark cell as visited
                    Level[randomY][randomX].bot_wall = false;       // Knock down wall
                    
                    back_trackX.push(randomX);                      // Push X for back track
                    back_trackY.push(randomY);                      // Push Y for back track
                    
                    randomY += 2;                                   // Move to next cell
                    Level[randomY][randomX].visited = true;         // Mark cell moved to as visited
                    Level[randomY][randomX].value = ' ';          // Update path
                    Level[randomY][randomX].top_wall = false;       // Knock down wall
                    visitedCells++;                                 // Increase visitedCells counter
                }
                else
                    continue;
            }
            
            // GO LEFT
            else if((random == 3) && (randomX > 1)) {
                if(Level[randomY][randomX - 2].visited == false) {        // If not visited
                    Level[randomY][randomX - 1].value = ' ';        // Delete display
                    Level[randomY][randomX - 1].visited = true;       // Mark cell as visited
                    Level[randomY][randomX].left_wall = false;      // Knock down wall
                    
                    back_trackX.push(randomX);                      // Push X for back track
                    back_trackY.push(randomY);                      // Push Y for back track
                    
                    randomX -= 2;                                   // Move to next cell
                    Level[randomY][randomX].visited = true;         // Mark cell moved to as visited
                    Level[randomY][randomX].value = ' ';          // Update path
                    Level[randomY][randomX].right_wall = false;     // Knock down wall
                    visitedCells++;                                 // Increase visitedCells counter
                }
                else
                    continue;
            }
            
            // GO RIGHT
            else if((random == 4) && (randomX < SIZE - 2)) {
                if(Level[randomY][randomX + 2].visited == false) {        // If not visited
                    Level[randomY][randomX + 1].value = ' ';        // Delete display
                    Level[randomY][randomX + 1].visited = true;       // Mark cell as visited
                    Level[randomY][randomX].right_wall = false;     // Knock down wall
                    
                    back_trackX.push(randomX);                      // Push X for back track
                    back_trackY.push(randomY);                      // Push Y for back track
                    
                    randomX += 2;                                   // Move to next cell
                    Level[randomY][randomX].visited = true;         // Mark cell moved to as visited
                    Level[randomY][randomX].value = ' ';          // Update path
                    Level[randomY][randomX].left_wall = false;      // Knock down wall
                    visitedCells++;                                 // Increase visitedCells counter
                }
                else
                    continue;
            }
        }
        else {
            randomX = back_trackX.top();
            back_trackX.pop();
            
            randomY = back_trackY.top();
            back_trackY.pop();
        }
        
        //ClearScreen();
        Redraw(Level);
    }
    
    goalX = randomX;
    goalY = randomY;
    Level[goalY][goalX].value = 'E';
    Redraw(Level);
}

// SAVE MAZE
void SaveMaze(Cell Level[][SIZE]) {
    std::ofstream output;
    std::string filename = "maze_data";
    char input;
    
    output.open(filename);
        
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            output << Level[i][j].value;
        }
        output << std::endl;
    }
    output.close();
}

bool MazeValid(Cell check_maze[][SIZE]) {
    bool isAllEmpty = false;
    bool isAllFull = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (check_maze[i][j].value == ' ') {
                isAllFull = false;
            } else if (check_maze[i][j].value == '#') {
                isAllEmpty = false;
            }
        }
    }
    if (isAllEmpty || isAllFull) {
        return false;
    }
    return true;
    
    
    
    
    
    
    
}
