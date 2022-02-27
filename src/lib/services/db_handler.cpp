//
// Created by victor on 20/02/22.
//

#include <iostream>
#include "db_handler.h"
#include <stdexcept>

db_handler::db_handler(const std::string &db_name) {
    std::string msg = "Establishing DB connection_handler...";
    int error = sqlite3_open(db_name.c_str(), &this->db);
    if (error != SQLITE_OK) {
        msg.append("Error: ")
                .append(sqlite3_errmsg(this->db)).append("\n");
        sqlite3_close(db);
        throw std::runtime_error(msg);
    }
    std::cout << msg.append("Success") << std::endl;
}


db_handler::~db_handler() {
    std::string msg = "Closing DB connection_handler...";
    int error = sqlite3_close(this->db);
    if (error != SQLITE_OK) {

        msg.append("Error: ")
                .append(sqlite3_errmsg(this->db)).append("\n");
        sqlite3_close(db);
        std::cerr << msg << std::endl;
    }
    std::cout << msg.append("Success") << std::endl;
}

/**DB ptr will still be valid if it fails*/
void db_handler::exec_void(const std::string &sql) {
    char *error;
    int ret_val = sqlite3_exec(this->db,
                               sql.c_str(),
                               nullptr,
                               nullptr,
                               &error);
    if (ret_val != SQLITE_OK) {
        std::string error_val;
        error_val.append("An error has occurred: ")
                .append(error).append("\n");
        sqlite3_free(error);
        throw std::runtime_error(error_val);
    }
}

