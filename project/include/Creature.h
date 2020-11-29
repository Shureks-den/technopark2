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

    [[nodiscard]] int get_base_DMG() const;
    [[nodiscard]] int get_HP() const;
    [[nodiscard]] int get_weapon_DMG() const;
    void take_dmg(int dmg);

 protected:
    int DMG_base = 1;
    int HP_;

 private:
    std::string enemy_name;
    int weapon_DMG;
};

#endif  // PROJECT_INCLUDE_CREATURE_H_
