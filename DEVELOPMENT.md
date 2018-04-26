# Development of Final Project

## 4/18/2018

### Problems / In Progress:

- Implementing camera "brightness" tracking with EasyCam
  - Camera tracking has to adjust to changing distances 
- Optimizing camera "brightness" tracking
  - Determines brightest point during each update
  - Kind of jumpy -> not super accurate and slightly laggy
- Creating a menu for player to choose settings
  - Either use ofcButton or somehow use ofDrawBitmapString with keyboard inputs or other method
- Linker errors with using static class variables 
  - Apple Linker errors -> declaring outside of class or extern works but not ideal
- Turning computer camera usage on/off
  - Always on ; need to find way to only turn on when needed
  
### Completed:

- Basic visualization of maze graphics
- EasyCam setup/works

## 4/26/2018

### Problems / In Progress:

- Implementing camera "brightness" tracking with EasyCam
  - Camera tracking has to adjust to changing distances 
  - Change direction input from squares (TopL - down, TopR - up, BottomL - left, BottomR - right) to triangles (more intuitive)
- Optimizing camera "brightness" tracking
  - Determines brightest point during each update
  - Kind of jumpy -> not super accurate and slightly laggy
  - Maybe change frame rate or implement count that only updates player position if stay in certain triangular region for some amount of time
- Weird flashing boxes in the background
  - Not in maze area but definitely appear during timed mode
- Turning computer camera usage on/off
  - Always on ; need to find way to only turn on when needed
- Implement "battle" using player and monster stats
  - Play battle mini-game until one side's health is 0
- Time lag / doesn't load when using random maze generator
  - Rainbow loading circle appears often -> nothing loads
  - Perhaps something wrong with the recursion in maze algorithm
  - Works fine 1/3 of the time
- Reset the perspective / EasyCam when resetting game or using camera input
  - Can reset distance and lock further change of view but can't re-orient the "angle"
  - If completed, make into function so user can reset view at any point in game
- Extra Goals: 
  - Timed Mode 
    - Make screen dark or fuzzy when paused so player can't just pause and stare at screen
    - Let player choose own time limit before starting
  
  
### Completed:

- Basic game flow (other than battle portion) complete
- Camera input technically works
- Different states of game able to be shown
- Resets generally work --> Need to continue to check for bugs
- Reading maze structure data from text files
- Basic random maze generator
- 
