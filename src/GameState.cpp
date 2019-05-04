#include <Arduino.h>
#include <GameState.h>
#include <Utils.h>

GameState::GameState() {
    this->health = 0;
    this->armor = 0;
    this->money = 0;
    this->clip_ammo = 0; 
    this->reserve_ammo = 0;
    this->weapon = WEAPON_NONE;
    this->weapon_type = UNDEFINED;
    // this->weapon_state = HOLSTERED;
    this->player_activity = MENU;
}

int GameState::update(String serialInput) {
    /**
     * HEALTH           -> [0,100]    current health
     * ARMOR            -> [0,100]    current armor
     * MONEY            -> [0,16000]  current money
     * CLIP_AMMO        -> ...
     * RESERVE_AMMO     -> ...
     * WEAPON           -> Weapon (WEAPON_GLOCK, ...)
     * WEAPON_TYPE      -> WeaponType (PISTOL, KNIFE, ...)
     *                                                            WEAPON_STATE     -> WeaponState (HOLSTERED, ACTIVE)
     * PLAYER_ACTIVITY  -> PlayerActivity (MENU, PLAYING...)
     */

    int count = 0;

    for (uint16_t i=0; i<serialInput.length(); i++) {
        if (serialInput.charAt(i) == ';')
            count++;
    }

    if (count != 7) {
        return -2;
    }
    
    String health;
    String armor;
    String money;
    String clip_ammo;
    String reserve_ammo;
    String weapon;
    String weapon_type;
    // String weapon_state;
    String player_activity;

    int last_index = 0;
    int index = serialInput.indexOf(';', last_index);

    health = serialInput.substring(last_index, index);
    last_index = index+1;
    

    index = serialInput.indexOf(';', last_index);
    armor = serialInput.substring(last_index, index);
    last_index = index+1;

    index = serialInput.indexOf(';', last_index);
    money = serialInput.substring(last_index, index);
    last_index = index+1;

    index = serialInput.indexOf(';', last_index);
    clip_ammo = serialInput.substring(last_index, index);
    last_index = index+1;
    
    index = serialInput.indexOf(';', last_index);
    reserve_ammo = serialInput.substring(last_index, index);
    last_index = index+1;
    
    // if (index == -1)
    //    return 2;

    index = serialInput.indexOf(';', last_index);
    weapon = serialInput.substring(last_index, index);
    last_index = index+1;

    index = serialInput.indexOf(';', last_index);
    weapon_type = serialInput.substring(last_index, index);
    last_index = index+1;

    // index = serialInput.indexOf(';', last_index);
    // weapon_state = serialInput.substring(last_index, index);
    // last_index = index+1;

    index = serialInput.indexOf(';', last_index);
    player_activity = serialInput.substring(last_index, index);
    last_index = index+1;
    
    // Serial.println("substrings:");
    // Serial.println(health + ";" + armor + ";" + money + ";" + clip_ammo + ";" + reserve_ammo + ";" + weapon + ";" + weapon_type + ";" + weapon_state + ";" + player_activity);
    // Serial.flush();

    // if (!isNumber(health) ||
    //     !isNumber(armor) ||
    //     !isNumber(money) ||
    //     !isNumber(clip_ammo) ||
    //     !isNumber(reserve_ammo) ||
    //     !isNumber(weapon) ||
    //     !isNumber(weapon_type) ||
    //     !isNumber(weapon_state) ||
    //     !isNumber(player_activity))
    //     return 1;



    this->health = health.toInt();
    this->armor = armor.toInt();
    this->money = money.toInt();
    this->clip_ammo = clip_ammo.toInt();
    this->reserve_ammo = reserve_ammo.toInt();
    this->weapon = weapon.toInt();
    this->weapon_type = weapon_type.toInt();
    // this->weapon_state = weapon_state.toInt();
    this->player_activity = player_activity.toInt();

    return 0;
}
