#ifndef PROJECT_INCLUDE_GAME_H_
#define PROJECT_INCLUDE_GAME_H_

#include <iostream>
#include <string>

#include "Player.h"

class Game {
 public:
    Game() = default;
    explicit Game(const std::string &file_name);
    ~Game() = default;

    void run();

 private:
    bool enemy_live;
    void print_player() const;
    movement &print_actions(size_t obj, movement &move, bool &enemy_live);
    void execute_command(Creature &enemy, const std::string command, size_t &obj,
                         movement &move);
    Map map;
    Player player;
};

#endif  // PROJECT_INCLUDE_GAME_H_
