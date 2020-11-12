#ifndef PROJECT_INCLUDE_CREATURE_H_
#define PROJECT_INCLUDE_CREATURE_H_

#include <iostream>
#include <vector>
#include <string>

enum enemy_hp {
    wolf_hp = 6,
    dog_hp = 3,
    rat_hp = 2
};

enum enemy_dmg {
    wolf_dmg = 10,
    dog_dmg = 5,
    rat_dmg = 3
};

class Creature {
 public:
    Creature() = default;
    explicit Creature(size_t type);
    ~Creature() = default;

    void print_info();
    void update_enemy_hp();

    [[nodiscard]] size_t get_base_DMG() const;
    [[nodiscard]] int get_HP() const;
    [[nodiscard]] size_t get_weapon_DMG() const;
    void set_HP(int new_value);

 private:
    std::string enemy_name;
    size_t DMG_base = 1;
    size_t weapon_DMG;
    int HP_;
};

#endif  // PROJECT_INCLUDE_CREATURE_H_
