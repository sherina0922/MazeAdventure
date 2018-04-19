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

struct CharacterType {
    std::string name;
    double health;
    double attack;
    double defense;
    bool isDead = false;
    CharacterType(std::string temp_name, double temp_health, double temp_attack, double temp_defense);
};

static std::vector<CharacterType> character_list;
static std::vector<CharacterType> enemy_list;


class Character {
public:
    
    static void CharacterSetup();
    static std::string GenerateRaceMenuString();
  
};
//*/
