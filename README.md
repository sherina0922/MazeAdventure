# CS 126 FinalProject

## Project Summary
The game itself runs similar to a typical maze game in which the player tries to reach the exit. This game has two modes: Free mode and Timed mode. In the free mode, the player can choose a character type (Warrior, Magician, etc.),  can choose the visibility settings, and plays a circle-target mini-game when encountering a monster. In the timed mode, the player tries to go through as many mazes as possible within the time limit. The visibility of the maze decreases as the player clears more mazes.

In both modes, the player moves using WASD keys, can reset the entire game ('r'), and can choose to use camera input for movement ('c'). The camera movement uses the computer's camera and tracks the location of the brightest pixel (using a phone's flashlight usually works). The input is registered according to where the brightest pixel is (upper triangle - UP, lower triangle - DOWN, left triangle - LEFT, right triangle - RIGHT). The player can drag the screen to view the maze from different angles and scroll in/out to zoom in/out. The orientation can be reset by left-clicking twice. In free mode, the space bar is used in the mini-game to stop the circle which determines the attack power. In timed mode, the player can pause the game ('p').

## Build Information
While in development, the game was built in XCode and requires the standard OF libraries as well as the ofxGui library. 

## Sources
Game sound effects - http://www.mariomayhem.com/downloads/sounds/
Game idea source and free mode maze source - https://www.youtube.com/watch?v=9Ozu-B2HLY4

