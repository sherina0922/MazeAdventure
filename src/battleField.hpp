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
    
    void SetStopClicked(bool new_status);
    int DetermineMonster(int posX, int posY);
    bool InitiateBattle(Character *player, int monster_number);
    bool DrawBattle(Character *player, Character *monster, bool stop_pressed);
    void BattleKeyPressed(int key);
};

