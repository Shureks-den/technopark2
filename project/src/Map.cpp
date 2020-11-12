#include <fstream>

#include "Map.h"


Map::Map(const std::string &path_to_map) {
    width_ = 0;
    height_ = 0;
    std::ifstream fin(path_to_map);
    if (!fin.is_open()) {
        std::cout << "file error" << std::endl;
        exit(1);
    }
    fin >> width_ >> height_;

    field_.resize(height_);
    for (auto& row : field_) {
        row.resize(width_);
        for (auto &element : row) {
            element = safe_zone;
        }
    }
    int x = 0;
    int y = 0;
    std::string event;
    while (fin >> x >> y >> event) {
        if (event == "dog") {
            field_[y][x] = enemy_dog;
        } else if (event == "wolf") {
            field_[y][x] = enemy_wolf;
        } else if (event == "rat") {
            field_[y][x] = enemy_rat;
        } else if (event == "armor") {
            field_[y][x] = found_armor;
        } else if (event == "helmet") {
            field_[y][x] = found_helmet;
        } else if (event == "shield") {
            field_[y][x] = found_shield;
        } else if (event == "pants") {
            field_[y][x] = found_pants;
        } else if (event == "T-Shirt") {
            field_[y][x] = found_T_Shirt;
        }
    }
    fin.close();
}

void Map::where_to_move(movement &move) const {
    if (pos.x > 0) {
        move.left = true;
        std::cout << std::endl << " * move left";
    } else {
        move.left = false;
    }

    if (pos.x + 1 < width_) {
        move.right = true;
        std::cout << std::endl << " * move right";
    } else {
        move.right = false;
    }

    if (pos.y > 0) {
        move.down = true;
        std::cout << std::endl << " * move down";
    } else {
        move.down = false;
    }

    if (pos.y + 1 < height_) {
        move.up = true;
        std::cout << std::endl << " * move up";
    } else {
        move.up = false;
    }
    if (!(move.right || move.left || move.down || move.up)) {
        std::cout << std::endl;
    }
}

void Map::print_map() {
    for (size_t i = 0; i < width_; i++) {
        for (size_t j = 0; j < height_; j++) {
            std::cout << field_[j][i] << "  ";
        }
        std::cout << std::endl;
    }
}

void Map::enemy_dead() {
    field_[pos.y][pos.x] = 0;
}

int Map::get_obj() const {
    return field_[pos.y][pos.x];
}
size_t Map::get_x() const {
    return pos.x;
}

size_t Map::get_y() const {
    return pos.y;
}

void Map::set_x(size_t new_value) {
    pos.x = new_value;
}

void Map::set_y(size_t new_value) {
    pos.y = new_value;
}


