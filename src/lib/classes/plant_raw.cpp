//
// Created by victor on 20/02/22.
//

#include "plant_raw.h"
#include <utility>


plant_raw::~plant_raw() = default;

plant_raw::plant_raw(long rack, long rack_x, long rack_y, std::string species):
rack(rack), rack_x(rack_x), rack_y(rack_y), species(std::move(species)) {}

long plant_raw::get_rack() const {
    return this->rack;
}

long plant_raw::get_rack_x() const {
    return this->rack_x;
}

long plant_raw::get_rack_y() const {
    return this->rack_y;
}

std::string plant_raw::get_species() const {
    return this->species;
}

std::tuple<int, int, int> plant_raw::get_primary_key() const {
    return {rack, rack_x, rack_y};
}
