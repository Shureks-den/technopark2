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

void Armor::print_armor_info(const std::map<std::string, Armor>& clothes) {
    for (const auto& [name, ch] : clothes) {
        if (ch.found && !ch.equipped) {
            std::cout << std::endl << " * pick " << name;
        }
    }
    for (const auto& [name, ch] : clothes) {
        if(ch.equipped) {
            std::cout << std::endl << " * throw " << name;
        }
    }
}