#include <iostream>
#include "lib/services/connection_pool.h"

int main() {

    gardener_db *handler = connection_handler().get();

    if (handler->schema_is_complete()) {
        std::cout << "schema is complete" << std::endl;
    } else {
        std::cout << "Error: shutting down gardener app" << std::endl;
        return -1;
    }
    // listen for requests and process them in a tcp socket}
}