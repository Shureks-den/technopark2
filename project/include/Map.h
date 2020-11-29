#ifndef PROJECT_INCLUDE_MAP_H_
#define PROJECT_INCLUDE_MAP_H_

#include <iostream>
#include <vector>
#include <string>

#include "Creature.h"
#include "Armor.h"

typedef enum {
    empty_zone,  // 0
    enemy_wolf,  // 1
    enemy_dog,  // 2
    enemy_rat,  // 3
    armor,  // 4
    helmet,  // 5
    shield,  // 6
    pants,  // 7
    T_Shirt  // 8
} map_event_t;

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

class Map{
 public:
    Map() = default;
    ~Map() = default;
    explicit Map(const std::string &path_to_map);

    void where_to_move(movement &move) const;
    void clear_zone();

    size_t get_x() const;
    size_t get_y() const;
    int get_obj() const;

    void set_x(size_t new_value);
    void set_y(size_t new_value);
 private:
    size_t height_;
    size_t width_;
    std::vector<std::vector<int>> field_;
    player_pos pos;
};

#endif  // PROJECT_INCLUDE_MAP_H_
