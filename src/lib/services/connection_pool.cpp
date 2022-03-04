//
// Created by victor on 27/02/22.
//

#include <iostream>
#include "connection_pool.h"
#include "../constants/constants.h"

pool_elem::pool_elem(): is_busy(false), connection() {}

gardener_db &pool_elem::get_conn() {
    return connection;
}
std::atomic_bool &pool_elem::get_is_busy_ref() {
    return is_busy;
}
template<class T>
std::vector<T> blocking_vector<T>::get_copy() {
    auto guard = std::lock_guard(vector_mutex);
    return inner;
}
template<class T>
void blocking_vector<T>::emplace_back(T t) {
    auto guard = std::lock_guard(vector_mutex);
    inner.emplace_back(t);
}

template<class T>
bool blocking_vector<T>::drop_one(T element) {
    std::lock_guard guard(vector_mutex);
    int pos = 0;
    bool found = false;
    for (auto item: inner) {
        if(item == element) {
            found = true;
            break;
        }
        pos++;
    }

    if(!found) return false;
    inner.erase(inner.begin() + pos);
    return true;
}

template<class T>
T blocking_vector<T>::back() {
    auto guard = std::lock_guard(vector_mutex);
    return inner.back();
}

connection_pool_inner::connection_pool_inner() {
    for (int i = 0; i < CONNECTION_POOL_START_SIZE; i++) {
        pool.emplace_back(std::make_shared<pool_elem>());
    }
}

connection_pool_inner &connection_pool_inner::get_instance() {
    static connection_pool_inner inner;
    return inner;
}

gardener_db &connection_pool_inner::get_connection() {
    auto pool_copy = pool.get_copy();
    for(auto& pair: pool_copy) {
        bool expected = false;
        std::atomic_bool &ref = pair->get_is_busy_ref();
        if (ref.compare_exchange_strong(expected, true)) {
            return pair->get_conn();
        }//if false it means that its busy
    }
    std::shared_ptr<pool_elem> new_elem = std::make_shared<pool_elem>();
    new_elem->get_is_busy_ref().store(true);
    pool.emplace_back(new_elem);
    return new_elem->get_conn();
}

bool connection_pool_inner::return_connection(gardener_db &elem) {
    auto pool_copy = pool.get_copy();
    int position = 0;
    bool found = false;
    std::shared_ptr<pool_elem> ptr;
    for (const auto& item: pool_copy) {
        if(&item->get_conn() == &elem) {
            found = true;
            ptr = item;
            break;
        }
        position++;
    }
    if(!found) return false;

    ptr->get_is_busy_ref().store(false);

    if(pool_copy.size() > 2*CONNECTION_POOL_START_SIZE) {
        pool.drop_one(ptr);
    }
    return true;
}

blocking_vector<std::shared_ptr<pool_elem>> &connection_pool_inner::unsafe_get_pool() {
    return pool;
}

connection_pool::connection_pool() {
    auto& instance = connection_pool_inner::get_instance();
    connection = &instance.get_connection();
}

gardener_db *connection_pool::get() {
    return connection;
}

connection_pool::~connection_pool() {
    auto& instance = connection_pool_inner::get_instance();
    instance.return_connection(*connection);
}
