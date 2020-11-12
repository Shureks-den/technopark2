#include "Game.h"

Game::Game(const std::string &file_name, bool stage2) : enemy_live(false), map(file_name), player(), stage2(stage2) { }


void Game::print_player_st1() const {
    std::cout << std::endl << map.get_x() << " x " << map.get_y() << ", hp: " << player.get_hp() << " > ";
}

void Game::print_player_st2() const {
    std::cout << std::endl << map.get_x() << " x " << map.get_y() << ", hp: " << player.get_hp() <<
    ", armor: " << player.get_ARM() << " > ";
}

movement& Game::print_actions(size_t obj, movement &move, bool &enemy_live, Map &map,
                              std::map<std::string, Armor>& clothes) {
    std::cout << "Supported actions:";

    if (obj >= enemy_wolf && obj <= enemy_rat) {
        enemy_live = true;
        std::cout << std::endl << " * kick enemy";
    } else {
        map.where_to_move(move);
        if (obj > enemy_rat) {
            print_status_clothes(clothes);
        }
    }
    return move;
}

void Game::execute_command(Creature &enemy, const std::string command, size_t &obj, movement &move,
                           std::map<std::string, Armor> &clothes) {
    if (command == "move left" || command == "move right" || command == "move up" || command == "move down") {
        map.enemy_dead();

        for (auto&[name, ch] : clothes) {
            clothes[name] = ch;
            ch.set_found(false);
        }
        player.move(move, command, obj, enemy, map, clothes);
    }

    if (command == "kick enemy" && enemy_live) {
        player.kick_enemy(enemy, obj, enemy_live, map);
        return;
    }

    if (command.compare(0, 4, "pick") == 0) {
        player.pick_clothes(command, clothes, obj);
        return;
    }

    if (command.compare(0, 5, "throw") == 0) {
        player.throw_clothes(command, clothes);
    }
}

void Game::run() {
    Creature enemy;
    size_t obj = 0;
    movement move;
    std::string command;
    std::map<std::string, Armor> clothes;
    init_clothes(clothes);

    while (player.get_hp() > 0) {
        move = print_actions(obj, move, enemy_live, map, clothes);
        if (stage2) {
            print_player_st2();
        } else {
            print_player_st1();
        }
        if (!getline(std::cin, command)) {
            return;
        }
        execute_command(enemy, command, obj, move, clothes);
    }
    std::cout << std::endl << "player died" << std::endl;
}

void Game::init_clothes(std::map<std::string, Armor> &clothes) {
    clothes["armor"] = {armor_wgt, armor_arm};
    clothes["helmet"] = {helmet_wgt, helmet_arm};
    clothes["shield"] = {shield_wgt, shield_arm};
    clothes["pants"] = {pants_wgt, pants_arm};
    clothes["T-Shirt"] = {T_Shirt_wgt, T_Shirt_arm};
}

void Game::print_status_clothes(std::map<std::string, Armor> &clothes) {
    for (const auto& [name, ch] : clothes) {
        if (ch.get_found() && !ch.get_equipped()) {
            std::cout << std::endl << " * pick " << name;
        }
    }

    for (const auto& [name, ch] : clothes) {
        if (ch.get_equipped()) {
            std::cout << std::endl << " * throw " << name;
        }
    }
}
