//
// Created by victor on 24/02/22.
//

#include <stdexcept>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "gardener_db.h"
#include "../constants/constants.h"


gardener_db::gardener_db() : db_handler(DB_NAME) {
    std::string result = "Setting up foreign keys support...";
    try {
        this->exec_void("PRAGMA foreign_keys = ON;");
        std::cout << result.append("Success") << std::endl;
    } catch (std::runtime_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

}

bool gardener_db::schema_is_complete() {
    std::string sql = "SELECT name from sqlite_master WHERE type='table';";
    // we know that there will only be one column with the name = 'name'
    std::string log = "Checking database integrity...";
    char *error = nullptr;
    std::vector<std::string> available_tables = {};

    auto *ptr = &available_tables;

    auto fun = []
            (void *param, int, char **col_value, char **) -> int {
        auto *vector_c = *(std::vector<std::string> **) param;
        vector_c->push_back({*col_value});
        return 0;

    };
    int ret_val = sqlite3_exec(this->db, sql.c_str(),
                               fun,
                               &ptr, &error);
    if (ret_val != SQLITE_OK) {
        std::cout << log
                .append("Integrity check returned a non zero value: ")
                .append(std::to_string(ret_val))
                .append("\n");
    }

    if (error) {
        std::cout << "An error occurred while checking db integrity: " << error << std::endl;
        sqlite3_free(error);
        return false;
    }
    bool will_fail = false;

    std::vector<std::string> missing_tables = {};

    for (const auto &needed: NEEDED_TABLES) {
        bool found = false;
        for (const auto &table: available_tables) {
            if (table == needed) {
                found = true;
                break;
            }
        }
        if (!found) {
            missing_tables.emplace_back(needed);
            will_fail = true;
        }
    }
    if (will_fail) {
        log.append("Error -> missing tables: ");
        std::for_each(missing_tables.begin(), missing_tables.end(), [&](std::string &elem) {
            log.append(elem).append(" ");
        });
        std::cout << log << std::endl;
        return false;//fail state
    }
    std::cout << log.append("Success\n");
    return true;
}

std::vector<rack> gardener_db::get_racks() {
    std::string sql = "SELECT * from rack;";
    size_t sql_len = sql.length();
    sqlite3_stmt *byte_code_statement = nullptr;
    const char *unused = nullptr;

    sqlite3_prepare_v2(this->db, sql.c_str(), -1, &byte_code_statement, &unused);


    int step = sqlite3_step(byte_code_statement);
    int retry_attempts = 0;
    if(step == SQLITE_BUSY) {
        while (step == SQLITE_BUSY) {
            retry_attempts++;
            if (retry_attempts >= MAX_DB_RETRIES) {
                sqlite3_finalize(byte_code_statement);
                throw std::runtime_error("Unable to acquire database locks");
            }
            step = sqlite3_step(byte_code_statement);
        }
    }
    std::vector<rack> vector;

    while(step != SQLITE_DONE) {
        std::string error;
        switch (step) {
            case SQLITE_ROW: {
                int num_col = sqlite3_column_count(byte_code_statement);
                if(num_col != 5) {
                    std::string error = "Expected 5 columns for  rack, found: ";
                    error.append(std::to_string(num_col));
                    sqlite3_finalize(byte_code_statement);
                    throw std::runtime_error(error);
                }
                long id;
                unsigned int rows;
                unsigned int cols;
                int available_slots;
                std::string description;
                for(int i = 0; i < num_col; i++) {
                    if(i == 0) {//id
                        id = sqlite3_column_int64(byte_code_statement, i);
                    }else if(i == 1) {//rows
                        rows = sqlite3_column_int(byte_code_statement, i);
                    }else if(i == 2) {//cols
                        cols = sqlite3_column_int(byte_code_statement, i);
                    }else if(i == 3) {//available_slots
                        available_slots = sqlite3_column_int(byte_code_statement, i);
                    }else if(i == 4) {//description
                        const char *description_c_str = reinterpret_cast<const char *>
                                (sqlite3_column_text(byte_code_statement, i));
                        description = description_c_str;
                    }
                }
                vector.emplace_back(id, rows, cols, available_slots, description);
                break;
            }
            case SQLITE_MISUSE: {
                error = "ERROR: DB_MISUSE";

                sqlite3_finalize(byte_code_statement);
                throw std::runtime_error(error);
                break;
            }
            default: {
                error = "ERROR code: ";
                error.append(std::to_string(step));
                sqlite3_finalize(byte_code_statement);
                throw std::runtime_error(error);
                break;
            }
        }
        step = sqlite3_step(byte_code_statement);
    }
    sqlite3_finalize(byte_code_statement);
    return vector;
}
