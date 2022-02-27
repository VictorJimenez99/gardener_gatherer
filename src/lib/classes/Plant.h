//
// Created by victor on 20/02/22.
//

#ifndef GARDENER_PLANT_H
#define GARDENER_PLANT_H

#include <string>
#include <memory>

class Plant {
private:
    long id;
    long rack;
    std::byte rack_position;
    std::string species;
    std::byte humidity_status;

public:
    Plant(long id, long rack, long rack_position, std::string species, int status);
    ~Plant();

    [[nodiscard]] long get_id() const;
    [[nodiscard]] long get_rack() const;
    [[nodiscard]] std::byte get_rack_position() const;
    [[nodiscard]] std::string get_species() const;
    [[nodiscard]] std::byte get_humidity_status() const;

};


#endif //GARDENER_PLANT_H
