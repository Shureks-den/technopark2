#include "Game.h"

Game::Game(const std::string &file_name) : enemy_live(false), map(file_name), player() { }


void Game::print_player() const {
    std::cout << std::endl << map.get_x() << " x " << map.get_y() << ", hp: " << player.get_hp() << " > ";
}

movement& Game::print_actions(size_t obj, movement &move, bool &enemy_live) {
    std::cout << "Supported actions:";

    if(obj >= enemy_wolf && obj <= enemy_rat) {
        enemy_live = true;
        std::cout << std::endl << " * kick enemy";
    } else {
        map.where_to_move(move);
    }
    return move;
}

void Game::execute_command(Creature &enemy, const std::string command, size_t &obj, movement &move) {
    if (command == "move left" || command == "move right" || command == "move up" || command == "move down") {
        player.move(move, command, obj, enemy, map);
    }
    if (command == "kick enemy" && enemy_live) {
        player.kick_enemy(enemy, obj, enemy_live, map);
        return;
    }
}

void Game::run() {
    Creature enemy;
    size_t obj = 0;
    movement move;
    std::string command;

    while(player.get_hp() > 0) {
        move = print_actions(obj, move, enemy_live);
        print_player();
        if (!getline(std::cin, command)) {
            return;
        }
        execute_command(enemy, command, obj, move);
    }
    std::cout << std::endl << "player died" << std::endl;
}