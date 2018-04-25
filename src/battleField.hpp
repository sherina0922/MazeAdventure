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

static ofSoundPlayer sound1;
const float initial_radius = 100;

class Battle {
public:
    bool stop_clicked = false;
    void SetStopClicked(bool stuff) {
        stop_clicked = stuff;
    };
    float radius = initial_radius;
    
    int DetermineMonster(int posX, int posY);
    bool InitiateBattle(Character *player, int posX, int posY);
    bool DrawBattle(Character *player, Character *monster, bool stop_pressed);
    
    void BattleKeyPressed(int key);
};

