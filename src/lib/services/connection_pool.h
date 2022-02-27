//
// Created by victor on 27/02/22.
//

#ifndef GARDENER_CONNECTION_POOL_H
#define GARDENER_CONNECTION_POOL_H


#include <utility>
#include <atomic>
#include <mutex>
#include <vector>
#include <memory>
#include "gardener_db.h"

class pool_elem {
private:
    std::atomic_bool is_busy;
    gardener_db connection;
public:
    pool_elem();

    bool get_is_busy_weak();

    std::atomic_bool &get_is_busy_ref();

    gardener_db &get_conn();
};

class connection_pool_inner {
private:
    // first answers the questions, isBusy?
    // true means busy - false means available
    std::mutex vector_mutex;
    std::vector<std::shared_ptr<pool_elem>> pool;

    connection_pool_inner();

public:
    static connection_pool_inner *instance();

    connection_pool_inner(const connection_pool_inner &) = delete;

    void operator=(const connection_pool_inner &) = delete;

    gardener_db &get_connection();

    bool drop_one(gardener_db &connection);


    void release_connection(gardener_db &connection);
};


class connection_handler {
private:
    connection_pool_inner *inner;
    gardener_db *db;

public:
    connection_handler();

    ~connection_handler();

    gardener_db *&get();

};


#endif //GARDENER_CONNECTION_POOL_H
