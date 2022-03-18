//
// Created by victor on 20/02/22.
//

#ifndef GARDENER_PLANT_RAW_H
#define GARDENER_PLANT_RAW_H

#include <string>
#include <memory>

class plant_raw {
private:
    long rack;
    long rack_x;
    long rack_y;
    std::string species;

public:
    //typedef std::unique_ptr<plant_raw> ptr;
    plant_raw(long rack, long rack_x, long rack_y, std::string species);
    ~plant_raw();
    [[nodiscard]] long get_rack() const;
    [[nodiscard]] long get_rack_x() const;
    [[nodiscard]] long get_rack_y() const;
    [[nodiscard]] std::string get_species() const;
    [[nodiscard]] std::tuple<int, int, int> get_primary_key() const;
};


#endif //GARDENER_PLANT_RAW_H
