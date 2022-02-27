//
// Created by victor on 24/02/22.
//

#ifndef GARDENER_GARDENER_DB_H
#define GARDENER_GARDENER_DB_H


#include "DBHandler.h"

class GardenerDB: public DBHandler {

public:
    GardenerDB();

    bool schema_is_complete();

};


#endif //GARDENER_GARDENER_DB_H
