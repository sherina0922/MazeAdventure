//
//  battleField.hpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/23/18.
//

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "character.hpp"
#include "constants.cpp"

class Battle {
public:
    bool stop_clicked = false;
    float radius = INITIAL_RADIUS;
    
    void SetStopClicked(bool new_status);                               //Sets stop_clicked to the new status
    bool DrawBattle(Character *player, Character *monster);             //Draws the battle (circles and character stats)
    void BattleKeyPressed(int key);                                     //Sets stop_clicked to true if space key pressed
    bool RunBattle(Character *player, Character *monster, int radius);  //Determines the outcome of the battle
};

