//
// Created by victor on 20/02/22.
//

#ifndef GARDENER_PLANT_RAW_H
#define GARDENER_PLANT_RAW_H

#include <string>
#include <memory>

class plant_raw {
private:
    long id;
    long rack;
    std::byte rack_position;
    std::string species;
    std::byte humidity_status;

public:
    //typedef std::unique_ptr<plant_raw> ptr;
    plant_raw(long id, long rack, long rack_position, std::string species, int humidity_status);

    ~plant_raw();

    [[nodiscard]] long get_id() const;

    [[nodiscard]] long get_rack() const;

    [[nodiscard]] std::byte get_rack_position() const;

    [[nodiscard]] std::string get_species() const;

    [[nodiscard]] std::byte get_humidity_status() const;

};


#endif //GARDENER_PLANT_RAW_H
