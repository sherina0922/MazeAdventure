//
//  character.cpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/16/18.
//
///*
#include "character.hpp"

//--------------------------------------------------------------
void Character::CharacterSetup() {
    character_list->push_back(CharacterType("Magician", 20, 15, 15)); //50
    character_list->push_back(CharacterType("Archer", 25, 20, 10)); //55
    character_list->push_back(CharacterType("Warrior", 25, 25, 5)); //55
    character_list->push_back(CharacterType("Dwarf", 27, 13, 15)); //55
    
    enemy_list->push_back(CharacterType("Goblin", 20, 10, 10)); //50
    enemy_list->push_back(CharacterType("Thief", 25, 15, 10)); //55
    enemy_list->push_back(CharacterType("Vampire", 20, 13, 10)); //55
    
}

//--------------------------------------------------------------
std::string Character::GenerateRaceMenuString() {
    std::string result = "Please choose from the following character types:\n";
    for (int count = 0; count < character_list->size(); count++) {
        result += std::to_string(count + 1) + ". " + character_list->at(count).name + "\n";
    }
    return result;
}

//--------------------------------------------------------------
void Character::ChooseCharacterType() {
    ofBackground(0, 0, 0);
    ofDrawBitmapString(GenerateRaceMenuString(), ofGetScreenWidth() / 4, ofGetScreenHeight() / 2);
}

//--------------------------------------------------------------
void Character::CharacterKeyPressed(int key) {
    player_stats = character_list->at(key - UNICODE_1);
}

//--------------------------------------------------------------
void Character::DrawCharacterStats() {
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    std:string player_condition_string = "Player stats:\nName: " + player_stats.name + "\nHealth: " + std::to_string(player_stats.health) + "\nAttack: " + std::to_string(player_stats.attack) + "\nDefense: " + std::to_string(player_stats.defense);
    ofDrawBitmapString(player_condition_string, 5, 70);
}
