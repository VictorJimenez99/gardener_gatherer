//
// Created by victor on 20/02/22.
//

#include "plant_raw.h"

#include <utility>

plant_raw::plant_raw(long id, long rack, long rack_position, std::string species, int humidity) :
        id(id), rack(rack), species(std::move(species)),
        rack_position(static_cast<std::byte>(rack_position)),
        humidity_status(static_cast<std::byte>(humidity)) {}


long plant_raw::get_id() const { return this->id; }

long plant_raw::get_rack() const { return this->rack; }

std::byte plant_raw::get_rack_position() const { return this->rack_position; }

std::string plant_raw::get_species() const { return {this->species}; }

std::byte plant_raw::get_humidity_status() const { return this->humidity_status; };

plant_raw::~plant_raw() = default;