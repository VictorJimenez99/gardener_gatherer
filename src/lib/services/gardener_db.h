//
// Created by victor on 24/02/22.
//

#ifndef GARDENER_GARDENER_DB_H
#define GARDENER_GARDENER_DB_H


#include "db_handler.h"

class gardener_db : public db_handler {

public:
    gardener_db();

    bool schema_is_complete();

};


#endif //GARDENER_GARDENER_DB_H
