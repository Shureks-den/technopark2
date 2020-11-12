#ifndef PREP_2020_02_GAME_H
#define PREP_2020_02_GAME_H


#include <iostream>
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


#endif //PREP_2020_02_GAME_H
