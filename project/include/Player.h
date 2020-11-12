#ifndef  PROJECT_INCLUDE_PLAYER_H_
#define  PROJECT_INCLUDE_PLAYER_H_

#include <utility>
#include <string>
#include <map>
#include "Map.h"

class Player {
 public:
    Player() = default;
    ~Player() = default;
    void kick_enemy(Creature &enemy, size_t &enemy_type, bool &enemy_live, Map &map);

    void pick_clothes(const std::string &command, std::map<std::string, Armor>& clothes, size_t &obj);
    void throw_clothes(const std::string &command, std::map<std::string, Armor>& clothes);

    void move(movement &move, const std::string &command, size_t &obj,
              Creature &enemy, Map &map, std::map<std::string, Armor>& clothes);

    void print_moved(size_t &obj, const Map &map) const;

    int get_hp() const;
    int get_ARM() const;

 private:
    int WGT = 0;
    int ARM = 0;
    int HP = 100;
    size_t DMG = 1;
};


#endif  // PROJECT_INCLUDE_PLAYER_H_
