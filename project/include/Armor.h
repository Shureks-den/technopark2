#ifndef PROJECT_INCLUDE_ARMOR_H_
#define PROJECT_INCLUDE_ARMOR_H_

#include <iostream>
#include <string>
#include <map>

enum clothes_wgt {
    armor_wgt = 3,
    helmet_wgt = 2,
    shield_wgt = 7,
    pants_wgt = 1,
    T_Shirt_wgt = 1
};

enum clothes_armor {
    armor_arm = 3,
    helmet_arm = 3,
    shield_arm = 5,
    pants_arm = 1,
    T_Shirt_arm = 1
};

class Armor {
 public:
    Armor() = default;
    Armor(int WGT, int ARM);
    ~Armor() = default;

    void set_equipped(bool new_value);
    void set_found(bool new_value);

    int get_WGT() const;
    int get_ARM() const;
    bool get_equipped() const;
    bool get_found() const;

 private:
    bool equipped = false;
    bool found = false;
    int WGT;
    int ARM;
};


#endif  // PROJECT_INCLUDE_ARMOR_H_
