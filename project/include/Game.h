#ifndef PROJECT_INCLUDE_GAME_H_
#define PROJECT_INCLUDE_GAME_H_

#include <iostream>
#include <string>
#include <map>
#include "Player.h"

class Game {
 public:
    Game() = default;
    explicit Game(const std::string &file_name, bool stage2);
    ~Game() = default;

    void run();

 private:
    bool enemy_live;
    void print_player_st1() const;
    void print_player_st2() const;
    void init_clothes(std::map<std::string, Armor>& clothes);
    void print_status_clothes(std::map<std::string, Armor>& clothes);
    movement &print_actions(size_t obj, movement &move, bool &enemy_live,
                            Map &map, std::map<std::string, Armor>& clothes);
    void execute_command(Creature &enemy, const std::string command, size_t &obj,
                         movement &move, std::map<std::string, Armor>& clothes);
    Map map;
    Player player;
    bool stage2;
};

#endif  // PROJECT_INCLUDE_GAME_H_
