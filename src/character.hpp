//
//  character.hpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/16/18.
//
///*
#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include "ofMain.h"

#include "constants.cpp"

class Character {
    
public:
    struct CharacterType {
        std::string name;
        int health;
        int attack;
        int defense;
        bool isDead = false;
        CharacterType() {
            name = "";
            health = 0;
            attack = 0;
            defense = 0;
            isDead = false;
        };
        CharacterType(std::string temp_name, double temp_health, double temp_attack, double temp_defense) {
            name = temp_name;
            health = temp_health;
            attack = temp_attack;
            defense = temp_defense;
            isDead = false;
        };
    };
    
    Character() {
        player_stats = CharacterType();
        character_list = new std::vector<CharacterType>;
        enemy_list = new std::vector<CharacterType>;
    };
    CharacterType player_stats;
    
    std::vector<CharacterType> *character_list;
    std::vector<CharacterType> *enemy_list;
    
    void CharacterSetup();
    std::string GenerateRaceMenuString();
    void ChooseCharacterType();
    void CharacterKeyPressed(int key);
    void DrawCharacterStats();
    
};
//*/
