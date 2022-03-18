//
// Created by victor on 17/03/22.
//

#include "rack.h"

#include <utility>

rack::~rack() = default;

long rack::get_id() const {
    return this->id;
}

unsigned int rack::get_total_rows() const {
    return this->total_rows;
}

unsigned int rack::get_total_columns() const {
    return this->total_columns;
}

int rack::get_available_slots() const {
    return this->available_slots;
}

std::string rack::get_description() const {
    return this->description;
}

rack::rack(long id, unsigned int total_rows,
           unsigned int total_columns,
           int available_slots, std::string description):
           id(id), total_rows(total_rows),
           total_columns(total_columns), available_slots(available_slots), description(std::move(description)) {}
