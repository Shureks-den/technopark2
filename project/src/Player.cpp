#include "Player.h"
void Player::kick_enemy(Creature &enemy, size_t &enemy_type, bool &enemy_live, Map &map) {
    enemy.set_HP(enemy.get_HP() - DMG);

    if(enemy.get_HP() <= 0) {
        std::cout << std::endl << "enemy killed" << std::endl;
        enemy_live = false;
        enemy.update_enemy_hp();
        map.enemy_dead();
        enemy_type = 0;
        return;
    }

    HP -= (enemy.get_base_DMG() + enemy.get_weapon_DMG());

    if(HP > 0) {
        std::cout << std::endl << "enemy kicked. Enemy hp: " << enemy.get_HP() << std::endl;
    }
}
void Player::move(movement &move, const std::string &command, size_t &obj, Creature &enemy, Map &map) {
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

        default: return;
    }
}
void Player::print_moved(size_t &obj, const Map &map) const {
    obj = map.get_obj();
    if(obj == 0) {
        std::cout << std::endl << "moved" << std::endl;
        return;
    }
}

int Player::get_hp() const {
    return HP;
}

