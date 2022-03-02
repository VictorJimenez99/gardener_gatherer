//
// Created by victor on 27/02/22.
//

#include "connection_pool.h"
#include "../constants/constants.h"

connection_pool_inner::connection_pool_inner() {
    for (int i = 0; i < CONNECTION_POOL_START_SIZE; i++) {
        pool.emplace_back(std::make_shared<pool_elem>());
    }
}

gardener_db &connection_pool_inner::get_connection() {
    bool expected = false;
    bool& ref = expected;
    for(auto & pair : pool) {
        if (pair->get_is_busy_ref().compare_exchange_strong(ref, true)) {
            return pair->get_conn();
        }//if false it means that its busy
    }
    std::lock_guard<std::mutex> guard(vector_mutex);//increment size
    std::atomic_bool t = true;
    pool.emplace_back(std::make_shared<pool_elem>());
    pool.back()->get_is_busy_ref().store(t);// because we are giving the resource to the caller
    return pool.back()->get_conn();
}

void connection_pool_inner::release_connection(gardener_db &connection) {
    for (auto &pair: pool) {
        if (&(pair->get_conn()) == &connection) {
            pair->get_is_busy_ref().store(false);
        }
    }
}

connection_pool_inner *connection_pool_inner::instance() {
    static connection_pool_inner inner;
    return &inner;
}

bool connection_pool_inner::drop_one(gardener_db &connection) {
    std::lock_guard<std::mutex> guard(vector_mutex);
    int count = 0;
    for (auto &pair: pool) {
        if (&(pair->get_conn()) == &connection) {
            bool is_busy = pair->get_is_busy_weak();
            if (is_busy) {
                return false;
            }
            break;
        }
        count++;
    }
    pool.erase(pool.begin() + count);
    return true;
}

std::vector<std::shared_ptr<pool_elem>> connection_pool_inner::get_pool() {
    return pool;
}


//----------------------POOL ELEM
pool_elem::pool_elem() : is_busy(false), connection() {}

bool pool_elem::get_is_busy_weak() {
    return this->is_busy.load();
}

std::atomic_bool &pool_elem::get_is_busy_ref() {
    return this->is_busy;
}

gardener_db &pool_elem::get_conn() {
    return this->connection;
}


connection_handler::connection_handler() {
    inner = connection_pool_inner::instance();
    db = &inner->get_connection();
}

gardener_db *connection_handler::get() {
    return db;
}

connection_handler::~connection_handler() = default;

