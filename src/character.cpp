//
//  character.cpp
//  final-project-sherina0922-master
//
//  Created by Sherina Hung on 4/16/18.
//

#include "character.hpp"

/**
 * Populates the character and monster lists
 */
void Character::CharacterSetup() {
    character_list->push_back(CharacterType("Magician", 23, 18, 10));
    character_list->push_back(CharacterType("Archer", 25, 20, 10));
    character_list->push_back(CharacterType("Warrior", 25, 23, 5));
    character_list->push_back(CharacterType("Dwarf", 27, 13, 13));
    
    monster_list->push_back(CharacterType("Goblin", 20, 12, 10));
    monster_list->push_back(CharacterType("Thief", 25, 15, 10));
    monster_list->push_back(CharacterType("Vampire", 20, 13, 10));
    monster_list->push_back(CharacterType("Pirate", 25, 16, 11));
    monster_list->push_back(CharacterType("Ghost", 24, 17, 10));
    
    ofTrueTypeFont::setGlobalDpi(DEFAULT_DPI);
    font.load("courier_new.ttf", DEFAULT_FONT_SIZE, false);
}

/**
 * Generates the message string for choosing a character type
 *
 * @return the character type choices as a string
 */
std::string Character::GenerateRaceMenuString() {
    std::string result = "Please choose from the following character types:\n";
    for (int count = 0; count < character_list->size(); count++) {
        result += std::to_string(count + 1) + ". " + character_list->at(count).name + "\n";
    }
    return result;
}

/**
 * Draws the screen for choosing a character type
 */
void Character::ChooseCharacterType() {
    ofBackground(0, 0, 0);
    font.drawString(GenerateRaceMenuString(), ofGetWidth() * HALF - CHOOSE_CHARACTER_OFFSET_X , ofGetScreenHeight() * HALF - CHOOSE_CHARACTER_OFFSET_Y);
}

/**
 * Sets the player's character stats to the according character type
 *
 * @param key - the Unicode value of the key pressed
 */
void Character::CharacterKeyPressed(int key) {
    player_stats = character_list->at(key - UNICODE_1);
    max_health = player_stats.health;
}

/**
 * Sets the player's character stats to the according monster character type
 * to the key pressed
 *
 * @param key - the Unicode value of the key pressed
 */
void Character::DetermineMonster(int key) {
    player_stats = monster_list->at(key - UNICODE_1);
}

/**
 * Draws the character stats on the side of the screen
 */
void Character::DrawCharacterStats() {
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    std: string player_condition_string = "Player stats:\nName: " + player_stats.name + "\nHealth: " + std::to_string(player_stats.health) +
                                        "\nAttack: " + std::to_string(player_stats.attack) + "\nDefense: " + std::to_string(player_stats.defense);
    ofDrawBitmapString(player_condition_string, OFFSET_X, CHARACTER_INFO_Y);
}

