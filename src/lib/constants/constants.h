//
// Created by victor on 25/02/22.
//

#ifndef GARDENER_CONSTANTS_H
#define GARDENER_CONSTANTS_H

#include <string>

constexpr char *NEEDED_TABLES[] = {(char *) "rack", (char *) "plant",};
constexpr unsigned int CONNECTION_POOL_START_SIZE = 20;
//constexpr char* DB_NAME = (char*)"/opt/gardener/files/gardener_db.sqlite";
constexpr char *DB_NAME = (char *) "gardener_db.sqlite";

#endif //GARDENER_CONSTANTS_H
