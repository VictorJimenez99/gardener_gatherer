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

template <class T>
class blocking_vector{
private:
    std::mutex vector_mutex;
    std::vector<T> inner;
public:
    blocking_vector() = default;
    T back();
    std::vector<T> get_copy();
    void emplace_back(T t);
    bool drop_one(T element);
    long unsafe_get_size() {return inner.size();};
    long get_size(){std::lock_guard g(vector_mutex); return inner.size();};
};

class pool_elem {
private:
    std::atomic_bool is_busy;
    gardener_db connection;
public:

    pool_elem();
    gardener_db &get_conn();
    std::atomic_bool &get_is_busy_ref();

};

class connection_pool_inner {
private:
    blocking_vector<std::shared_ptr<pool_elem>> pool;
    connection_pool_inner();
public:
    static connection_pool_inner& get_instance();
    gardener_db& get_connection();
    bool return_connection(gardener_db &elem);
    blocking_vector<std::shared_ptr<pool_elem>> &unsafe_get_pool();

};


class connection_pool {
private:
    gardener_db* connection;
public:
    connection_pool();
    gardener_db* get();
    ~connection_pool();
};


#endif //GARDENER_CONNECTION_POOL_H
