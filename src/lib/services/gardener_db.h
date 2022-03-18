//
// Created by victor on 24/02/22.
//

#ifndef GARDENER_GARDENER_DB_H
#define GARDENER_GARDENER_DB_H


#include <optional>
#include "db_handler.h"
#include <vector>
#include "../classes/rack.h"

class gardener_db : public db_handler {

public:
    gardener_db();
    bool schema_is_complete();
    std::vector<rack> get_racks();
    std::optional<rack> get_rack_by_id();

};


#endif //GARDENER_GARDENER_DB_H
