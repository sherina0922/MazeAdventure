# Project Proposal

## Idea 1

### Basic Summary

I wanted to create a adventure like game in which the player tries to get to the end of a maze with limited visibility and has to deal with monsters along the way. The player, before starting the game, should be able to choose a difficulty which may not necessarily change the maze formation but will limit how many spaces around the player's current position is visible. The idea is that the harder the difficulty, the less visibility. Also, the player should be able to somewhat customize their stats as fighting monsters is part of the game. Ideally, the player (when fighting the monster) should be able to make decisions like attack and defend but may be reduced to automatic battling if limitations exist. The current stats of the player would most likely be plainly visible on the side of the screen and be automatically updated as the game continues. The player would move using WASD keys. 

I might attempt to visualize the maze with 3D boxes so the user can drag the screen to view the maze from different angles/perspectives and add a feature that allows the user to move using camera tracking of the brightest object. 

### Possible Libraries

I'm not quite sure exactly which libraries I will end up using but for now...
- ofBitmapFont -> to print out messages
- ofEasyCam -> to allow for different viewing angles of the maze/game -> can reference the ofEasyCam project from OF Examples
- of3dPrimitives (ofBoxPrimitive) -> to make maze/player boxes -> can reference the of3dPrimitives project from OF Examples
- ofxOpenCV

### Outside Resources

- [OpenFrameworks Youtube tutorials](https://www.youtube.com/playlist?list=PL4neAtv21WOmrV8z9rSzL20QpdLU1zJLr) 
- [Game Idea Source](https://www.youtube.com/watch?v=9Ozu-B2HLY4)
- Snake Game for basic game flow, controls

## Idea 2

### Basic Summary

I wanted to create an application like "Paint" in which the user can draw things with different colors and save their work. To make it more interesting, I want to add a "Camera mode" in which the user uses a bright object as the stylus and the camera tracks that bright object to draw things. Regular drawing with the mouse should still work as usual.
/
### Possible Libraries and References

- ofxOpenCv -> use to access computer camera
- ofPoint


### Outside Resources

- [OpenFrameworks Youtube tutorials](https://www.youtube.com/playlist?list=PL4neAtv21WOmrV8z9rSzL20QpdLU1zJLr) 

