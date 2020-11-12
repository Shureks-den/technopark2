#ifndef PREP_2020_02_MAP_H
#define PREP_2020_02_MAP_H
/* идея сделать 0 пустой, свободной, для перемещения клеткой, 1 с оружием, 2 с монстром */

#include <iostream>
#include <vector>

#include "Creature.h"

typedef enum {
    safe_zone,  // 0
    enemy_wolf, // 1
    enemy_dog,  // 2
    enemy_rat, // 3
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

    void print_map();
    void where_to_move(movement &move) const;
    void enemy_dead();

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


#endif //PREP_2020_02_MAP_H
