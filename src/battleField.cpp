//
//  battleField.cpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/23/18.
//

#include "battleField.hpp"

//--------------------------------------------------------------
int Battle::DetermineMonster(int posX, int posY) {
    //either hard code like below or randomize or label each monster something diff when parsing in
    sound1.load("laser_sound.mp3"); //for testing purposes only
    sound1.play();
    
    if (posX == 3 && posY == 5) {
        sound1.play();
        return 0;
    } else if (posX == 15 && posY == 15) {
        sound1.play();
        return 1;
    } else if (posX == 29 && posY == 13) {
        sound1.play();
        return 2;
    }
    
    return -1;

}
//--------------------------------------------------------------
bool Battle::InitiateBattle(Character *player, int posX, int posY) {
    //return true if player win, false if player dead
    Character current_monster;
    current_monster.player_stats = player->enemy_list->at(DetermineMonster(posX, posY));
    
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
        ofDrawBitmapString("YOU DIED!", ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
        return false;
    }
    
    
}
//--------------------------------------------------------------
bool Battle::DrawBattle(Character *player, Character *monster, bool stop_pressed) {
    ofBackground(0, 0, 0);
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    ofDrawBitmapString("Press space to stop", ofGetWindowWidth() / 2, ofGetWindowHeight() / 4);
    
    ofSetColor(FULL_COLOR,165,0); //Set to ORANGE
    ofDrawCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, initial_radius / 2);
    
    ofSetColor(0, FULL_COLOR, 0); //Set to GREEN
    ofDrawCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 20);
    
    ofNoFill();
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //Set to GREEN
    if (!stop_pressed && radius >= 0) {
        radius -= 1.0;
    }
    ofDrawCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, radius); //radius should change as time passes
    
    //float damage = 0;
    if (stop_pressed) {
        if (radius <= 20) {
            radius = initial_radius;
            stop_clicked = false;
            //damage = player.player_stats.attack - monster.player_stats.defense;
            return true;
        } else if (radius <= initial_radius / 2) {
            //damage = 0.75 * (player.player_stats.attack) - monster.player_stats.defense;
            radius = initial_radius;
            stop_clicked = false;
            return false;
        } else {
            //damage = 0.50 * (player.player_stats.attack) - monster.player_stats.defense;
            radius = initial_radius;
            stop_clicked = false;
            return false;
        }
    } else if (!stop_pressed && radius < 0) {
         //damage = 0.25 * (player.player_stats.attack) - monster.player_stats.defense;
        radius = initial_radius;
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
















