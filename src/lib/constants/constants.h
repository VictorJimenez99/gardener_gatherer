//
// Created by victor on 25/02/22.
//

#ifndef GARDENER_CONSTANTS_H
#define GARDENER_CONSTANTS_H

#include <string>

constexpr char *NEEDED_TABLES[] = {(char *) "rack",
                                   (char *) "plant",
                                   (char*) "measurement"
                                   };
constexpr unsigned int CONNECTION_POOL_SIZE = 20;
//constexpr char* DB_NAME = (char*)"/opt/gardener/files/gardener_db.sqlite";
constexpr char *DB_NAME = (char *) "gardener_db.sqlite";

constexpr unsigned int MAX_DB_RETRIES = 200;

#endif //GARDENER_CONSTANTS_H
