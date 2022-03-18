//
// Created by victor on 17/03/22.
//

#ifndef GARDENER_RACK_H
#define GARDENER_RACK_H

#include <string>

class rack {
private:
    long id;
    unsigned int total_rows;
    unsigned int total_columns;

    int available_slots;
    std::string description;


public:
    rack(long id, unsigned int total_rows, unsigned int total_columns, int available_slots, std::string description);
    ~rack();

    [[nodiscard]] long get_id() const;
    [[nodiscard]] unsigned int get_total_rows() const;
    [[nodiscard]] unsigned int get_total_columns() const;
    [[nodiscard]] int get_available_slots() const;
    [[nodiscard]] std::string get_description() const;



};


#endif //GARDENER_RACK_H
