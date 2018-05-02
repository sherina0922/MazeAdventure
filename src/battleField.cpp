//
//  battleField.cpp
//  final-project-sherina0922
//
//  Created by Sherina Hung on 4/23/18.
//

#include "battleField.hpp"

/**
 * Draws the battle screen and calls RunBattle to determine the status of the battle
 *
 * @param player - the Character of the player
 * @param monster - the Character of the current monster
 * @return TRUE if battle is over; FALSE otherwise
 */
bool Battle::DrawBattle(Character *player, Character *monster) {
    ofBackground(0, 0, 0);
    ofTrueTypeFont::setGlobalDpi(DEFAULT_DPI);
    font.load("courier_new.ttf", DEFAULT_FONT_SIZE, false);
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    font.drawString("Press space to stop", ofGetWindowWidth() * HALF - BATTLE_OFFSET_X ,
                       BATTLE_OFFSET_Y + ofGetWindowHeight() * std::pow(HALF, 2));
    // draw circles
    ofSetColor(FULL_COLOR, FULL_COLOR * HALF, 0); // set color ORANGE
    ofNoFill();
    ofDrawCircle(ofGetWindowWidth() * HALF, ofGetWindowHeight() * HALF, INITIAL_RADIUS * HALF);
    
    ofSetColor(0, FULL_COLOR, 0); // set color GREEN
    ofNoFill();
    ofDrawCircle(ofGetWindowWidth() * HALF, ofGetWindowHeight() * HALF, INITIAL_RADIUS * HALF * HALF);
    
    ofNoFill();
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR); //set color WHITE
    if (!stop_clicked && radius >= 0) {
        // radius should change as time passes
        radius -= DECREASE_RADIUS;
    }
    ofDrawCircle(ofGetWindowWidth() * HALF, ofGetWindowHeight() * HALF, radius);
    
    // display player and monster stats
    ofSetColor(FULL_COLOR, FULL_COLOR, FULL_COLOR);
    player->DrawCharacterStats();
    ofTranslate(0, TRANSLATE_MONSTER_STATS_Y);
    monster->DrawCharacterStats();
    
    bool result = RunBattle(player, monster, radius);
    if (stop_clicked || (!stop_clicked && radius <= 0)) {
        //reset circles
        radius = INITIAL_RADIUS;
        stop_clicked = false;
    }
    return result; //false if neither is dead, true if one side is dead and battle over
}

/**
 * Runs the battle depending on whether the stop is clicked, where the circle is stopped, and determines
 * the amount of attack dealt to the monster. If player or monster dies, returns TRUE
 *
 * @param player - the Character of the player
 * @param monster - the Character of the current monster
 * @param radius - the current radius of the white circle
 * @return TRUE if battle is over; FALSE otherwise
 */
bool Battle::RunBattle(Character *player, Character *monster, int radius) {
    float damage = 0;
    if (stop_clicked) {
        // determine damage depending on where circle is stopped
        if (radius <= INITIAL_RADIUS * HALF * HALF) {
            // inner green circle
            damage = player->player_stats.attack - monster->player_stats.defense;
        } else if (radius <= INITIAL_RADIUS * HALF) {
            // inner orange circle
            damage = MEDIUM_DAMAGE_PERCENTAGE * (player->player_stats.attack) - monster->player_stats.defense;
        }
        if (damage >= 0) {
            monster->player_stats.health -= damage;
        }
        if (monster->player_stats.health <= 0) {
            // if monster is dead, reset battle and exit here
            monster->player_stats.isDead = true;
            // reset player health after each battle
            monster->player_stats.health = monster->max_health;
            player->player_stats.health = player->max_health;
            return true;
        } else {
            // monster attacks
            damage = (monster->player_stats.attack) - player->player_stats.defense;
            if (damage > 0) {
                player->player_stats.health -= damage;
            }
        }
    } else if (!stop_clicked && radius <= 0) {
        // if player didn't click to stop, monster still gets to attack
        damage = monster->player_stats.attack - player->player_stats.defense;
        if (damage > 0) {
            player->player_stats.health -= damage;
        }
        return false;
    }
    
    // check if player or monster is dead
    if (player->player_stats.health <= 0) {
        player->player_stats.isDead = true;
        game_over_sound.load("game_over.wav");
        game_over_sound.play();
        return true;
    } else if (monster->player_stats.health <= 0) {
        monster->player_stats.isDead = true;
        //reset player health after each battle
        player->player_stats.health = player->max_health;
        return true;
    }
    return false;
}

/**
 * Sets stop_clicked to true if space key is pressed
 *
 * @param key - the unicode value of the key pressed
 */
void Battle::BattleKeyPressed(int key) {
    if (key == ' ') {
        SetStopClicked(true);
    }
}

/**
 * Sets the new status of stop_clicked
 *
 * @param new_status - the new stop_clicked status
 */
void Battle::SetStopClicked(bool new_status) {
    stop_clicked = new_status;
}
