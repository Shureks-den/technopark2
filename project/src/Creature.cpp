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

void Creature::update_enemy_hp() {
    if (enemy_name == "wolf") {
        set_HP(wolf_hp);
    } else if (enemy_name == "rat") {
        set_HP(rat_hp);
    } else if (enemy_name == "dog") {
        set_HP(dog_hp);
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

void Creature::set_HP(int new_value) {
    HP_ = new_value;
}
