#include "Armor.h"
Armor::Armor(int WGT, int ARM) : WGT(WGT), ARM(ARM) { }

void Armor::set_equipped(bool new_value) {
    equipped = new_value;
}

void Armor::set_found(bool new_value) {
    found = new_value;
}

int Armor::get_ARM() const {
    return ARM;
}

int Armor::get_WGT() const {
    return WGT;
}

bool Armor::get_equipped() const {
    return equipped;
}

bool Armor::get_found() const {
    return found;
}

