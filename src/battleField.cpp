//
//  battleField.cpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/23/18.
//

#include "battleField.hpp"

//--------------------------------------------------------------
//currently not used due to changes in maze input file format
int Battle::DetermineMonster(int posX, int posY) {
    //either hard code like below or randomize or label each monster something diff when parsing in
    if (posX == 3 && posY == 5) {
        return 0;
    } else if (posX == 15 && posY == 15) {
        return 1;
    } else if (posX == 29 && posY == 13) {
        return 2;
    }
    return -1;
}

//--------------------------------------------------------------
bool Battle::InitiateBattle(Character *player, int monster_number) {
    //return true if player win, false if player dead
    Character current_monster;
    current_monster.player_stats = player->enemy_list->at(monster_number);
    
    while (player->player_stats.health > 0 && current_monster.player_stats.health > 0) {
        //RunBattle(player, current_monster);
        current_monster.player_stats.health -= player->player_stats.attack - current_monster.player_stats.defense;
        player->player_stats.health -= current_monster.player_stats.attack - player->player_stats.defense;
    }
   
    //ofSetBackgroundColor(0, 0, 0);
    if (player->player_stats.health > 0) {
        //player won
        return true;
    } else {
        //monster won
        ofBackground(FULL_COLOR, FULL_COLOR, FULL_COLOR);
        ofDrawBitmapString("YOU DIED!", ofGetWindowWidth() * HALF, ofGetWindowHeight() * HALF);
        return false;
    }
}

//--------------------------------------------------------------
bool Battle::DrawBattle(Character *player, Character *monster, bool stop_pressed) {
    ofBackground(0, 0, 0);
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    player->DrawCharacterStats();
    
    ofDrawBitmapString("Press space to stop", ofGetWindowWidth() * HALF, ofGetWindowHeight() * std::pow(HALF, 2));
    
    ofSetColor(FULL_COLOR, FULL_COLOR * HALF, 0); //Set to ORANGE
    ofDrawCircle(ofGetWindowWidth() * HALF, ofGetWindowHeight() * HALF, INITIAL_RADIUS * HALF);
    
    ofSetColor(0, FULL_COLOR, 0); //Set to GREEN
    ofDrawCircle(ofGetWindowWidth() * HALF, ofGetWindowHeight() * HALF, 20);
    
    ofNoFill();
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //Set to GREEN
    if (!stop_pressed && radius >= 0) {
        radius -= 1.5;
    }
    ofDrawCircle(ofGetWindowWidth() * HALF, ofGetWindowHeight() * HALF, radius); //radius should change as time passes
    
    ofTranslate(OFFSET_X, 100);
    monster->DrawCharacterStats();
    float damage = 0;
    if (stop_pressed) {
        //determine damage depending on where circle is stopped
        if (radius <= 20) {
            damage = 2 * player->player_stats.attack - monster->player_stats.defense;
        } else if (radius <= INITIAL_RADIUS * HALF) {
            damage = 0.95 * (player->player_stats.attack) - monster->player_stats.defense;
        } else {
            damage = 0.75 * (player->player_stats.attack) - monster->player_stats.defense;
        }
        if (damage > 0) {
            monster->player_stats.health -= damage;
            if (monster->player_stats.health <= 0) {
                //if monster is dead
                monster->player_stats.isDead = true;
                return true;
            } else {
                //if monster not dead, monster's turn to attack
                damage = (monster->player_stats.attack) - player->player_stats.defense;
                if (damage <= 0) {
                    damage = 0;
                }
                player->player_stats.health -= damage;
            }
        }
        
        if (player->player_stats.health <= 0) {
            player->player_stats.isDead = true;
            return true;
        } else if (monster->player_stats.health <= 0) {
            monster->player_stats.isDead = true;
            
            return true;
        } else {
            radius = INITIAL_RADIUS;
            stop_clicked = false;
            return false;
        }
    } else if (!stop_pressed && radius < 0) {
         //damage = 0.25 * (player.player_stats.attack) - monster.player_stats.defense;
        radius = INITIAL_RADIUS;
        stop_pressed = false;
        return false;
    }
    //monster.player_stats.health -= damage;
    return false;
}

//--------------------------------------------------------------
void Battle::BattleKeyPressed(int key) {
    if (key == ' ') {
        SetStopClicked(true);
    }
}

//--------------------------------------------------------------
void Battle::SetStopClicked(bool new_status) {
    stop_clicked = new_status;
}
