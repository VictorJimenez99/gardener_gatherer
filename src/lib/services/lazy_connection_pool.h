//
// Created by victor on 05/03/22.
//

#ifndef GARDENER_LAZY_CONNECTION_POOL_H
#define GARDENER_LAZY_CONNECTION_POOL_H

#include <atomic>
#include <array>
#include <memory>
#include <utility>
#include "gardener_db.h"
#include "../constants/constants.h"

class pool_element {
private:
    std::atomic_bool is_busy;
    std::shared_ptr<gardener_db> connection;
public:
    pool_element():is_busy(false), connection(std::make_shared<gardener_db>()){};
    std::atomic_bool& get_is_busy_ref() {return is_busy;};
    std::shared_ptr<gardener_db> get_connection() {return connection;};
};

class pool_request_result {
private:
    bool success;
    std::shared_ptr<gardener_db>* db;

public:
    pool_request_result(bool is_successful, std::shared_ptr<gardener_db>* conn): success(is_successful), db(conn){};
    [[nodiscard]] bool was_successful() const{return success;};
    std::shared_ptr<gardener_db>* get() {return db;};


};


class lazy_connection_pool {
private:
    std::array<std::shared_ptr<pool_element>, CONNECTION_POOL_SIZE> pool;
    lazy_connection_pool();

public:
    static lazy_connection_pool& get_instance();
    pool_request_result get_connection();

    void give_back(const std::shared_ptr<gardener_db>&db_conn);
};

// TODO: add a static counter to this object, every time an owned connection gets created add one to it,
// TODO: decremented when its deleted
// TODO: busy wait(or sleep) if THRESHOLD is reached
// TODO: think about timeout exceptions since a THRESHOLD number of stale connection will still
// TODO: lock the system

class db_connection {
private:
    lazy_connection_pool& pool_connection;
    bool ownership;// once assigned it should freeze
    std::shared_ptr<gardener_db> db;
public:

    db_connection();
    ~db_connection();
    [[nodiscard]] bool get_ownership() const{return ownership;};

    std::shared_ptr<gardener_db> get();
};


#endif //GARDENER_LAZY_CONNECTION_POOL_H
