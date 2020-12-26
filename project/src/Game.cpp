#include "Game.h"

Game::Game(const std::string &file_name, bool stage2) : enemy_live(false), map(file_name), player(), stage2(stage2) { }


void Game::print_player_st1() const {
    std::cout << std::endl << player.get_x() << " x " << player.get_y() << ", hp: " << player.get_HP() << " > ";
}

void Game::print_player_st2() const {
    std::cout << std::endl << player.get_x() << " x " << player.get_y() << ", hp: " << player.get_HP() <<
    ", armor: " << player.get_ARM() << " > ";
}

movement& Game::print_actions(size_t obj, movement &move, bool &enemy_live, Map &map,
                              std::map<std::string, Armor>& clothes) {
    std::cout << "Supported actions:";

    if (is_enemy(obj)) {
        enemy_live = true;
        std::cout << std::endl << " * kick enemy";
    } else {
        player.where_to_move(move, map);
        if (is_clothes(obj)) {
            print_status_clothes(clothes);
        }
    }
    return move;
}

void Game::execute_command(Creature &enemy, const std::string command, size_t &obj, movement &move,
                           std::map<std::string, Armor> &clothes) {
    if (command == "move left" || command == "move right" || command == "move up" || command == "move down") {
        map.clear_zone(player.get_y(), player.get_x());

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

    if (command.find("pick") != std::string::npos) {
        player.pick_clothes(command, clothes, obj);
        return;
    }

    if (command.find("throw") != std::string::npos) {
        player.throw_clothes(command, clothes);
    }
}


bool Game::is_enemy(size_t obj) {
    if (obj == enemy_wolf) {
        return true;
    }  
    if (obj == enemy_dog) {
        return true;
    } 
    if (obj == enemy_rat) {
        return true;
    }
    return false;
}

bool Game::is_clothes(size_t obj) {
   if (obj == clothes_armor) {
        return true;
    }  
    if (obj == clothes_helmet) {
        return true;
    } 
    if (obj == clothes_pants) {
        return true;
    }
    if (obj == clothes_shield) {
        return true;
    }
    if (obj == clothes_T_Shirt) {
        return true;
    }
    return false; 
}

void Game::run() {
    Creature enemy;
    size_t obj = 0;
    movement move;
    std::string command;
    std::map<std::string, Armor> clothes;
    init_clothes(clothes);

    while (player.get_HP() > 0) {
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
