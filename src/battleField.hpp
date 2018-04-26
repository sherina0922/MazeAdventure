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

static ofSoundPlayer sound1;

class Battle {
public:
    bool stop_clicked = false;
    void SetStopClicked(bool stuff) {
        stop_clicked = stuff;
    };
    float radius = INITIAL_RADIUS;
    
    int DetermineMonster(int posX, int posY);
    bool InitiateBattle(Character *player, int posX, int posY);
    bool DrawBattle(Character *player, Character *monster, bool stop_pressed);
    
    void BattleKeyPressed(int key);
};

