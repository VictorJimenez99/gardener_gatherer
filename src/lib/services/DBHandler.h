//
// Created by victor on 20/02/22.
//

#ifndef GARDENER_DB_HANDLER_H
#define GARDENER_DB_HANDLER_H


#include <sqlite3.h>
#include <string>
#include <functional>

class DBHandler {
protected:
    sqlite3 *db{nullptr};

public:
    explicit DBHandler(const std::string& db_name);
    ~DBHandler();

    void exec_void(const std::string &sql);

};


#endif //GARDENER_DB_HANDLER_H
