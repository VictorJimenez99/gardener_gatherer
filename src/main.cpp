#include <memory>
#include <iostream>
#include "lib/services/GardenerDB.h"

int main() {
    auto handler = GardenerDB();
    if(handler.schema_is_complete()) {
        std::cout << "schema is complete" << std::endl;
    }else {
        std::cout << "error closing app" << std::endl;
        return -1;
    }

    return 0;
}
