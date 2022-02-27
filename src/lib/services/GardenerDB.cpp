//
// Created by victor on 24/02/22.
//

#include <stdexcept>
#include <iostream>
#include <memory>
#include "GardenerDB.h"
#include "../constants/tables.h"

GardenerDB::GardenerDB() : DBHandler("/opt/gardener/files/gardener_db.sqlite") {
    std::string result = "Setting up foreign keys support...";
    try {
        this->exec_void("PRAGMA foreign_keys = ON;");
        std::cout << result.append("Success") << std::endl;
    } catch (std::runtime_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

}

bool GardenerDB::schema_is_complete() {
    std::string sql = "SELECT name from sqlite_master WHERE type='table';";
    // we know that there will only be one column with the name = 'name'
    std::string log = "Checking database integrity...";
    char *error = nullptr;
    std::vector<std::string> available_tables = {};

    auto* ptr = &available_tables;

    auto fun = []
            (void *param, int, char **col_value, char**) -> int {
        auto *vector_c = *(std::vector<std::string>**)param;
        vector_c->push_back({*col_value});
        return 0;

    };
    int ret_val = sqlite3_exec(this->db, sql.c_str(),
                               fun,
                               &ptr, &error);
    if(ret_val != SQLITE_OK) {
        std::cout << log
                .append("Integrity check returned a non zero value: ")
                .append(std::to_string(ret_val))
                .append("\n");
    }

    if(error) {
        std::cout << "An error occurred while checking db integrity: " << error << std::endl;
        sqlite3_free(error);
        return false;
    }
    bool will_fail = false;

    std::vector<std::string> missing_tables = {};

    for(const auto& needed: NEEDED_TABLES) {
        bool found = false;
        for(const auto& table: available_tables){
            if(table == needed) {
                found = true;
                break;
            }
        }
        if(!found) {
            missing_tables.emplace_back(needed);
            will_fail = true;
        }
    }
    if(will_fail) {
        log.append("Error -> missing tables: ");
        std::for_each( missing_tables.begin(), missing_tables.end(), [&](std::string& elem){
           log.append(elem).append(" ");
        });
        std::cout << log << std::endl;
        return false;//fail state
    }
    std::cout << log.append("Success\n");
    return true;
}
