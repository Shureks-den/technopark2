#include "Player.h"

Player::Player() {
    HP_ = 100;
    WGT = 0;
    ARM = 0;
}

void Player::kick_enemy(Creature &enemy, size_t &enemy_type, bool &enemy_live, Map &map) {
    enemy.take_dmg(DMG_base);

    if (enemy.get_HP() <= 0) {
        std::cout << std::endl << "enemy killed" << std::endl;
        enemy_live = false;
        map.clear_zone(this->get_y(), this->get_x());
        enemy_type = 0;
        return;
    }
    if ((enemy.get_weapon_DMG() + enemy.get_base_DMG()) <= ARM) {
        this->take_dmg(1);
    } else {
        this->take_dmg(((enemy.get_base_DMG() + enemy.get_weapon_DMG()) - ARM));
    }

    if (HP_ > 0) {
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
        this->set_x(this->get_x() - 1);
        print_moved(obj, map);
    }
    if (command == "move right" && move.right) {
        this->set_x(this->get_x() + 1);
        print_moved(obj, map);
    }
    if (command == "move down" && move.down) {
        this->set_y(this->get_y() - 1);
        print_moved(obj, map);
    }
    if (command == "move up" && move.up) {
        this->set_y(this->get_y() + 1);
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
        case clothes_pants:
            std::cout << std::endl << "pants found" << std::endl;
            clothes["pants"].set_found(true);
            return;
        case clothes_helmet:
            std::cout << std::endl << "helmet found" << std::endl;
            clothes["helmet"].set_found(true);
            return;
        case clothes_T_Shirt:
            std::cout << std::endl << "T-Shirt found" << std::endl;
            clothes["T-Shirt"].set_found(true);
            return;
        case clothes_shield:
            std::cout << std::endl << "shield found" << std::endl;
            clothes["shield"].set_found(true);
            return;
        case clothes_armor:
            std::cout << std::endl << "armor found" << std::endl;
            clothes["armor"].set_found(true);
            return;

        default: return;
    }
}
void Player::print_moved(size_t &obj, const Map &map) const {
    obj = map.get_obj(get_y(), get_x());
    if (obj == 0) {
        std::cout << std::endl << "moved" << std::endl;
        return;
    }
}

int Player::get_ARM() const {
    return ARM;
}

size_t Player::get_x() const {
    return pos.x;
}

size_t Player::get_y() const {
    return pos.y;
}

void Player::set_x(size_t new_value) {
    pos.x = new_value;
}

void Player::set_y(size_t new_value) {
    pos.y = new_value;
}

void Player::where_to_move(movement &move, Map map) const {
    if (pos.x > 0) {
        move.left = true;
        std::cout << std::endl << " * move left";
    } else {
        move.left = false;
    }

    if (pos.x + 1 < map.get_width()) {
        move.right = true;
        std::cout << std::endl << " * move right";
    } else {
        move.right = false;
    }

    if (pos.y > 0) {
        move.down = true;
        std::cout << std::endl << " * move down";
    } else {
        move.down = false;
    }

    if (pos.y + 1 < map.get_height()) {
        move.up = true;
        std::cout << std::endl << " * move up";
    } else {
        move.up = false;
    }
    if (!(move.right || move.left || move.down || move.up)) {
        std::cout << std::endl;
    }
}
