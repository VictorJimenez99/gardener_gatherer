//
// Created by victor on 20/02/22.
//

#ifndef GARDENER_DB_HANDLER_H
#define GARDENER_DB_HANDLER_H


#include <sqlite3.h>
#include <string>

class db_handler {
protected:
    sqlite3 *db{nullptr};

public:
    explicit db_handler(const std::string &db_name);

    ~db_handler();

    void exec_void(const std::string &sql);
};


#endif //GARDENER_DB_HANDLER_H
