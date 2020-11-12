#ifndef PREP_2020_02_PLAYER_H
#define PREP_2020_02_PLAYER_H
#include "Map.h"

class Player {
public:
    Player() = default;
    ~Player() = default;
    void kick_enemy (Creature &enemy, size_t &enemy_type, bool &enemy_live, Map &map);

    void move(movement &move, const std::string &command, size_t &obj,
              Creature &enemy, Map &map);

    void print_moved(size_t &obj, const Map &map) const;

    int get_hp() const;

private:
    int HP = 100;
    size_t DMG = 1;
};


#endif //PREP_2020_02_PLAYER_H
