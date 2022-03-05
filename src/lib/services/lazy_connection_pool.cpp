//
// Created by victor on 05/03/22.
//

#include <iostream>
#include "lazy_connection_pool.h"

lazy_connection_pool &lazy_connection_pool::get_instance() {
    static lazy_connection_pool inner;
    return inner;
}

pool_request_result lazy_connection_pool::get_connection() {
    for(auto & pair:pool) {
        bool expected = false;
        std::atomic_bool &ref = pair->get_is_busy_ref();
        if (ref.compare_exchange_strong(expected, true)) {
            auto conn = pair->get_connection();
            pool_request_result ret(true, &conn);
            return ret;
        }//if false it means that its busy
    }
    return {false, nullptr};
}

void lazy_connection_pool::give_back(const std::shared_ptr<gardener_db>&db_conn) {
    for(auto & pair:pool) {
        auto address_given = &*db_conn;
        auto current_address = &*pair->get_connection();
        if(address_given == current_address){
            pair->get_is_busy_ref().store(false);
            break;
        }
    }
}

lazy_connection_pool::lazy_connection_pool(){
    for(int i = 0; i < CONNECTION_POOL_SIZE; i++) {
        pool[i] = std::make_shared<pool_element>();
    }
};


db_connection::db_connection():pool_connection(lazy_connection_pool::get_instance()), ownership(false) {
    pool_request_result result = pool_connection.get_connection();
    ownership = !result.was_successful(); // if it was successful, this object doesn't own the data
    if(ownership) {
        db = std::make_shared<gardener_db>();
        return;
    } else{
        db = *result.get();
        return;
    }
}

db_connection::~db_connection() {
     if(!ownership) {
         pool_connection.give_back(db);
     }
}

std::shared_ptr<gardener_db> db_connection::get() {
    return db;
}
