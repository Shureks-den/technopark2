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
            element = empty_zone;
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
            field_[y][x] = armor;
        } else if (event == "helmet") {
            field_[y][x] = helmet;
        } else if (event == "shield") {
            field_[y][x] = shield;
        } else if (event == "pants") {
            field_[y][x] = pants;
        } else if (event == "T-Shirt") {
            field_[y][x] = T_Shirt;
        }
    }
    fin.close();
}


void Map::clear_zone(int y, int x) {
    field_[y][x] = 0;
}

int Map::get_obj(int y, int x) const {
    return field_[y][x];
}

size_t Map::get_height() const {
    return height_;
}

size_t Map::get_width() const {
    return width_;
}
