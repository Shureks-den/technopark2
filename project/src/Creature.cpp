#include "Creature.h"
#include "Map.h"

Creature::Creature(size_t type) {
    size_t enemy_type = type;
    switch (enemy_type) {
        case enemy_wolf: {
            enemy_name = "wolf";
            HP_ = wolf_hp;
            weapon_DMG = wolf_dmg;
            break;
        }
        case enemy_dog: {
            enemy_name = "dog";
            HP_ = dog_hp;
            weapon_DMG = dog_dmg;
            break;
        }
        case enemy_rat: {
            enemy_name = "rat";
            HP_ = rat_hp;
            weapon_DMG = rat_dmg;
            break;
        }
        default: break;
    }
}


void Creature::print_info() {
    std::cout << std::endl << enemy_name << " found, " << get_HP() << " hp" << std::endl;
}

int Creature::get_weapon_DMG() const {
    return weapon_DMG;
}

int Creature::get_HP() const {
    return HP_;
}

int Creature::get_base_DMG() const {
    return DMG_base;
}

void Creature::take_dmg(int dmg) {
    HP_ -= dmg;
}
