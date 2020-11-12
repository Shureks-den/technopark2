#include "Player.h"
void Player::kick_enemy(Creature &enemy, size_t &enemy_type, bool &enemy_live, Map &map) {
    enemy.set_HP(enemy.get_HP() - DMG);

    if (enemy.get_HP() <= 0) {
        std::cout << std::endl << "enemy killed" << std::endl;
        enemy_live = false;
        enemy.update_enemy_hp();
        map.enemy_dead();
        enemy_type = 0;
        return;
    }
    if ((enemy.get_weapon_DMG() + enemy.get_base_DMG()) <= ARM) {
        HP--;
    } else {
        HP -= ((enemy.get_base_DMG() + enemy.get_weapon_DMG()) - ARM);
    }

    if (HP > 0) {
        std::cout << std::endl << "enemy kicked. Enemy hp: " << enemy.get_HP() << std::endl;
    }
}

void Player::pick_clothes(const std::string &command, std::map<std::string, Armor> &clothes, size_t &obj) {
    for (auto& [name, ch] : clothes) {
        if (ch.get_found() && command.find(name) > 0 && !ch.get_equipped() && (WGT + ch.get_WGT() <= 20)) {
            std::cout << std::endl << "clothes worn" << std::endl;

            ch.set_equipped(true);
            ch.set_found(false);

            WGT += ch.get_WGT();
            ARM += ch.get_ARM();

            obj = 0;
            return;
        }
    }
}

void Player::throw_clothes(const std::string &command, std::map<std::string, Armor> &clothes) {
    for (auto& [name, ch] : clothes) {
        if (ch.get_equipped() && command.find(name) != std::string::npos) {
            std::cout << std::endl << "the " << name << " is thrown out" << std::endl;

            ch.set_equipped(false);

            WGT -= ch.get_WGT();
            ARM -= ch.get_ARM();

            return;
        }
    }
}
void Player::move(movement &move, const std::string &command, size_t &obj, Creature &enemy,
                  Map &map, std::map<std::string, Armor>& clothes) {
    if (command == "move left" && move.left) {
        map.set_x(map.get_x() - 1);
        print_moved(obj, map);
    }
    if (command == "move right" && move.right) {
        map.set_x(map.get_x() + 1);
        print_moved(obj, map);
    }
    if (command == "move down" && move.down) {
        map.set_y(map.get_y() - 1);
        print_moved(obj, map);
    }
    if (command == "move up" && move.up) {
        map.set_y(map.get_y() + 1);
        print_moved(obj, map);
    }

    Creature wolf(enemy_wolf);
    Creature dog(enemy_dog);
    Creature rat(enemy_rat);

    switch (obj) {
        case enemy_wolf:
            enemy = wolf;
            enemy.print_info();
            return;

        case enemy_dog:
            enemy = dog;
            enemy.print_info();
            return;

        case enemy_rat:
            enemy = rat;
            enemy.print_info();
            return;
        case found_pants:
            std::cout << std::endl << "pants found" << std::endl;
            clothes["pants"].set_found(true);
            return;
        case found_helmet:
            std::cout << std::endl << "helmet found" << std::endl;
            clothes["helmet"].set_found(true);
            return;
        case found_T_Shirt:
            std::cout << std::endl << "T-Shirt found" << std::endl;
            clothes["T-Shirt"].set_found(true);
            return;
        case found_shield:
            std::cout << std::endl << "shield found" << std::endl;
            clothes["shield"].set_found(true);
            return;
        case found_armor:
            std::cout << std::endl << "armor found" << std::endl;
            clothes["armor"].set_found(true);
            return;

        default: return;
    }
}
void Player::print_moved(size_t &obj, const Map &map) const {
    obj = map.get_obj();
    if (obj == 0) {
        std::cout << std::endl << "moved" << std::endl;
        return;
    }
}

int Player::get_hp() const {
    return HP;
}

int Player::get_ARM() const {
    return ARM;
}

