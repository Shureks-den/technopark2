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

class Map{
 public:
    Map() = default;
    ~Map() = default;
    explicit Map(const std::string &path_to_map);

    void clear_zone(int y, int x);
    [[nodiscard]] int get_obj(int y, int x) const;

    [[nodiscard]] size_t get_width() const;
    [[nodiscard]] size_t get_height() const;

 private:
    size_t height_;
    size_t width_;
    std::vector<std::vector<int>> field_;
};

#endif  // PROJECT_INCLUDE_MAP_H_
