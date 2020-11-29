#ifndef  PROJECT_INCLUDE_PLAYER_H_
#define  PROJECT_INCLUDE_PLAYER_H_

#include <utility>
#include <string>
#include <map>
#include "Map.h"

struct player_pos {
    size_t x = 0;
    size_t y = 0;
};

struct movement {
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
};

class Player : public Creature {
 public:
    Player();
    void kick_enemy(Creature &enemy, size_t &enemy_type, bool &enemy_live, Map &map);

    void pick_clothes(const std::string &command, std::map<std::string, Armor>& clothes, size_t &obj);
    void throw_clothes(const std::string &command, std::map<std::string, Armor>& clothes);

    void where_to_move(movement &move, Map map) const;
    void move(movement &move, const std::string &command, size_t &obj,
              Creature &enemy, Map &map, std::map<std::string, Armor>& clothes);

    [[nodiscard]] int get_ARM() const;
    [[nodiscard]] size_t get_y() const;
    [[nodiscard]] size_t get_x() const;

 private:
    void set_y(size_t new_value);
    void set_x(size_t new_value);
    void print_moved(size_t &obj, const Map &map) const;

 private:
    int WGT;
    int ARM;
    player_pos pos;
};


#endif  // PROJECT_INCLUDE_PLAYER_H_
