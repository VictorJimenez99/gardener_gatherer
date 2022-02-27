//
// Created by victor on 20/02/22.
//

#include "Plant.h"

#include <utility>

Plant::Plant(long id, long rack, long rack_position, std::string species, int humidity):
        id(id), rack(rack), species(std::move(species)),
        rack_position(static_cast<std::byte>(rack_position)),
        humidity_status(static_cast<std::byte>(humidity)) {}


long Plant::get_id() const {return this->id;}

long Plant::get_rack() const {return this->rack;}

std::byte Plant::get_rack_position() const {return this->rack_position;}

std::string Plant::get_species() const {return {this->species};}

std::byte Plant::get_humidity_status() const {return this->humidity_status;};

Plant::~Plant() = default;